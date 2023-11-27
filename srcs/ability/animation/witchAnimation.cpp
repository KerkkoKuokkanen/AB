
#include "../../../hdr/global.h"

void WitchAnimation::GetHandGlowSprite()
{
	SDL_Rect dest = character->sprite->dest;
	if (colorType == 0)
		glow = new Sprite(gameState.textures.attacks.glows[0], dest, NULL, NULL, 0, FLIP_NONE);
	else if (colorType == 1)
		glow = new Sprite(gameState.textures.attacks.glows[1], dest, NULL, NULL, 0, FLIP_NONE);
	else
		glow = new Sprite(gameState.textures.attacks.glows[2], dest, NULL, NULL, 0, FLIP_NONE);
	glow->orderLayer = character->sprite->orderLayer;
	glow->z = character->sprite->z - 0.02f;
	gameState.render->AddSprite(glow, BATTLEGROUND_LAYER);
}

WitchAnimation::WitchAnimation(Character *character, int colorType, int intensity)
{
	WitchAnimation::colorType = colorType;
	intensity = (intensity < 0) ? 0 : intensity;
	intensity = (intensity > 10) ? 10 : intensity;
	WitchAnimation::intensity = intensity;
	WitchAnimation::character = character;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.attacks.witchAttack);
	SDL_Rect dest = character->sprite->dest;
	aura[0] = new Sprite(gameState.textures.attacks.buffLight[0], dest, NULL, NULL, 0, FLIP_NONE);
	aura[1] = new Sprite(gameState.textures.attacks.buffLight[1], dest, NULL, NULL, 0, FLIP_NONE);
	aura[0]->orderLayer = character->sprite->orderLayer;
	aura[1]->orderLayer = character->sprite->orderLayer;
	aura[0]->z = character->sprite->z + 0.2f;
	aura[1]->z = character->sprite->z - 0.2f;
	gameState.render->AddSprite(aura[0], BATTLEGROUND_LAYER);
	gameState.render->AddSprite(aura[1], BATTLEGROUND_LAYER);
	GetHandGlowSprite();
}
