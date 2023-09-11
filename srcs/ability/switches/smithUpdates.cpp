
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
		case THROW_TOOLBOX:
		{
			ToolThrowAnim *used = (ToolThrowAnim*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SUPPLY_ALLY:
		{
			SupplyAlly *used = (SupplyAlly*)anim.animation;
			used->Update();
			if (used->removeFat)
			{
				t_Supply *use = (t_Supply*)ability->stats;
				int amount = use->amount;
				Character *target = used->target;
				int maxFat = target->stats.maxFatigue;
				float multi = (float)amount / 100.0f;
				int reduce = rounding((float)maxFat * multi);
				target->stats.fatigue -= reduce;
				if (target->stats.fatigue < 0)
					target->stats.fatigue = 0;
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
