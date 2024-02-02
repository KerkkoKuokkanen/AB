
#include "../../../hdr/global.h"

void Abilities::UpdateEnemyAnimationOne(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case SKELE_MELEE:
		{
			SkeleMeleeAnim *used = (SkeleMeleeAnim*)anim.animation;
			used->Update();
			if (used->createDamage)
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