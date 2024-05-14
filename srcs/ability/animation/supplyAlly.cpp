
#include "../../../hdr/global.h"

SupplyAlly::SupplyAlly(Character *character, Character *target)
{
	SupplyAlly::character = character;
	SupplyAlly::target = target;
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(target->position);
	character->setAnimationActive(true);
	Vector dir = Vector((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y)).Normalized();
	mover = new CharacterMover(character, dir, 12, 12, 250.0f);
}

void SupplyAlly::Update()
{
	removeFat = false;
	if (done)
		return ;
	int ret = mover->Update();
	if (ret == 10)
	{
		new SupplyEffect(target);
		removeFat = true;
	}
	if (ret == -1)
		done = true;
}

void SupplyAlly::Destroy()
{
	if (mover != NULL)
		delete mover;
	character->setAnimationActive(false);
}
