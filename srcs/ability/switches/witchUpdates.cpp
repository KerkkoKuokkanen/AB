
#include "../../../hdr/global.h"

bool CheckForSize(SDL_Point point1, SDL_Point point2)
{
	t_Teleport *used = (t_Teleport*)gameState.updateObjs.abilities->ability->stats;
	Character *ret = gameState.battle.ground->map[point2.y][point2.x].character;
	if (ret != NULL)
	{
		if (ret->stats.size <= used->maxSize)
			return (true);
	}
	return (false);
}

bool CheckForMaxHealth(SDL_Point point1, SDL_Point point2)
{
	Character *ret = gameState.battle.ground->map[point2.y][point2.x].character;
	if (ret == NULL)
		return (false);
	if (ret->stats.health >= ret->stats.maxHealth)
		return (false);
	return (true);
}

static void ApplyRainPoison(Character *target, Character *character, t_Ability *ability)
{
	PlaySound(gameState.audio.rainAttack[1], Channels::VOLUME_6, 0);
	gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(28, 138, 0), 0);
	t_AcidRainDamage *stack = (t_AcidRainDamage*)ability->stats;
	int stacks = stack->stacks;
	std::string used;
	used += std::to_string(stacks);
	used += " poison";
	const char *ret = used.c_str();
	CreateTextSnippet(character, target, ret, 1000, Color(28, 138, 0));
	for (int i = 0; i < stacks; i++)
		target->statuses.poison.push_back(3);
}

void Abilities::UpdateWitchAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case ACID_RAIN:
		{
			AcidRain *used = (AcidRain*)animation.animation;
			used->Update();
			if (used->createDamage)
			{
				if (!StatusApply(ability, character, target, true))
					CreateMiss(character->position, target->position, target, true);
				else
					ApplyRainPoison(target, character, ability);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case TELEPORT:
		{
			TeleStart *used = (TeleStart*)animation.animation;
			used->Update();
			if (used->createEffect)
			{
				Character *used = gameState.battle.ground->map[targPoints[0].y][targPoints[0].x].character;
				if (MeleeCheck(character, used, ability) || used->ally)
					objects.push_back({new TelePort(used, targPoints[1]), TELEPORT});
				else
					CreateMiss(character->position, used->position, used, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case HEALTH_TRANSFER:
		{
			HeartBeat *used = (HeartBeat*)animation.animation;
			used->Update();
			if (used->createEffect)
			{
				Character *source = gameState.battle.ground->map[targPoints[0].y][targPoints[0].x].character;
				if (MeleeCheck(character, source, ability) || source->ally)
				{
					Character *end = gameState.battle.ground->map[targPoints[1].y][targPoints[1].x].character;
					objects.push_back({new HealthTransfer(source, end), HEALTH_TRANSFER});
				}
				else
					CreateMiss(character->position, source->position, source, true);
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

int Abilities::CreateWitchDamage()
{
	t_HealthTransfer *stats = (t_HealthTransfer*)ability->stats;
	Character *damaged = gameState.battle.ground->map[targPoints[0].y][targPoints[0].x].character;
	Character *healed = gameState.battle.ground->map[targPoints[1].y][targPoints[1].x].character;
	float amount = (float)stats->amount / 100.0f;
	int precent = rounding((float)damaged->stats.maxHealth * amount);
	int missing = healed->stats.maxHealth - healed->stats.health;
	int doThisDamage = (missing > precent) ? precent : missing;
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
	t_Sound add4 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
	t_Sound add5 = {gameState.audio.hitEffect, Channels::VOLUME_30, 0};
	std::vector<t_Sound> sounds = {add3, add4, add5};
	damager.damageCreator.CreateDamage(damaged, Color(255, 0, 0), 0, doThisDamage, damager.GetDirection(character->position, damaged), sounds);
	CreateDamageSnippet(character->position, damaged, rand() % 100 + 1);
	return (doThisDamage);
}

void Abilities::UpdateWitchObjects(t_Object &object, int index)
{
	switch (object.type)
	{
		case TELEPORT:
		{
			TelePort *used = (TelePort*)object.object;
			used->Update();
			if (used->done)
			{
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
		case HEALTH_TRANSFER:
		{
			HealthTransfer *used = (HealthTransfer*)object.object;
			used->Update();
			if (used->createDamage)
			{
				int save = CreateWitchDamage();
				used->damageDoneSave = save;
			}
			if (used->createEffect)
			{
				Character *targ = gameState.battle.ground->map[targPoints[1].y][targPoints[1].x].character;
				Character *source = gameState.battle.ground->map[targPoints[0].y][targPoints[0].x].character;
				targ->stats.health += used->damageDoneSave;
				if (targ->stats.health > targ->stats.maxHealth)
					targ->stats.health = targ->stats.maxHealth;
				new HealEffect(targ, source, used->damageDoneSave);
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
