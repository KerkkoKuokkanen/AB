
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
		if (mover == NULL)
		{
			destroy = true;
			return (true);
		}
	}
	return (false);
}

void FlameBlast::IncrementIterator()
{
	iterator++;
	while (iterator < amount)
	{
		Character *ret = gameState.battle.ground->map[targets[iterator].y][targets[iterator].x].character;
		if (ret != NULL && !ret->killed)
			return ;
		iterator++;
	}
}

void FlameBlast::CreateFireBall()
{
	counter = 0;
	alpha = 0;
	Character *targ = gameState.battle.ground->map[targets[iterator].y][targets[iterator].x].character;
	if (targ == NULL)
		return ;
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

Vector FlameBlast::getDirection(bool bigDir)
{
	Vector ret(1.0f, 0.0f);
	float multi = (bigDir) ? 0.3f : 0.15f;
	float angle = float_rand() * (PI * multi);
	angle = (rand() % 2 == 0) ? angle : angle * (-1.0f);
	vectorRotate(ret, angle);
	return (ret);
}

Color FlameBlast::getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit < 55)
		return (Color(255, 24, 0));
	return (Color(209, 110, 0));
}

int FlameBlast::GetPartAmount()
{
	switch (counter)
	{
		case 8:
			return (2);
		case 16:
			return (5);
		case 24:
			return (10);
		case 32:
			return (80);
	}
	return (0);
}

void FlameBlast::CreateParticles()
{
	if (counter % 8 != 0 || iterator >= amount)
		return ;
	SDL_Rect dest = character->sprite->dest;
	int iter = GetPartAmount();
	bool beel = (iter == 80) ? true : false;
	for (int i = 0; i < iter; i++)
	{
		Vector dir = getDirection(beel);
		float speed = float_rand() * 80.0f + 90.0f;
		Color used = getColor();
		int life = rand() % 10 + 10;
		float add = (float_rand() - float_rand()) * 0.1f;
		float drag = 1.0f + float_rand() * 0.1f;
		if (iter == 80)
			life += rand() % 10 + 15;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)dest.x + 4900.0f,
											(float)dest.y + 2600.0f), speed, used, used, life, drag, false, add);
	}
}

void FlameBlast::UpdateMover()
{
	if (mover == NULL)
		return ;
	int ret = mover->Update();
	if (ret == ANIMATION_DONE)
	{
		delete mover;
		mover = NULL;
	}
}

void FlameBlast::Update()
{
	if (destroy)
		return ;
	if (CheckIfDone())
		return ;
	CreateParticles();
	UpdateMover();
	UpdateAura();
	UpdateFireBalls();
	if (counter == 35 && iterator < amount)
		PlaySound(gameState.audio.flameBlast[2], Channels::FLAME_BLAST_LAUNCH, 0);
	if (counter >= LAUNCH_TIME && iterator < amount)
	{
		CreateFireBall();
		SetScreenShake(400, 4);
		IncrementIterator();
		if (iterator >= amount)
			character->sprite->setTexture(gameState.textures.chars.pyroIdle1);
		mover = new CharacterMover(character, Vector(-0.5f, -0.5f), 6, 6, 200.0f);
	}
	if (counter == 0 && iterator < amount)
		PlaySound(gameState.audio.flameBlast[1], Channels::FLAME_BLAST_CHARGE, 0);
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
	if (mover != NULL)
		delete mover;
	for (int i = 0; i < fireBalls.size(); i++)
	{
		if (fireBalls[i].fireBall != NULL)
			delete fireBalls[i].fireBall;
	}
	fireBalls.clear();
}
