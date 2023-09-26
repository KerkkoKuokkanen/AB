
#include "../../../hdr/global.h"

HostEyesAnim::HostEyesAnim(Character *character, Character *target)
{
	HostEyesAnim::character = character;
	HostEyesAnim::target = target;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.attacks.hostEyes);
}

void HostEyesAnim::Update()
{
	createEffect = false;
	if (done)
		return ;
	counter++;
	if (counter > 60)
		done = true;
}

void HostEyesAnim::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.mageIdle[0]);
}
