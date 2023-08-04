
#include "../../../hdr/global.h"
#define BALL_DIMENTIONS 4000
#define FLOAT_AMOUNT 800.0f
#define HAND_BALL_FLOAT_AMOUNT 100.0f
#define ALPHA_TIME 26
#define PARTICLE_AMOUNT 280
#define FADE_START 156
#define SECOND_PHASE 140

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit >= 90)
		return (Color(20, 8, 1));
	if (hit < 45)
		return (Color(214, 89, 0));
	return (Color(219, 40, 0));
}

void Incinerate::CreateSprite(t_IncinerateStruct &ball, Character *target)
{
	SDL_Point place = {target->sprite->dest.x + target->sprite->dest.w / 2, target->sprite->dest.y + (int)((float)target->sprite->dest.h * 0.4)};
	SDL_Rect dest = {place.x - BALL_DIMENTIONS / 2, place.y - BALL_DIMENTIONS / 2 + (int)FLOAT_AMOUNT, BALL_DIMENTIONS, BALL_DIMENTIONS};
	ball.ball = new Sprite(gameState.textures.attacks.incinerate[0], dest, NULL, NULL, 0, FLIP_NONE);
	ball.aura = new Sprite(gameState.textures.attacks.incinerate[1], dest, NULL, NULL, 0, FLIP_NONE);
	ball.ball->AlphaMod(0);
	ball.ball->orderLayer = target->sprite->orderLayer;
	ball.ball->z = target->sprite->z + 0.5f;
	ball.aura->AlphaMod(0);
	ball.aura->orderLayer = target->sprite->orderLayer;
	ball.aura->z = target->sprite->z + 0.25f;
	gameState.render->AddSprite(ball.ball, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(ball.aura, BATTLEGROUND_LAYER);
}

void Incinerate::CreateHandBall()
{
	SDL_Rect dest = character->sprite->dest;
	SDL_Rect used = {dest.x + 4100, dest.y + 1960, 1600, 1600};
	handBall = new Sprite(gameState.textures.attacks.incinerate[0], used, NULL, NULL, 0, FLIP_NONE);
	handBall->orderLayer = character->sprite->orderLayer;
	handBall->z = character->sprite->z + 0.25f;
	handBall->AlphaMod(0);
	gameState.render->AddSprite(handBall, BATTLEGROUND_LAYER);
}

Incinerate::Incinerate(Character *character, std::vector<SDL_Point> &targets)
{
	if (targets.size() == 0)
	{
		done = true;
		return ;
	}
	PlaySound(gameState.audio.incinerate[0], Channels::INCINERATE_CHARGE, 0);
	PlaySound(gameState.audio.incinerate[1], Channels::INCINERATE_SPIN, 0);
	Incinerate::character = character;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.chars.pyroAttack[0]);
	for (int i = 0; i < targets.size(); i++)
	{
		SDL_Point pos = targets[i];
		Character *targ = gameState.battle.ground->map[pos.y][pos.x].character;
		t_IncinerateStruct add;
		if (targ != NULL)
			CreateSprite(add, targ);
		add.pos = pos;
		balls.push_back(add);
	}
	CreateHandBall();
	counter = 0;
}

void Incinerate::HandleSpriteAlpha(Sprite *sprite)
{
	float unit = 255.0f / (float)ALPHA_TIME;
	int alpha = rounding(unit * (float)counter);
	if (alpha > 255)
		alpha = 255;
	sprite->AlphaMod(alpha);
}

void Incinerate::MoveHandBall()
{
	float unit = HAND_BALL_FLOAT_AMOUNT / (float)ALPHA_TIME;
	handBall->Move(Vector(0.0f, -unit));
}

void Incinerate::RotateSprite(Sprite *sprite)
{
	float rotateSpeed = (float)counter * ((float)counter * 0.25f);
	sprite->setAngle(rotateSpeed);
}

void Incinerate::UpdateHandBall()
{
	if (secondPhase)
		return ;
	if (counter <= ALPHA_TIME)
	{
		HandleSpriteAlpha(handBall);
		MoveHandBall();
	}
	else
		handBall->ClearAlphaMod();
	RotateSprite(handBall);
}

