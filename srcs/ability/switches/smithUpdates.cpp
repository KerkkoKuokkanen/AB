
#include "../../../hdr/global.h"

void Abilities::UpdateSmithAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case HAMMER_SMACK:
		{
			HammerSmack *used = (HammerSmack*)anim.animation;
			used->Update();
			if (used->damage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
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
