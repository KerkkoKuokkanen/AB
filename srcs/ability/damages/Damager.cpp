
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

void Damager::PositionBars(Character *target, t_Bars &bars)
{
	Vector topMid((float)(target->sprite->dest.x + target->topMid.x), (float)(target->sprite->dest.y + target->topMid.y));
	topMid.y -= 1000.0f;
	int diff = THE_HOVER_BAR_WIDTH / 2;
	topMid.x -= (float)diff;
	SDL_Point place = {rounding(topMid.x), rounding(topMid.y)};
	bars.health->Position(place);
	place.y = place.y - HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP;
	bars.armor->Position(place);
	Vector pos((float)place.x, (float)(place.y - 740.0f));
	bars.statusBar->Postion(pos);
}

void Damager::CreateBars(Character *target)
{
	for (int i = 0; i < bars.size(); i++)
	{
		if (bars[i].target == target)
		{
			bars[i].timer = THE_BAR_LIFETIME;
			return ;
		}
	}
	t_Bars add;
	add.target = target;
	add.timer = THE_BAR_LIFETIME;
	SDL_Rect dest = {0, 0, THE_HOVER_BAR_WIDTH, 500};
	add.health = new Bar(dest, false, false);
	add.armor = new Bar(dest, false, false);
	add.health->ChangeToSmallBar();
	add.armor->ChangeToSmallBar();
	add.armor->SetColor(201, 14, 14);
	add.health->SetColor(101, 97, 135);
	add.statusBar = new Statuses(target, 640, 310, false);
	PositionBars(target, add);
	add.armor->Update(target, true);
	add.health->Update(target, false);
	add.statusBar->Update();
	bars.push_back(add);
}

void Damager::CreateDebuff(t_Ability *ability, Character *character, SDL_Point targ)
{
	Character *target = gameState.battle.ground->map[targ.y][targ.x].character;
	if (target == NULL)
		return ;
	switch (character->cSing)
	{
		case PYRO:
			statuses.push_back(new AddStatus(character, target, StatusSigns::BURN));
			break ;
		case LION:
			target->statuses.stun = 1;
			break ;
	}
}

void Damager::AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets, bool sound)
{
	for (int i = 0; i < targets.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targets[i].y][targets[i].x].character;
		if (targ == NULL || targ->killed)
			continue ;
		CreateBars(targ);
		if (sound)
		{
			t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
			t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
			std::vector<t_Sound> sounds = {add2, add3};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), 5, 5, GetDirection(character, targ), sounds);
		}
		else
		{
			std::vector<t_Sound> sounds = {};
			damageCreator.CreateDamage(targ, Color(255, 0, 0), 5, 5, GetDirection(character, targ), sounds);
		}
		if (StatusApply(ability, character, targ))
			CreateDebuff(ability, character, targ->position);
	}
}

void Damager::UpdateBars()
{
	for (int i = 0; i < bars.size(); i++)
	{
		bars[i].timer -= 1;
		bars[i].armor->Update(bars[i].target, true);
		bars[i].health->Update(bars[i].target, false);
		bars[i].statusBar->Update();
		if (bars[i].timer <= 0)
		{
			delete bars[i].health;
			delete bars[i].armor;
			delete bars[i].statusBar;
			bars[i].target->damaged = false;
			bars.erase(bars.begin() + i);
			i--;
		}
	}
}

void Damager::UpdateStatuses()
{
	for (int i = 0; i < statuses.size(); i++)
	{
		statuses[i]->Update();
		if (statuses[i]->done)
		{
			delete statuses[i];
			statuses.erase(statuses.begin() + i);
			i--;
		}
	}
}

void Damager::Update()
{
	damageCreator.Update();
	UpdateStatuses();
	UpdateBars();
}
