
#include "../../../hdr/global.h"
#define NOT_ACCEPTED(value) ((value) < 0.0f)

typedef struct s_Ai2State
{
	t_AiCharacter *current;
	t_AiCharacter **charQ;
	t_AiMapItem **items;
}				t_Ai2State;

int abilityUseIndex = 0;

static t_Ai2State GetAi2AbilityScore(t_Ability *ability, t_AiCharacter *current, t_AiCharacter **charQ, t_AiMapItem **items, SDL_Point pos)
{
	
}

void AiIterator2::AbilityToPosition(uint8_t x, uint8_t y)
{
	SDL_Point pos = {x, y};
	for (int i = 0; i < current->character->abilities.size(); i++)
	{
		t_Ability *used = &current->character->abilities[i];
		abilityUseIndex = 0;
		while (true)
		{
			//SDL_FPoint ret = GetAi2AbilityScore(used, current, charQ, mapItems, pos);
			if (NOT_ACCEPTED(ret.y))
				break ;
			AddToTheAiMoves(savedMoves[i], {pos, abilityUseIndex, ret.x}, ally);
			abilityUseIndex += 1;
		}
	}
}
