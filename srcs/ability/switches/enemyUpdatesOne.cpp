
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
		case SKELE_LUNGE:
		{
			SkeleLunge *used = (SkeleLunge*)anim.animation;
			used->Update();
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
			if (used->done)
			{
				PlaySound(gameState.audio.BuffEffect, Channels::VOLUME_11, 0);
				character->statuses.buffs.push_back({BuffTypes::OPPORTUNITY_ACCURACY, 2, 50, false});
				new BuffEffect(character, true);
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}