
#include "../../../hdr/global.h"

t_AiMapUnit **GetReplica(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	t_AiMapUnit **ret = (t_AiMapUnit**)malloc(sizeof(t_AiMapUnit*) * h);
	for (int i = 0; i < h; i++)
	{
		ret[i] = (t_AiMapUnit*)malloc(sizeof(t_AiMapUnit) * w);
		for (int j = 0; j < w; j++)
		{
			std::memcpy(&ret[i][j], &map[i][j], sizeof(t_AiMapUnit));
		}
	}
	return (ret);
}

void DestroyMap(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}
