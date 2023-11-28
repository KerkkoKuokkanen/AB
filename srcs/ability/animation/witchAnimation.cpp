
#include "../../../hdr/global.h"
#define TIME 40
#define DEFAULT_PART_AMOUNT 30
#define PART_INCREASE 1

void WitchAnimation::GetHandGlowSprite()
{
	SDL_Rect dest = character->sprite->dest;
	if (colorType == 0)
		glow = new Sprite(gameState.textures.attacks.glows[2], dest, NULL, NULL, 0, FLIP_NONE);
	else if (colorType == 1)
		glow = new Sprite(gameState.textures.attacks.glows[0], dest, NULL, NULL, 0, FLIP_NONE);
	else
		glow = new Sprite(gameState.textures.attacks.glows[1], dest, NULL, NULL, 0, FLIP_NONE);
	glow->orderLayer = character->sprite->orderLayer;
	glow->z = character->sprite->z - 0.02f;
	gameState.render->AddSprite(glow, BATTLEGROUND_LAYER);
}

WitchAnimation::WitchAnimation(Character *character, int colorType, int intensity)
{
	PlaySound(gameState.audio.mageCast, Channels::MAGE_CAST, 0);
	WitchAnimation::colorType = colorType;
	intensity = (intensity < 0) ? 0 : intensity;
	intensity = (intensity > 10) ? 10 : intensity;
	WitchAnimation::intensity = intensity;
	WitchAnimation::character = character;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.attacks.witchAttack);
	SDL_Rect dest = character->sprite->dest;
	dest.y += 1200;
	dest.w -= 650;
	dest.x += 350;
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

void WitchAnimation::UpdateAuraAlpha()
{
	if (aura[0] == NULL || aura[1] == NULL)
		return ;
	float unit = 255.0f / 35.0f;
	float alpha = 255.0f - (unit * (float)counter);
	int used = rounding(alpha);
	if (used <= 0)
	{
		delete aura[0];
		delete aura[1];
		aura[0] = NULL;
		aura[1] = NULL;
		return ;
	}
	if (used > 255)
		used = 255;
	aura[0]->AlphaMod(used);
	aura[1]->AlphaMod(used);
}

SDL_Point WitchAnimation::GetPartPos()
{
	SDL_Rect dest = character->sprite->dest;
	SDL_Point ret = {dest.x + 1800, dest.y + 1200};
	return (ret);
}

Color WitchAnimation::GetPartColor()
{
	switch (colorType)
	{
		case WitchAnimationType::GREEN:
			return (Color(0, 130, 0));
		case WitchAnimationType::BLUE:
			return (Color(0, 0, 255));
		case WitchAnimationType::RED:
			return (Color(255, 0, 0));
	}
	return (Color(0, 0, 255));
}

void WitchAnimation::CreateParticles()
{
	SDL_Point place = GetPartPos();
	Color color = GetPartColor();
	int partAmount = DEFAULT_PART_AMOUNT + PART_INCREASE * intensity;
	for (int i = 0; i < partAmount; i++)
	{
		int xOffset = (rand() % 500) - 250;
		int yOffset = (rand() % 500) - 250;
		Vector dir(-1.0f, 0.0f);
		float angle = float_rand() * (PI / 4.0f);
		vectorRotate(dir, angle);
		Vector position((float)(place.x + xOffset), (float)(place.y + yOffset));
		float speed = rand() % 50 + 75;
		int life = rand() % 10 + 20;
		gameState.updateObjs.partManager->CreateModParticle(dir, position, speed, color, color, life, 1.04f, false, -0.05f);
	}
}

void WitchAnimation::Update()
{
	if (done)
		return ;
	UpdateAuraAlpha();
	if (counter == 8)
		CreateParticles();
	counter++;
	if (counter >= TIME)
		done = true;
}

void WitchAnimation::Destroy()
{
	if (glow != NULL)
		delete glow;
	if (aura[0] != NULL)
		delete aura[0];
	if (aura[1] != NULL)
		delete aura[1];
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.witchIdle[1]);
}
