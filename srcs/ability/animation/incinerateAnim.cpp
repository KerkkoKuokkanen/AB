
#include "../../../hdr/global.h"
#define BALL_DIMENTIONS 5000
#define FLOAT_AMOUNT 500

void Incinerate::CreateSprite(t_IncinerateStruct &ball, Character *target)
{
	SDL_Point place = {target->sprite->dest.x + target->sprite->dest.w / 2, target->sprite->dest.y + target->sprite->dest.h / 2};
	SDL_Rect dest = {place.x - BALL_DIMENTIONS / 2, place.y - BALL_DIMENTIONS / 2 + FLOAT_AMOUNT, BALL_DIMENTIONS, BALL_DIMENTIONS};
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
	SDL_Rect used = {dest.x + 5000, dest.y + 2000, BALL_DIMENTIONS, BALL_DIMENTIONS};
	handBall = new Sprite(gameState.textures.attacks.incinerate[0], used, NULL, NULL, 0, FLIP_NONE);
	handBall->orderLayer = character->sprite->orderLayer;
	handBall->z = character->sprite->z + 0.25f;
	handBall->AlphaMod(0);
}

Incinerate::Incinerate(Character *character, std::vector<SDL_Point> &targets)
{
	if (targets.size() == 0)
	{
		done = true;
		return ;
	}
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
	counter = 0;
}

void Incinerate::UpdateHandBall()
{

}

void Incinerate::UpdateBalls()
{

}

void Incinerate::Update()
{
	if (done)
		return ;
	UpdateHandBall();
	UpdateBalls();
	counter++;
	if (counter > 180)
		done = true;
}

void Incinerate::Destroy()
{
	if (handBall != NULL)
		delete handBall;
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].ball != NULL)
			delete balls[i].ball;
		if (balls[i].aura != NULL)
			delete balls[i].aura;
	}
	balls.clear();
}
