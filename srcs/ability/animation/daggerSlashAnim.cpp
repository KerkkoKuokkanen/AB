
#include "../../../hdr/global.h"

Vector DaggerSlashAnim::GetDirection()
{
	SDL_Point cPos = character->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

DaggerSlashAnim::DaggerSlashAnim(Character *character, SDL_Point target)
{
	PlaySound(gameState.audio.daggerSlash, Channels::DAGGER_SLASH, 0);
	character->setAnimationActive(true);
	DaggerSlashAnim::target = target;
	DaggerSlashAnim::character = character;
	mover = new CharacterMover(character, GetDirection(), 12, 12, 120.0f);
	daggerTrail = NULL;
}

void DaggerSlashAnim::CreateTrail()
{
	daggerTrail = new Sprite(gameState.textures.thiefSlash[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(daggerTrail, BATTLEGROUND_LAYER);
	daggerTrail->orderLayer = character->sprite->orderLayer;
	daggerTrail->setDepth(character->sprite->z + 1);
}

void DaggerSlashAnim::UpdateTrail()
{
	if (daggerTrail == NULL)
		return ;
	if (counter == 23)
	{
		delete daggerTrail;
		daggerTrail = NULL;
		return ;
	}
	int alphaIter = counter - 4;
	int alpha = 255 - 13 * alphaIter;
	daggerTrail->AlphaMod(alpha);
	daggerTrail->Position(Vector((float)character->sprite->dest.x, (float)character->sprite->dest.y));
}

void DaggerSlashAnim::Update()
{
	if (done)
		return ;
	createDamage = false;
	mover->Update();
	UpdateTrail();
	if (counter > 25)
	{
		done = true;
		Destroy();
	}
	if (counter == 6)
		createDamage = true;
	if (counter == 4)
	{
		character->sprite->setTexture(gameState.textures.thiefSlash[0]);
		character->sprite->dest.x += 400;
		character->sprite->dest.y += 100;
		CreateTrail();
	}
	if (counter == 23)
	{
		character->sprite->setTexture(gameState.textures.thiefIdle1);
		character->sprite->dest.x -= 400;
		character->sprite->dest.y -= 100;
	}
	counter++;
}

void DaggerSlashAnim::Destroy()
{
	character->setAnimationActive(false);
	if (daggerTrail != NULL)
		delete daggerTrail;
	if (mover != NULL)
		delete mover;
}
