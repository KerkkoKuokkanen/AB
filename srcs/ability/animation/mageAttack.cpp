
#include "../../../hdr/global.h"

MageAttack::MageAttack(Character *character)
{
	MageAttack::character = character;
	counter = 0;
	character->setAnimationActive(true);
}

void MageAttack::CreateLight()
{
	PlaySound(gameState.audio.mageCast, Channels::MAGE_CAST, 0);
	character->sprite->setTexture(gameState.textures.attacks.mageAttack);
	SDL_Rect dest = character->sprite->dest;
	dest.w -= 900;
	dest.x += 240;
	dest.y += 1550;
	light1 = new Sprite(gameState.textures.attacks.buffLight[0], dest, NULL, NULL, 0, FLIP_NONE);
	light2 = new Sprite(gameState.textures.attacks.buffLight[1], dest, NULL, NULL, 0, FLIP_NONE);
	light1->orderLayer = character->sprite->orderLayer;
	light1->z = character->sprite->z + 0.2f;
	light2->orderLayer = character->sprite->orderLayer;
	light2->z = character->sprite->z - 0.2f;
	gameState.render->AddSprite(light1, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(light2, BATTLEGROUND_LAYER);
	character->sprite->dest.x -= 100;
	character->sprite->dest.y += 200;
}

void MageAttack::UpdateLight()
{
	if (counter < 34)
		return ;
	if (light1 == NULL || light2 == NULL)
		return ;
	int count = counter - 34;
	float amount = 255.0f / 15.0f;
	float alpha = 255.0f - (amount * (float)count);
	if (alpha < 0.0f)
	{
		delete light1;
		delete light2;
		light1 = NULL;
		light2 = NULL;
		return ;
	}
	int alphaU = rounding(alpha);
	if (alphaU <= 0)
		alphaU = 1;
	if (alphaU > 255)
		alphaU = 255;
	light1->AlphaMod(alphaU);
	light2->AlphaMod(alphaU);
}

void MageAttack::Update()
{
	createEffect = false;
	if (done)
		return ;
	counter++;
	UpdateLight();
	if (counter == 6)
		CreateLight();
	if (counter == 8)
		createEffect = true;
	if (counter > 53)
		done = true;
}

void MageAttack::Destroy()
{
	character->sprite->setTexture(gameState.textures.chars.mageIdle[0]);
	gameState.battle.ground->PlaceCharacter(character->position, character);
	character->setAnimationActive(false);
	if (light1 != NULL)
		delete light1;
	if (light2 != NULL)
		delete light2;
}
