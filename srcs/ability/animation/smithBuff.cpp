
#include "../../../hdr/global.h"

SmithBuff::SmithBuff(Character *character, Character *target)
{
	SmithBuff::character = character;
	SmithBuff::target = target;
	counter = 0;
	character->setAnimationActive(true);
}

void SmithBuff::CreateLight()
{
	character->sprite->setTexture(gameState.textures.attacks.smithBuff);
	SDL_Rect dest = character->sprite->dest;
	dest.x -= 50;
	dest.y += 1370;
	lights[0] = new Sprite(gameState.textures.attacks.buffLight[0], dest, NULL, NULL, 0, FLIP_NONE);
	lights[1] = new Sprite(gameState.textures.attacks.buffLight[1], dest, NULL, NULL, 0, FLIP_NONE);
	lights[0]->orderLayer = character->sprite->orderLayer;
	lights[0]->z = character->sprite->z + 0.2f;
	//lights[0]->ColorMod(23, 96, 255);
	lights[0]->ColorMod(199, 60, 22);
	lights[1]->orderLayer = character->sprite->orderLayer;
	lights[1]->z = character->sprite->z - 0.2f;
	//lights[1]->ColorMod(23, 96, 255);
	lights[1]->ColorMod(199, 60, 22);
	gameState.render->AddSprite(lights[0], BATTLEGROUND_LAYER);
	gameState.render->AddSprite(lights[1], BATTLEGROUND_LAYER);
}

void SmithBuff::UpdateLight()
{
	if (counter < 30)
		return ;
	int count = counter - 30;
	float amount = 255.0f / 15.0f;
	float alpha = 255.0f - (amount * (float)count);
	if (alpha < 0.0f)
	{
		delete lights[0];
		delete lights[1];
		lights[0] = NULL;
		lights[1] = NULL;
		return ;
	}
	int alphaU = rounding(alpha);
	if (alphaU <= 0)
		alphaU = 1;
	if (alphaU > 255)
		alphaU = 255;
	lights[0]->AlphaMod(alphaU);
	lights[1]->AlphaMod(alphaU);
}

void SmithBuff::Update()
{
	if (done)
		return ;
	counter++;
	UpdateLight();
	if (counter == 6)
		CreateLight();
	if (counter > 46)
		done = true;
}

void SmithBuff::Destroy()
{
	character->sprite->setTexture(gameState.textures.chars.smithIdle[0]);
	character->setAnimationActive(false);
	if (lights[0] != NULL)
		delete lights[0];
	if (lights[1] != NULL)
		delete lights[1];
}