void Incinerate::MoveABall(Sprite *sprite)
{
	float unit = FLOAT_AMOUNT / (float)ALPHA_TIME;
	sprite->Move(Vector(0.0f, -unit));
}

void Incinerate::HandleAuraAlpha(Sprite *sprite)
{
	if (counter <= ALPHA_TIME)
		return ;
	float unit = 255.0f / (float)alphaMod;
	int alpha = 0;
	if (!everyOther)
		alpha = rounding(unit * (float)alphaCount);
	else
		alpha = rounding(unit * (float)(alphaMod - alphaCount));
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	sprite->AlphaMod(alpha);
	alphaCount++;
	if (alphaCount < alphaMod)
		return ;
	everyOther = (everyOther) ? false : true;
	alphaCount = 0;
	alphaMod -= 3;
	if (alphaMod < 4)
		alphaMod = 4;
}

void Incinerate::CreateBallParticles(Sprite *ball)
{
	if (counter <= ALPHA_TIME)
		return ;
	if (counter % 16 != 0)
		return ;
	SDL_Point genPlace = {ball->dest.x + ball->dest.w / 2, ball->dest.y + ball->dest.h / 2};
	for (int i = 0; i < ballPartAmount; i++)
	{
		int xAdd = rand() % 200 - 100;
		int yAdd = rand() % 200 - 100;
		float angle = float_rand() * (PI * 2.0f);
		Vector dir(0.0f, 1.0f);
		vectorRotate(dir, angle);
		float drag = 1.06f + float_rand() * 0.1f;
		float speed = rand() % 80 + 80;
		Vector place((float)(genPlace.x + xAdd), (float)(genPlace.y + yAdd));
		int life = rand() % 40 + 8;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), Color(1, 1, 1), life, drag, false);
	}
}

void Incinerate::UpdateBalls()
{
	if (secondPhase)
		return ;
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].aura->dest = balls[i].ball->dest;
		if (counter <= ALPHA_TIME)
		{
			HandleSpriteAlpha(balls[i].ball);
			MoveABall(balls[i].ball);
		}
		CreateBallParticles(balls[i].ball);
		HandleAuraAlpha(balls[i].aura);
		RotateSprite(balls[i].ball);
	}
	if (counter % 20 == 0)
		ballPartAmount += ballPartAmount / 2;
}

void Incinerate::RemoveExplosions()
{
	for (int i = 0; i < explosions.size(); i++)
		delete explosions[i];
	explosions.clear();
}

void Incinerate::ExplosionAngle()
{
	int count = counter - SECOND_PHASE;
	if (count == 0)
		count = 1;
	float angleAdd = 5.0f / (1.05f * ((float)count * 0.4f));
	for (int i = 0; i < explosions.size(); i++)
	{
		explosions[i]->addAngle(angleAdd);
	}
}

void Incinerate::UpdateExplosions()
{
	if (!secondPhase)
		return ;
	if (explosions.size() == 0)
		return ;
	ExplosionAngle();
	if (counter <= FADE_START)
		return ;
	int count = counter - FADE_START;
	float unit = 255.0f / 40.0f;
	int alpha = 255 - rounding(unit * (float)(count));
	if (count >= 39)
	{
		RemoveExplosions();
		return ;
	}
	float amount = (float)count * ((float)count * 0.3f);
	int adder = rounding(amount * 0.5f);
	for (int i = 0; i < explosions.size(); i++)
	{
		SDL_Rect dest = explosions[i]->dest;
		dest = {dest.x + adder, dest.y + adder, dest.h - (int)amount, dest.w - (int)amount};
		explosions[i]->dest = dest;
		explosions[i]->AlphaMod(alpha);
	}
}

void Incinerate::UpdateHandParts()
{
	if (!secondPhase)
		return ;
	if (counter <= FADE_START)
		return ;
	if (handParts == NULL)
		return ;
	int count = counter - FADE_START;
	float unit = 255.0f / 40.0f;
	int alpha = 255 - rounding(unit * (float)(count));
	if (count >= 39)
	{
		delete handParts;
		handParts = NULL;
		return ;
	}
	handParts->AlphaMod(alpha);
}

