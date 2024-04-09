
#include "../../../hdr/global.h"

float CrazyLoopScore(t_AiMapUnit **map, std::vector<t_AiCharacter*> &charQ)
{
	OrderTheCharQ(charQ);
	DestroyMap(map);
	return (0.0f);
}
