
#include "../../../hdr/global.h"

static bool IsCharacter(t_AiMapUnit &point)
{
	if (point.character == NULL)
		return (false);
	return (true);
}

static float GetHealthScore(t_AiMapUnit **map, bool ally)
{
	float ah = 0.0f;
	float eh = 0.0f;
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			bool value = IsCharacter(map[i][j]);
			if (value == false)
				continue ;
			if (map[i][j].character->character->ally)
			{
				if (map[i][j].character->alive)
					ah += (float)(map[i][j].character->health + map[i][j].character->armor);
			}
			else
			{
				if (map[i][j].character->alive)
					eh += (float)(map[i][j].character->health + map[i][j].character->armor);
			}
		}
	}
	float finalValue = ah - eh;
	return (finalValue);
}

float GetAiScore(t_AiMapUnit **map, bool ally)
{
	float healthScore = GetHealthScore(map, ally);
	return (healthScore);
}
