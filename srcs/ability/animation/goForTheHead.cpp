
#include "../../../hdr/global.h"

Vector GoForTheHead::GetDirection()
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return ((ret).Normalized());
}

GoForTheHead::GoForTheHead(Character *character, Character *target)
{
	GoForTheHead::character = character;
	GoForTheHead::target = target;
	character->setAnimationActive(true);
	Vector dir = GetDirection();
	mover = new CharacterMover(character, dir, 12, 12, 200.0f);
}

void GoForTheHead::UpdateTrail(int ret)
{
	if (trail == NULL)
		return ;
	trail->dest = character->sprite->dest;
	int count = ret - 5;
	if (count <= 4)
		return ;
	int newCount = count - 4;
	float unit = 255.0f / 14.0f;
	float alpha = 255.0f - (unit * (float)newCount);
	int used = rounding(alpha);
	if (used <= 0)
	{
		delete trail;
		trail = NULL;
		return ;
	}
	trail->AlphaMod(used);
}

void GoForTheHead::CreateTrail()
{
	PlaySound(gameState.audio.hammerSmack, Channels::HAMMER_SMACK, 0);
	character->sprite->setTexture(gameState.textures.attacks.smithHeadSmack[0]);
	trail = new Sprite(gameState.textures.attacks.smithHeadSmack[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z + 0.05f;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
}

void GoForTheHead::Update()
{
	createDamage = false;
	if (done)
		return ;
	if (counter >= 4)
	{
		int ret = mover->Update();
		if (ret == (-1))
		{
			done = true;
			return ;
		}
		UpdateTrail(ret);
		if (ret == 5)
			CreateTrail();
		if (ret == 7)
			createDamage = true;
		if (ret == 21)
		{
			character->sprite->setTexture(gameState.textures.chars.smithIdle[1]);
			character->setAnimationActive(false);
		}
	}
	if (counter > 200)
	{
		done = true;
		createDamage = true;
	}
	counter++;
}

void GoForTheHead::Destroy()
{
	character->setAnimationActive(false);
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
}
