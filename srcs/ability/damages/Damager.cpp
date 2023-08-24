
#include "../../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -220
#define THE_HOVER_BAR_WIDTH 3200
#define THE_BAR_LIFETIME 88

static bool TopRight(Character *character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character->position;
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

static bool TopLeft(Character *character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character->position;
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

static bool downRight(Character *character, Character *target)
{
	SDL_Point pos = target->position;
	SDL_Point cPos = character->position;
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

static void addStatus(Character *damager, Character *target, t_Ability *ability)
{
	if (ability == NULL)
		return ;
	if (target == NULL || target->killed)
		return ;
	switch (ability->statusSign)
	{
		case StatusSigns::BURN:
			target->statuses.burns.push_back(3);
			CreateTextSnippet(damager, target, "burn", 1200, Color(176, 79, 0));
			break ;
		case StatusSigns::STUN:
			if (target->statuses.stun == 0)
				CreateTextSnippet(damager, target, "stun", 1200, Color(186, 168, 0));
			target->statuses.stun = 1;
			break ;
	}
}

Vector Damager::GetDirection(Character *character, Character *target)
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
		if (sound)
		{
			t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
			t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
			std::vector<t_Sound> sounds = {add2, add3};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), 5, 5, GetDirection(character, targ), sounds);
			CreateDamageSnippet(character, targ, rand() % 100 + 1);
		}
		else
		{
			std::vector<t_Sound> sounds = {};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), 5, 5, GetDirection(character, targ), sounds);
			CreateDamageSnippet(character, targ, 12 + 12);
		}
		if (StatusApply(ability, character, targ))
			addStatus(character, targ, ability);
	}
}

void Damager::AddOpportunityDamage(Character *damager, Character *target)
{
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::LOWER_VOLUME_HIT, 0};
	std::vector<t_Sound> sounds = {add3};
	damageCreator.CreateDamage(target, Color(255, 0, 0), 5, 5, GetDirection(damager, target), sounds);
	CreateDamageSnippet(damager, target, rand() % 100 + 1, true);
}

void Damager::Update()
{
	damageCreator.Update();
}
