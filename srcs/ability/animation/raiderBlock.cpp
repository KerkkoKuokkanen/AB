
#include "../../../hdr/global.h"
#define ABILITY_TIME 70

RaiderBlock::RaiderBlock(Character *character)
{
	RaiderBlock::character = character;
	character->setAnimationActive(true);
	PlaySound(gameState.audio.raiderBlock, Channels::VOLUME_25, 0);
}

void RaiderBlock::Update()
{
	createBuff = false;
	if (done)
		return ;
	if (counter == 5)
	{
		character->sprite->setTexture(gameState.textures.attacks.raiderBlock);
		new BuffEffect(character, true);
	}
	if (counter == 20)
		createBuff = true;
	counter++;
	if (counter > ABILITY_TIME)
		done = true;
}

void RaiderBlock::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.raiderIdle[0]);
}
