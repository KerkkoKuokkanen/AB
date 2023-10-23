
#include "../../../hdr/global.h"

TurnIndicator::TurnIndicator()
{
	chosen = NULL;
}

void TurnIndicator::Update()
{
	if (chosen == NULL)
		return ;
	if (!chosen->ally)
		return ;
	if (gameState.updateObjs.abilities->active)
		return ;
	SDL_Point pos = FindCharacter(chosen);
	if (pos.x == -1 || pos.y == -1)
		return ;
	if (gameState.battle.ground->map[pos.y][pos.x].highlited ||
		gameState.battle.ground->map[pos.y][pos.x].marked)
		return ;
	float fadeMulti = cos(gameState.updateObjs.fadeIter) / 2.0f + 0.5f;
	float r = 255.0f - 194.0f;
	float g = 214.0f - 170.0f;
	float b = 105.0f - 102.0f;
	gameState.battle.ground->HighLightBlock(pos, 194 + (int)(r * fadeMulti), 170 + (int)(g * fadeMulti), 102 + (int)(b * fadeMulti));
}

SDL_Point TurnIndicator::FindCharacter(Character* character)
{
	SDL_Point ret = {-1, -1};
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (gameState.battle.ground->map[i][j].character != NULL)
			{
				if (gameState.battle.ground->map[i][j].character == character)
				{
					ret = {j, i};
					break ;
				}
			}
		}
	}
	return (ret);
}

void TurnIndicator::SetCharacter(Character *character)
{
	if (character == chosen)
		return ;
	chosen = character;
}
