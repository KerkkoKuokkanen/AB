
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
				if (RangeCheckWithoutBlockers(character, used, ability) || used->ally)
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
	}
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
	}
}
