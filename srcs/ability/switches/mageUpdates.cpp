
#include "../../../hdr/global.h"

static bool CheckForNoOtherMages(Character *character, Character *target)
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *used = gameState.battle.ground->characters[i].character;
		if (used == character)
			continue ;
		if (used->statuses.hosting != NULL)
		{
			Character *ret = (Character*)used->statuses.hosting;
			if (ret == target)
				return (false);
		}
	}
	return (true);
}

static bool CreateHostEffect(t_Ability *ability, Character *character, Character *target)
{
	if (target->ally)
	{
		CreateTextSnippet(character, target, "host", 1200, Color(145, 3, 110));
		new HostEffect(target);
		if (character->statuses.hosting != NULL)
		{
			Character *ret = (Character*)character->statuses.hosting;
			if (CheckForNoOtherMages(character, target))
				ret->statuses.hosted = false;
		}
		target->statuses.hosted = true;
		character->statuses.hosting = target;
		return (true);
	}
	if (!StatusApply(ability, character, target))
		return (false);
	CreateTextSnippet(character, target, "host", 1200, Color(145, 3, 110));
	new HostEffect(target);
	if (character->statuses.hosting != NULL)
	{
		Character *ret = (Character*)character->statuses.hosting;
		if (CheckForNoOtherMages(character, target))
			ret->statuses.hosted = false;
	}
	target->statuses.hosted = true;
	character->statuses.hosting = target;
	return (true);
}

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
		case ROCK_FALL:
		{
			MageAttack *used = (MageAttack*)anim.animation;
			used->Update();
			if (used->createEffect)
			{
				for (int i = 0; i < targPoints.size(); i++)
					objects.push_back({new RockFall(targPoints[i]), ROCK_FALL});
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case HOST_EYES:
		{
			HostEyesAnim *used = (HostEyesAnim*)anim.animation;
			used->Update();
			if (used->done)
			{
				if (!CreateHostEffect(ability, character, target))
					CreateMiss(character->position, target->position, target, true);
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
				if (MeleeCheck(character, target, ability))
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
		case ROCK_FALL:
		{
			RockFall *used = (RockFall*)object.object;
			used->Update();
			if (used->createDamage)
			{
				SDL_Point targ = used->target;
				Character *ret = gameState.battle.ground->map[targ.y][targ.x].character;
				std::vector<SDL_Point> targyy = {targ};
				if (ret != NULL)
				{
					if (MeleeCheck(character, ret, ability))
						damager.AddDamage(ability, character, targyy);
					else
						CreateMiss(character->position, targ, ret, true);
				}
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
