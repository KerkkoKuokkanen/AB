
#include "../../../hdr/global.h"

void Abilities::UpdateThiefAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case DAGGER_THROW:
		{
			DaggerThrowAnim *used = (DaggerThrowAnim*)animation.animation;
			used->Update();
			if (used->timeForAbility)
			{
				int chance = GetChance(character, target, ability);
				Character *ret = RangedCheck(character, target, chance);
				targetPoint = ret->position;
				objects.push_back({new Dagger(character, ret, chance), DAGGER_OBJ});
			}
			if (!used->active)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SMOKE_BOMB:
		{
			SmokeBombAnim *use = (SmokeBombAnim*)animation.animation;
			use->Update();
			if (!use->active)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			if (use->timeForAbility)
				objects.push_back({new SmokeBomb(character->position, targetPoint), SMOKE_OBJ});
			break ;
		}
		case DAGGER_SLASH:
		{
			DaggerSlashAnim *use = (DaggerSlashAnim*)animation.animation;
			use->Update();
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}

void Abilities::UpdateThiefObject(t_Object &object, int index)
{
	switch (object.type)
	{
		case DAGGER_OBJ:
		{
			Dagger *used = (Dagger*)object.object;
			used->Update();
			if (used->remove)
			{
				if (used->createDamage)
					CreateDamage();
				else
					PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
		case SMOKE_OBJ:
		{
			SmokeBomb *used = (SmokeBomb*)object.object;
			used->Update();
			if (used->setEffect)
				effectUpdater.SetEffect(character, targetPoint, ability);
			if (used->destroy)
			{
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
	}
}