void Incinerate::Update()
{
	createDamage = false;
	if (done)
		return ;
	UpdateHandBall();
	UpdateBalls();
	UpdateHandParts();
	UpdateExplosions();
	counter++;
	if (counter == SECOND_PHASE - 7)
	{
		PlaySound(gameState.audio.incinerate[2], Channels::INCINERATE_EXP, 0);
		PlaySound(gameState.audio.incinerate[3], Channels::INCINERATE_MOLO, 0);
	}
	if (counter == SECOND_PHASE)
		StartSecondPhase();
	if (counter == SECOND_PHASE + 8)
		createDamage = true;
	if (counter >= 200)
		done = true;
}

void Incinerate::StartSecondPhase()
{
	secondPhase = true;
	PlaySound(gameState.audio.incinerate[4], Channels::INCINERATE_EXP_SOUND, 0);
	SetScreenShake(500, 6);
	CreateExplosions();
	CreateHandParticles();
	character->sprite->setTexture(gameState.textures.chars.pyroAttack[1]);
	handParts = new Sprite(gameState.textures.chars.pyroAttackParts, character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	handParts->orderLayer = character->sprite->orderLayer;
	handParts->z = character->sprite->z;
	gameState.render->AddSprite(handParts, BATTLEGROUND_LAYER);
	if (handBall != NULL)
		delete handBall;
	handBall = NULL;
}

void Incinerate::CreateHandParticles()
{
	SDL_Point genPlace = {character->sprite->dest.x + 4400, character->sprite->dest.y + 2100};
	for (int i = 0; i < 40; i++)
	{
		int xAdd = rand() % 200 - 100;
		int yAdd = rand() % 200 - 100;
		float angle = float_rand() * (PI * 2.0f);
		Vector dir(0.0f, 1.0f);
		vectorRotate(dir, angle);
		float drag = 1.06f + float_rand() * 0.1f;
		float speed = rand() % 80 + 80;
		Vector place((float)(genPlace.x + xAdd), (float)(genPlace.y + yAdd));
		int life = rand() % 10 + 40;
		float yAdder = -float_rand() * 0.04f;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), Color(1, 1, 1), life, drag, false, yAdder);
	}
}

void Incinerate::CreateParticles(SDL_Rect dest)
{
	SDL_Point genPlace = {dest.x + dest.w / 2, dest.y + dest.h / 2};
	for (int i = 0; i < PARTICLE_AMOUNT; i++)
	{
		int xAdd = rand() % 1500 - 750;
		int yAdd = rand() % 1500 - 750;
		float angle = float_rand() * (PI * 2.0f);
		Vector dir(0.0f, 1.0f);
		vectorRotate(dir, angle);
		float drag = 1.0f + float_rand() * 0.1f;
		float speed = rand() % 150 + 150;
		Vector place((float)(genPlace.x + xAdd), (float)(genPlace.y + yAdd));
		int life = rand() % 10 + 60;
		float yAdder = (float_rand() - float_rand()) * 0.01f;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), Color(1, 1, 1), life, drag, false, yAdder);
	}
}

void Incinerate::CreateExplosions()
{
	for (int i = 0; i < balls.size(); i++)
	{
		SDL_Rect rect = balls[i].ball->dest;
		CreateParticles(rect);
		SDL_Rect dest = {rect.x - 1000, rect.y - 1000, rect.w + 2000, rect.h + 2000};
		Sprite *exp = new Sprite(gameState.textures.attacks.incExplosion, dest, NULL, NULL, 0, FLIP_NONE);
		exp->orderLayer = balls[i].ball->orderLayer;
		exp->z = balls[i].ball->z;
		gameState.render->AddSprite(exp, BATTLEGROUND_LAYER);
		explosions.push_back(exp);
		delete balls[i].ball;
		delete balls[i].aura;
	}
	balls.clear();
}

void Incinerate::Destroy()
{
	if (handBall != NULL)
		delete handBall;
	if (handParts != NULL)
		delete handParts;
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].ball != NULL)
			delete balls[i].ball;
		if (balls[i].aura != NULL)
			delete balls[i].aura;
	}
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i] != NULL)
			delete explosions[i];
	}
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.pyroIdle1);
}
