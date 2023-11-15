
#include "../../../hdr/global.h"

static void ShieldBashHit(Character *character, Character *target, t_Ability *ability)
{

}

void Abilities::UpdateKnightAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case FLAIL_STRIKE:
		{
			KnightAttack *used = (KnightAttack*)anim.animation;
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
		case SHILED_BASH:
		{
			ShieldBash *used = (ShieldBash*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (!MeleeCheck(character, target, ability))
					CreateMiss(character->position, target->position, target, true);
				else
				{
					CreateDamage();
					ShieldBashHit(character, target, ability);
				}
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

