
#include "../../../hdr/global.h"
#define LAUNCH_TIME 38

FlameBlast::FlameBlast(Character *character, std::vector<SDL_Point> &targets, t_Ability *ability)
{
	FlameBlast::targets = targets;
	FlameBlast::character = character;
	FlameBlast::ability = ability;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.chars.pyroFlameBlast);
	aura = new Sprite(gameState.textures.attacks.fireBallAura, character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	aura->orderLayer = character->sprite->orderLayer;
	aura->z = character->sprite->z + 0.1f;
	aura->AlphaMod(0);
	gameState.render->AddSprite(aura, BATTLEGROUND_LAYER);
	amount = targets.size();
}

void FlameBlast::UpdateAura()
{
	if (iterator >= amount)
	{
		aura->AlphaMod(0);
		return ;
	}
	if (counter % 3 == 0 && counter != 0)
		alpha -= 45;
	else
		alpha += 25;
	if (alpha > 200)
		alpha = 200;
	aura->AlphaMod(alpha);
}

bool FlameBlast::CheckIfDone()
{
	if (iterator >= amount)
	{
		for (int i = 0; i < fireBalls.size(); i++)
		{
			if (fireBalls[i].done == false)
				return (false);
		}
		destroy = true;
		return (true);
	}
	return (false);
}

void FlameBlast::CreateFireBall()
{
	counter = 0;
	alpha = 0;
	Character *targ = gameState.battle.ground->map[targets[iterator].y][targets[iterator].x].character;
	int chance = GetChance(character, targ, ability);
	Character *hitTarg = RangedCheck(character, targ, chance);
	Character *used = hitTarg;
	if (hitTarg == NULL)
		used = targ;
	bool hit = (chance == 1) ? false : true;
	FireBall *ball = new FireBall(character, used->position, hit);
	t_FireBall add = {ball, used->position, false, false, hit};
	fireBalls.push_back(add);
}

void FlameBlast::UpdateFireBalls()
{
	for (int i = 0; i < fireBalls.size(); i++)
	{
		if (fireBalls[i].fireBall == NULL)
			continue ;
		fireBalls[i].fireBall->Update();
		if (fireBalls[i].fireBall->destroy)
		{
			fireBalls[i].atGoal = true;
			delete fireBalls[i].fireBall;
			fireBalls[i].fireBall = NULL;
		}
	}
}

void FlameBlast::Update()
{
	if (destroy)
		return ;
	if (CheckIfDone())
		return ;
	UpdateAura();
	UpdateFireBalls();
	if (counter >= LAUNCH_TIME && iterator < amount)
	{
		CreateFireBall();
		iterator++;
		if (iterator >= amount)
			character->sprite->setTexture(gameState.textures.chars.pyroIdle1);
	}
	counter++;
}

std::vector<t_HitReturn> &FlameBlast::GetTargets()
{
	retPoints.clear();
	for (int i = 0; i < fireBalls.size(); i++)
	{
		if (fireBalls[i].atGoal && !fireBalls[i].done)
		{
			fireBalls[i].done = true;
			retPoints.push_back({fireBalls[i].target, fireBalls[i].missing});
		}
	}
	return (retPoints);
}

void FlameBlast::Destroy()
{
	character->setAnimationActive(false);
	delete aura;
	for (int i = 0; i < fireBalls.size(); i++)
	{
		if (fireBalls[i].fireBall != NULL)
			delete fireBalls[i].fireBall;
	}
	fireBalls.clear();
}
