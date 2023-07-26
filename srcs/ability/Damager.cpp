
#include "../../hdr/global.h"
#define HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP -220
#define THE_HOVER_BAR_WIDTH 3200
#define THE_BAR_LIFETIME 58

Vector Damager::GetDirection(Character *character, Character *target)
{
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect eDest = target->sprite->dest;
	Vector toEnemy(cDest.x - eDest.x, cDest.y - eDest.y);
	float angle = vectorAngle(Vector(0.0f, 1.0f), toEnemy);
	float sign = (cDest.x <= eDest.x) ? 1.0f : -1.0f;
	if (angle < PI / 2)
		return(Vector(0.5 * sign, -0.5f));
	return (Vector(0.5f * sign, 0.5f));
}

void Damager::PositionBars(Character *target, t_Bars &bars)
{
	Vector topMid = GetCharacterTopMid(target);
	topMid.y -= 1000.0f;
	int diff = THE_HOVER_BAR_WIDTH / 2;
	topMid.x -= (float)diff;
	SDL_Point place = {rounding(topMid.x), rounding(topMid.y)};
	bars.health->Position(place);
	place.y -= HOW_MUCH_THE_BAR_NEEDS_TO_BE_ON_TOP;
	bars.armor->Position(place);
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
	PositionBars(target, add);
	add.armor->Update(target, true);
	add.health->Update(target, false);
	bars.push_back(add);
}

void Damager::AddDamage(t_Ability *ability, Character *character, std::vector<SDL_Point> &targets)
{
	for (int i = 0; i < targets.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targets[i].y][targets[i].x].character;
		if (targ == NULL || targ->killed)
			continue ;
		CreateBars(targ);
		t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
		t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
		std::vector<t_Sound> sounds = {add2, add3};
		damageCreator.CreateDamage(targ, Color(255, 0, 0), 10, 10, GetDirection(character, targ), sounds);
	}
}

void Damager::UpdateBars()
{
	for (int i = 0; i < bars.size(); i++)
	{
		bars[i].timer -= 1;
		bars[i].armor->Update(bars[i].target, true);
		bars[i].health->Update(bars[i].target, false);
		if (bars[i].timer <= 0)
		{
			delete bars[i].health;
			delete bars[i].armor;
			bars[i].target->damaged = false;
			bars.erase(bars.begin() + i);
			i--;
		}
	}
}

void Damager::Update()
{
	damageCreator.Update();
	UpdateBars();
}
