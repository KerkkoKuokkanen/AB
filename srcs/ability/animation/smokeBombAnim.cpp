
#include "../../../hdr/global.h"

SmokeBombAnim::SmokeBombAnim(Character *character, SDL_Point pos)
{
	SmokeBombAnim::character = character;
	SmokeBombAnim::pos = pos;
	character->setAnimationActive(true);
	SDL_Point cPos = character->position;
	SDL_Rect cDest = gameState.battle.ground->GetSprite(cPos)->dest;
	SDL_Rect sDest = gameState.battle.ground->GetSprite(pos)->dest;
	Vector dir(sDest.x - cDest.x, sDest.y - cDest.y);
	mover = new CharacterMover(character, dir, 9, 9, 80.0f, true);
	if (character->position.y == pos.y && character->position.x == pos.x)
		return ;
	if (dir.y < 0.0f)
		return ;
	SDL_Point position = character->position;
	character->sprite->orderLayer = position.y + 1;
}

void SmokeBombAnim::SetThrowText()
{
	PlaySound(gameState.audio.smokeThrow, Channels::SMOKE_THROW, 0);
	character->sprite->setTexture(gameState.textures.thiefSmokeThrow[0]);
	trail = new Sprite(gameState.textures.thiefSmokeThrow[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	SDL_Point position = character->position;
	trail->orderLayer = position.y;
	trail->setDepth(character->sprite->z - 1);
}

void SmokeBombAnim::RemoveAnimText()
{
	character->sprite->setTexture(gameState.textures.thiefIdle1);
}

void SmokeBombAnim::Update()
{
	timeForAbility = false;
	mover->Update();
	if (counter == 20)
	{
		if (active)
			AnimationDone();
		return ;
	}
	if (counter == 6)
		timeForAbility = true;
	if (counter == 4)
		SetThrowText();
	if (counter > 4 && alpha > 0)
	{
		SDL_Rect dest = character->sprite->dest;
		trail->Position(Vector(dest.x, dest.y));
		alpha -= 25;
		if (alpha < 0)
			alpha = 0;
		trail->AlphaMod((Uint8)alpha);
		if (alpha == 0)
		{
			delete trail;
			trail = NULL;
		}
	}
	if (counter == 13)
		RemoveAnimText();
	counter++;
}

void SmokeBombAnim::AnimationDone()
{
	SDL_Point position = character->position;
	character->sprite->orderLayer = position.y;
	character->setAnimationActive(false);
	active = false;
}

void SmokeBombAnim::Destroy()
{
	if (mover != NULL)
		delete mover;
	if (trail != NULL)
		delete trail;
}
