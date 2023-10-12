
#include "../../../hdr/global.h"

void Abilities::UpdateRaiderAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case AXE_SLASH:
		{
			AxeSlash *used = (AxeSlash*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			break ;
		}
		case AXE_JUMP:
		{
			AxeJumpAnim *used = (AxeJumpAnim*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
				{
					std::vector<SDL_Point> point = {target->position};
					damager.AddDamage(ability, character, point);
				}
				else
					CreateMiss(character->position, target->position, target, true);
			}
			break ;
		}
		case TOXIC_BLADE:
		{
			ToxinBuff *used = (ToxinBuff*)anim.animation;
			used->Update();
			if (used->addStatus)
			{
				t_ToxicBlade *add = (t_ToxicBlade*)ability->stats;
				for (int i = 0; i < add->hits; i++)
					character->statuses.toxicBlade.push_back(add->stacks);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
