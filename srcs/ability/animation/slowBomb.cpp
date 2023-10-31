
#include "../../../hdr/global.h"
#define NAIL_AMOUNT 120
#define PARTICLE_AMOUNT 500
#define MAX_SPEED 400.0f

static Vector GetDirection(SDL_Point cPoint, SDL_Point tPoint)
{
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(cPoint);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(tPoint);
	Vector dir((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y));
	dir = dir.Normalized();
	return (dir);
}

static Vector GetDirectionForParts()
{
	Vector dir(0.0f, -1.0f);
	float angle = (rand() % 2 == 0) ? float_rand() * PI : -float_rand() * PI;
	vectorRotate(dir, angle);
	return (dir);
}

static float GetSpeed(Vector dir)
{
	Vector aVec(1.0f, 0.0f);
	if (dir.x < 0.0f)
		aVec.x = -1.0f;
	float angle = (PI * 0.5f) - vectorAngle(aVec, dir);
	if (angle < (PI * 0.1f))
		angle = (PI * 0.1f);
	float unit = MAX_SPEED / (PI * 0.5f);
	float speec = unit * angle;
	return (speec + 100.0f + (float)(rand() % 80));
}

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 75)
		return (Color(12, 29, 156));
	if (hit > 43)
		return (Color(65, 80, 196));
	if (hit > 9)
		return (Color(31, 77, 107));
	return (Color(4, 28, 43));
}

SlowBomb::SlowBomb(Character *character, SDL_Point target, t_Ability *ability)
{
	SlowBomb::character = character;
	SlowBomb::target = target;
	SlowBomb::ability = ability;
	character->setAnimationActive(true);
	Vector moverDirection = GetDirection(character->position, target);
	if (moverDirection.x < 0.0f)
		angleAddition = -angleAddition;
	mover = new CharacterMover(character, moverDirection, 12, 12, 200.0f);
}

static float GetHeightForThrow(SDL_Point start, SDL_Point end)
{
	Vector mag((float)(end.x - start.x), (float)(end.y - start.y));
	float magnitude = mag.Magnitude();
	if (magnitude < 6000.0f)
		return (3500.0f);
	if (magnitude > 18000.0f)
		return (15000.0f);
	float unit = 14000.0f / 18000.0f;
	float amount = unit * magnitude;
	return (amount);
}

void SlowBomb::StartThrow()
{
	PlaySound(gameState.audio.toolThrow, Channels::TOOL_THROW, 0);
	character->sprite->dest.x += 200;
	character->sprite->setTexture(gameState.textures.attacks.alchemistThrow[0]);
	trail = new Sprite(gameState.textures.attacks.alchemistThrow[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z - 0.04f;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	bombCreated = true;
	SDL_Rect bombDest = {character->sprite->dest.x + 4700, character->sprite->dest.y + 1600, 1600, 1600};
	bomb = new Sprite(gameState.textures.attacks.bombs[2], bombDest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(bomb, OBJECT_LAYER);
	SDL_Rect dst = gameState.battle.ground->getTileDest(target);
	dst.x += 1800;
	dst.y += 1200;
	arch = new ThrowArch(bomb, {bomb->dest.x, bomb->dest.y}, {dst.x, dst.y},
						GetHeightForThrow({bomb->dest.x, bomb->dest.y}, {dst.x, dst.y}), 360.0f);
}

void SlowBomb::CreateParticles()
{
	t_SlowBomb *used = (t_SlowBomb*)ability->stats;
	int version = used->version;
	float unit = 0.5f / 10.0f;
	float amountMulti = 1.0f - (unit * version);
	float speedMulti = 1.1f - (unit * version);
	int amount = (int)(PARTICLE_AMOUNT * amountMulti);
	SDL_Point pos = {bomb->dest.x + 800, bomb->dest.y - 1000};
	for (int i = 0; i < amount; i++)
	{
		int xAdd = (rand() % 150) - (rand() % 150);
		int yAdd = (rand() % 150) - (rand() % 150);
		Vector dir = GetDirectionForParts();
		float drag = 1.07f + float_rand() * 0.1f;
		float speed = (rand() % 6 == 0) ? (float)(rand() % 550 + 50) * speedMulti : GetSpeed(dir) * 1.3f * speedMulti;
		Vector place((float)(pos.x + xAdd), (float)(pos.y + yAdd));
		int life = rand() % 20 + 33;
		int sizeRand = rand() % 200 + 200;
		Color used = GetColor();
		gameState.updateObjs.partManager->CreateModParticleWithTexture(gameState.textures.KillParticle[0],
										dir, place, speed, used, used, life, drag, false, 0.04f, {0, 0, sizeRand, sizeRand});
	}
}

void SlowBomb::UpdateBomb()
{
	if (bomb == NULL)
		return ;
	if (arch == NULL)
		return ;
	arch->Update();
	bomb->addAngle(angleAddition);
	if (arch->done)
	{
		PlaySound(gameState.audio.slowBomb[0], Channels::VOLUME_60, 0);
		PlaySound(gameState.audio.slowBomb[1], Channels::VOLUME_128, 0);
		PlaySound(gameState.audio.acidBomb[2], Channels::VOLUME_22, 0);
		SetScreenShake(200, 6);
		CreateParticles();
		delete arch;
		delete bomb;
		arch = NULL;
		bomb = NULL;
	}
}

void SlowBomb::UpdateTrail(int ret)
{
	if (trail == NULL)
		return ;
	trail->dest = character->sprite->dest;
	int count = ret - 5;
	if (count == 17)
	{
		delete trail;
		trail = NULL;
		character->sprite->setTexture(gameState.textures.chars.AlchemistIdle[0]);
		return ;
	}
	float unit = 255.0f / 17.0f;
	float alpha	= 255.0f - unit * (float)count;
	int used = rounding(alpha);
	trail->AlphaMod(used);
}

void SlowBomb::UpdateMover()
{
	if (mover == NULL)
		return ;
	int ret = mover->Update();
	UpdateTrail(ret);
	if (ret == 5)
		StartThrow();
	if (ret == (-1))
	{
		delete mover;
		mover = NULL;
		character->sprite->setTexture(gameState.textures.chars.AlchemistIdle[0]);
		character->setAnimationActive(false);
	}
}

void SlowBomb::Update()
{
	createDamage = false;
	if (done)
		return ;
	if (bombCreated && bomb == NULL && damageCreated == false)
	{
		createDamage = true;
		damageCreated = true;
	}
	if (CheckIfDone())
	{
		done = true;
		return ;
	}
	UpdateMover();
	UpdateBomb();
	counter++;
	if (counter > 300)
	{
		done = true;
		createDamage = true;
	}
}

bool SlowBomb::CheckIfDone()
{
	if (mover == NULL && arch == NULL && bomb == NULL)
		return (true);
	return (false);
}

void SlowBomb::Destroy()
{
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
	if (arch != NULL)
		delete arch;
	if (bomb != NULL)
		delete bomb;
	character->setAnimationActive(false);
}