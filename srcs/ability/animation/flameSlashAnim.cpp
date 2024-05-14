
#include "../../../hdr/global.h"

Vector FlameSlash::GetDirection()
{
	SDL_Point cPos = character->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

FlameSlash::FlameSlash(Character *character, SDL_Point target)
{
	PlaySound(gameState.audio.flameSlash, Channels::FLAME_SLASH, 0);
	character->setAnimationActive(true);
	FlameSlash::target = target;
	FlameSlash::character = character;
	mover = new CharacterMover(character, GetDirection(), 12, 12, 120.0f);
	trail = NULL;
}

void FlameSlash::CreateTrail()
{
	trail = new Sprite(gameState.textures.chars.flameSlash[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	trail->orderLayer = character->sprite->orderLayer;
	trail->setDepth(character->sprite->z + 1);
}

void FlameSlash::UpdateTrail()
{
	if (trail == NULL)
		return ;
	if (counter == 23)
	{
		delete trail;
		trail = NULL;
		return ;
	}
	if (counter >= 18)
	{
		int alphaIter = counter - 17;
		int alpha = 255 - 40 * alphaIter;
		trail->AlphaMod(alpha);
	}
	trail->Position(Vector((float)character->sprite->dest.x, (float)character->sprite->dest.y));
}

void FlameSlash::Update()
{
	if (done)
		return ;
	createDamage = false;
	mover->Update();
	UpdateTrail();
	if (counter > 25)
		done = true;
	if (counter == 6)
		createDamage = true;
	if (counter == 4)
	{
		character->sprite->setTexture(gameState.textures.chars.flameSlash[0]);
		character->sprite->Move(Vector(180.0f, -250.0f));
		CreateTrail();
	}
	if (counter == 23)
	{
		character->sprite->setTexture(gameState.textures.chars.pyroIdle1);
		character->sprite->Move(Vector(-180.0f, 250.0f));
	}
	counter++;
}

void FlameSlash::Destroy()
{
	character->setAnimationActive(false);
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
}
