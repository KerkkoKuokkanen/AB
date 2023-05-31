
#include "../../hdr/global.h"

SDL_Point getPositionOfCharacter(Character *character)
{
	SDL_Point position = {0, 0};
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (gameState.battle.ground->map[i][j].character != NULL)
			{
				if (gameState.battle.ground->map[i][j].character == character)
				{
					position = {j , i};
					return (position);
				}
			}
		}
	}
	return (position);
}

Vector DaggerThrow::GetDirection(Character *enemy)
{
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect eDest = enemy->sprite->dest;
	Vector toEnemy(cDest.x - eDest.x, cDest.y - eDest.y);
	float angle = vectorAngle(Vector(0.0f, 1.0f), toEnemy);
	float sign = (cDest.x <= eDest.x) ? 1.0f : -1.0f;
	if (angle < PI / 2)
		return(Vector(0.5 * sign, -0.5f));
	return (Vector(0.5f * sign, 0.5f));
}

void DaggerThrow::OverEnemy(Character *enemy)
{
	if (gameState.keys.click != RELEASE_CLICK)
		return ;
	gameState.updateObjs.animationManager->SetAnimation(new DaggerThrowAnim(character, enemy), DAGGER_THROW_ANIMATION);
	thrown = true;
}

void DaggerThrow::Update()
{
	Color purp = {255, 69, 56}, colorH(245, 147, 66), colorL(204, 126, 61);
	gameState.updateObjs.groundColoring->ClearMap();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] == TOOL_MAP_SIGN)
				continue ;
			SDL_Point pos = {j, i};
			if (gameState.battle.ground->map[i][j].character != NULL
				&& (gameState.battle.ground->map[i][j].marked || gameState.battle.ground->map[i][j].character->hover)
				&& gameState.battle.ground->map[i][j].character->ally == false)
			{
				gameState.updateObjs.groundColoring->SetColoredPosition(pos, purp, purp);
				OverEnemy(gameState.battle.ground->map[i][j].character);
			}
			else
				gameState.updateObjs.groundColoring->SetColoredPosition(pos, colorH, colorL);
		}
	}
}

void DaggerThrow::MarkPosition(SDL_Point pos, int sign)
{
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return ;
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return ;
	map[pos.y][pos.x] = sign;
}

void DaggerThrow::GetInactivePositions()
{
	int modder = (position.y % 2 == 0) ? (-1) : 1;
	MarkPosition(position, TOOL_MAP_SIGN);
	SDL_Point pos = {position.x, position.y - 1};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x, position.y + 1};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x + modder, position.y - 1};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x + modder, position.y + 1};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x + 1, position.y};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x - 1, position.y};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x, position.y - 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x, position.y + 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x + 1, position.y + 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x + 1, position.y - 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x - 1, position.y + 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
	pos = {position.x - 1, position.y - 2};
	MarkPosition(pos, TOOL_MAP_SIGN);
}

DaggerThrow::DaggerThrow(Character *character)
{
	DaggerThrow::character = character;
	position = getPositionOfCharacter(character);
	map = (int**)malloc(sizeof(int *) * gameState.battle.ground->map.size());
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		map[i] = (int *)malloc(sizeof(int) * gameState.battle.ground->map[0].size());
	findMovables(map, range, position);
	Color colorH(245, 147, 66);
	Color colorL(204, 126, 61);
	GetInactivePositions();
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
	{
		for (int j = 0; j < gameState.battle.ground->map[0].size(); j++)
		{
			if (map[i][j] != TOOL_MAP_SIGN)
			{
				SDL_Point pos = {j, i};
				gameState.updateObjs.groundColoring->SetColoredPosition(pos, colorH, colorL);
			}
		}
	}
	gameState.updateObjs.groundColoring->active = true;
}

void DaggerThrow::Destroy()
{
	for (int i = 0; i < gameState.battle.ground->map.size(); i++)
		free(map[i]);
	free(map);
	gameState.updateObjs.groundColoring->ClearMap();
	gameState.updateObjs.groundColoring->active = false;
}
