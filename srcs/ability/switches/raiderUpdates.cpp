
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
	}
}
