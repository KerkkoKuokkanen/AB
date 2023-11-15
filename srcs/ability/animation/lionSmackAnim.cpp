
#include "../../../hdr/global.h"

Vector LionSmack::GetDirection()
{
	SDL_Point cPos = character->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

LionSmack::LionSmack(Character *character, SDL_Point target)
{
	LionSmack::character = character;
	LionSmack::target = target;
	character->setAnimationActive(true);
	mover = new CharacterMover(character, GetDirection(), 17, 17, 180.0f);
	PlaySound(gameState.audio.lionSmack, Channels::VOLUME_12, 0);
}

void LionSmack::CreateTrail()
{
	SDL_Rect dest = character->sprite->dest;
	trail = new Sprite(gameState.textures.attacks.lionTrail, dest, NULL, NULL, 0, FLIP_NONE);
	trail->z = character->sprite->z - 0.5f;
	trail->orderLayer = character->sprite->orderLayer;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
}

void LionSmack::UpdateTrail(int ret)
{
	if (ret < 7 || trail == NULL)
		return ;
	float unit = 255.0f / 30.0f;
	float multi = (float)ret - 7.0f;
	int alpha = 255 - rounding(unit * multi);
	trail->AlphaMod(alpha);
	trail->dest = character->sprite->dest;
}

void LionSmack::Update()
{
	if (done)
		return ;
	createDamage = false;
	int ret = mover->Update();
	UpdateTrail(ret);
	if (ret == 6)
	{
		character->sprite->Move(Vector(0.0f, -100.0f));
		character->sprite->setTexture(gameState.textures.chars.lionSmack);
		CreateTrail();
	}
	if (ret == 8)
		createDamage = true;
	if (ret == ANIMATION_DONE)
	{
		Vector use = gameState.battle.ground->GetCharacterCoord(character->position, character);
		character->sprite->Position(use);
		character->sprite->setTexture(gameState.textures.chars.lionIdle[0]);
		done = true;
	}
}

void LionSmack::Destroy()
{
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
	character->setAnimationActive(false);
}
