
#include "../../../hdr/global.h"

static void AddBombStatuses(Character *target, Character *character, t_Ability *ability)
{
	switch(ability->type)
	{
		case NAIL_BOMB:
		{
			if (!StatusApply(ability, character, target, true))
			{
				CreateTextSnippet(character, target, "MISS", 900, Color(184, 6, 6));
				return ;
			}
			gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(184, 6, 6), 10);
			t_DamageBomb *stk = (t_DamageBomb*)ability->stats;
			int stacks = stk->stacks;
			std::string used;
			used += std::to_string(stacks);
			used += " bleed";
			const char *ret = used.c_str();
			CreateTextSnippet(character, target, ret, 1000, Color(184, 6, 6));
			for (int i = 0; i < stacks; i++)
				target->statuses.bleed.push_back(3);
			break ;
		}
	}
}

void Abilities::CreateBombDamages()
{
	for (int i = 0; i < targPoints.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targPoints[i].y][targPoints[i].x].character;
		if (targ != NULL)
		{
			if (RangeCheckWithoutBlockers(character, targ, ability))
			{
				std::vector<SDL_Point> used = {targPoints[i]};
				damager.AddDamage(ability, character, used);
				AddBombStatuses(targ, character, ability);
			}
			else
				CreateMiss(character->position, targ->position, targ, true);
		}
	}
}

void Abilities::UpdateAlchemistAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case NAIL_BOMB:
		{
			NailBomb *used = (NailBomb*)anim.animation;
			used->Update();
			if (used->createDamage)
				CreateBombDamages();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
