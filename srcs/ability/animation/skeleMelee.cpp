
#include "../../../hdr/global.h"

static Vector GetDirection(Character *character, Character *target)
{
	SDL_Point cPos = character->position;
	SDL_Point tPos = target->position;
	SDL_Rect cDest = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect tDest = gameState.battle.ground->getTileDest(tPos);
	Vector ret((float)(tDest.x - cDest.x), (float)(tDest.y - cDest.y));
	return (ret);
}

SkeleMeleeAnim::SkeleMeleeAnim(Character *character, Character *target)
{
	SkeleMeleeAnim::character = character;
	SkeleMeleeAnim::target = target;
	character->setAnimationActive(true);
	Vector dir = GetDirection(character, target);
	mover = new SpriteMover(character->sprite, dir, 30, 90.0f);
	if (dir.y > 0.0f)
		orderDiff = 1;
	character->sprite->orderLayer += orderDiff;
}

void SkeleMeleeAnim::UpdateSprite(int ret)
{
	if (ret == 4)
	{
		PlaySound(gameState.audio.skeleMelee, Channels::VOLUME_12, 0);
		character->sprite->dest.y -= 600;
		character->sprite->dest.x -= 400;
		character->sprite->setTexture(gameState.textures.attacks.sekeleMelee);
	}
	if (ret == 25)
	{
		character->sprite->dest.y += 600;
		character->sprite->dest.x += 400;
		character->sprite->setTexture(gameState.textures.skeleIdle1);
		character->sprite->orderLayer -= orderDiff;
	}
}

void SkeleMeleeAnim::Update()
{
	createDamage = false;
	if (done)
		return ;
	int ret = mover->Update();
	UpdateSprite(ret);
	if (ret == 9)
		createDamage = true;
	if (ret == (-1))
	{
		delete mover;
		mover = NULL;
		character->setAnimationActive(false);
		done = true;
	}
}

void SkeleMeleeAnim::Destroy()
{
	character->setAnimationActive(false);
	if (mover != NULL)
		delete mover;
}
