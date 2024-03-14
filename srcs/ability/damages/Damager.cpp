
#include "../../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -220
#define THE_HOVER_BAR_WIDTH 3200
#define THE_BAR_LIFETIME 88

static bool TopRight(SDL_Point character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character;
	if (pos.y <= cPos.y)
	{
		if (pos.x > cPos.x)
			return (true);
		if (pos.x == cPos.x)
		{
			int x = getXToLeft(pos);
			if (x == pos.x)
				return (true);
		}
	}
	return (false);
}

static bool TopLeft(SDL_Point character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character;
	if (pos.y <= cPos.y)
	{
		if (pos.x < cPos.x)
			return (true);
		if (pos.x == cPos.x)
		{
			int x = getXToRight(pos);
			if (x == pos.x)
				return (true);
		}
	}
	return (false);
}

static bool downRight(SDL_Point character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character;
	if (pos.y > cPos.y)
	{
		if (pos.x > cPos.x)
			return (true);
		if (pos.x == cPos.x)
		{
			int x = getXToLeft(pos);
			if (x == pos.x)
				return (true);
		}
	}
	return (false);
}

static void addStatus(Character *damager, Character *target, t_Ability *ability, bool hit)
{
	if (ability == NULL)
		return ;
	if (target == NULL || target->killed)
		return ;
	switch (ability->statusSign)
	{
		case StatusSigns::BURN:
		{
			if (!hit)
			{
				CreateTextSnippet(damager, target, "MISS", 900, Color(176, 79, 0));
				break ;
			}
			gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(176, 79, 0), 0);
			target->statuses.burns.push_back(3);
			CreateTextSnippet(damager, target, "burned", 1200, Color(176, 79, 0));
			break ;
		}
		case StatusSigns::STUN:
		{
			if (!hit && target->statuses.stun == 0)
			{
				CreateTextSnippet(damager, target, "MISS", 900, Color(186, 168, 0));
				break ;
			}
			if (target->statuses.stun == 0)
				CreateTextSnippet(damager, target, "stunned", 1200, Color(186, 168, 0));
			target->statuses.stun = 1;
			break ;
		}
		case StatusSigns::BLEED:
		{
			if (!hit)
			{
				CreateTextSnippet(damager, target, "MISS", 900, Color(184, 6, 6));
				break ;
			}
			gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(184, 6, 6), 10);
			t_AttackWithStatus *val = (t_AttackWithStatus*)ability->stats;
			int stacks = val->stacks;
			std::string used;
			used += std::to_string(stacks);
			used += " bleed";
			const char *ret = used.c_str();
			CreateTextSnippet(damager, target, ret, 1000, Color(184, 6, 6));
			for (int i = 0; i < stacks; i++)
				target->statuses.bleed.push_back(3);
		}
	}
}

Vector Damager::GetDirection(SDL_Point character, Character *target)
{
	if (TopRight(character, target))
		return (Vector(0.5f, -0.5f));
	if (TopLeft(character, target))
		return (Vector(-0.5f, -0.5f));
	if (downRight(character, target))
		return (Vector(0.5f, 0.5f));
	return (Vector(-0.5f, 0.5f));
	
}

void Damager::AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets, bool sound)
{
	for (int i = 0; i < targets.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targets[i].y][targets[i].x].character;
		if (targ == NULL || targ->killed)
			continue ;
		SDL_Point damages = GetDamageValues(targ, character, ability);
		if (sound)
		{
			t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
			t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
			t_Sound add5 = {gameState.audio.hitEffect, Channels::VOLUME_30, 0};
			std::vector<t_Sound> sounds = {add2, add3, add5};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), damages.x, damages.y, GetDirection(character->position, targ), sounds);
			CreateDamageSnippet(character->position, targ, damages.x + damages.y);
		}
		else
		{
			std::vector<t_Sound> sounds = {};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), damages.x, damages.y, GetDirection(character->position, targ), sounds);
			CreateDamageSnippet(character->position, targ, damages.x + damages.y);
		}
		bool ret = StatusApply(ability, character, targ);
		addStatus(character, targ, ability, ret);
	}
}

void Damager::AddBleedDamage(Character *target, int amount)
{
	if (target->stats.health <= 0)
		return ;
	SetDelayer(2);
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::VOLUME_8, 0};
	t_Sound add4 = {gameState.audio.bleed, Channels::VOLUME_23, 0};
	t_Sound add5 = {gameState.audio.hitEffect, Channels::VOLUME_30, 0};
	std::vector<t_Sound> sounds = {add3, add4, add5};
	Vector dir(1.0f, 0.0f);
	if (target->ally)
		dir.x = -1.0f;
	if ((target->stats.health - amount) > 0)
	{
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 0);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 6);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 12);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 18);
	}
	damageCreator.CreateDamage(target, Color(255, 0, 0), 0, amount, dir, sounds);
	CreatePoisonSnippet(target, rand() % 100 + 1, Color(184, 6, 6));
}

void Damager::AddPoisonDamage(Character *target, int amount)
{
	if (target->stats.health <= 0)
		return ;
	SetDelayer(2);
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::VOLUME_8, 0};
	t_Sound add4 = {gameState.audio.poison, Channels::VOLUME_23, 0};
	t_Sound add5 = {gameState.audio.hitEffect, Channels::VOLUME_30, 0};
	std::vector<t_Sound> sounds = {add3, add4, add5};
	Vector dir(1.0f, 0.0f);
	if (target->ally)
		dir.x = -1.0f;
	if ((target->stats.health - amount) > 0)
	{
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 0);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 6);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 12);
		gameState.updateObjs.info->AddColorEffect(target->sprite, 3, Color(28, 138, 0), 18);
	}
	damageCreator.CreateDamage(target, Color(255, 0, 0), 0, amount, dir, sounds);
	CreatePoisonSnippet(target, rand() % 100 + 1, Color(28, 138, 0));
}

void Damager::AddOpportunityDamage(SDL_Point damager, Character *target)
{
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
	t_Sound add4 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
	t_Sound add5 = {gameState.audio.hitEffect, Channels::VOLUME_30, 0};
	std::vector<t_Sound> sounds = {add3, add4, add5};
	SDL_Point damages = GetOpportunityDamageValues(target, damager);
	SetDelayer(3);
	if (target->cSing == LION)
		damageCreator.CreateDamage(target, Color(255, 0, 0), damages.x, damages.y, GetDirection(damager, target), sounds, false);
	else
		damageCreator.CreateDamage(target, Color(255, 0, 0), damages.x, damages.y, GetDirection(damager, target), sounds);
	CreateDamageSnippet(damager, target, damages.x + damages.y, true);
}

void Damager::Update()
{
	damageCreator.Update();
}
