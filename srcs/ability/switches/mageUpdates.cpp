
#include "../../../hdr/global.h"

void Abilities::UpdateMageAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case LIGHTNING_BOLT:
		{
			MageAttack *used = (MageAttack*)anim.animation;
			used->Update();
			if (used->createEffect)
				objects.push_back({new LightningBolt(targetPoint), LIGHTNING_BOLT});
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}

void Abilities::UpdateMageObject(t_Object &object, int index)
{
	switch (object.type)
	{
		case LIGHTNING_BOLT:
		{
			LightningBolt *used = (LightningBolt*)object.object;
			used->Update();
			if (used->createDamage)
			{
				if (RangeCheckWithoutBlockers(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, targetPoint, target, true);
			}
			if (used->done)
			{
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
	}
}
