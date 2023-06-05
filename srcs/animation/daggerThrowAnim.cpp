
#include "../../hdr/global.h"

DaggerThrowAnim::DaggerThrowAnim(Character *character, Character *enemy)
{
	DaggerThrowAnim::character = character;
	DaggerThrowAnim::enemy = enemy;
	character->setAnimationActive(true);
	SDL_FPoint cPoint = {
		(float)(character->sprite->dest.x + character->sprite->dest.w / 2),
		(float)(character->sprite->dest.y + character->sprite->dest.h / 2)
	};
	SDL_FPoint ePoint = {
		(float)(enemy->sprite->dest.x + enemy->sprite->dest.w / 2),
		(float)(enemy->sprite->dest.y + enemy->sprite->dest.h / 2)
	};
	Vector dir = Vector(ePoint.x -  cPoint.x, ePoint.y - cPoint.y).Normalized();
	direction = {dir.x, dir.y};
	if (direction.y < 0.0f)
		return ;
	SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(character);
	character->sprite->orderLayer = (pos.y + 1);
}

void DaggerThrowAnim::MoveToEnemy()
{
	int duration = DAGGER_THROW_ANIMATION_TIME / 2;
	float speed = (100.0f / ((float)(counter - duration + 1))) + 80.0f;
	character->sprite->Move(Vector(direction.x * speed, direction.y * speed));
}

void DaggerThrowAnim::MoveBack()
{
	if (!thrown)
	{
		thrown = true;
		PlaySound(gameState.audio.throwAnim, Channels::DAGGER_THROW_ANIM, 0);
		gameState.updateObjs.objectManager->AddObject(new Dagger(character, enemy, 80), DAGGER_OBJ);
		character->sprite->setTexture(gameState.textures.thiefDaggerThrow);
		character->sprite->Move(Vector(550.0f, 380.0f));
	}
	int duration = DAGGER_THROW_ANIMATION_TIME / 2;
	int time = counter;
	float speed = (100.0f / (float)time) + 80.0f;
	character->sprite->Move(Vector(-direction.x * speed, -direction.y * speed));
}

void DaggerThrowAnim::AnimationDone()
{
	SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(character);
	gameState.battle.ground->PlaceCharacter(pos, character);
	character->sprite->setTexture(gameState.textures.thiefIdle1);
	character->setAnimationActive(false);
	character->sprite->orderLayer = pos.y;
}

void DaggerThrowAnim::Update()
{
	if (counter <= 0)
	{
		active = false;
		return ;
	}
	if (counter >= (DAGGER_THROW_ANIMATION_TIME / 2))
		MoveToEnemy();
	else
		MoveBack();
	counter--;
	if (counter == 0)
		AnimationDone();
}
