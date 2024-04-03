
#include "../../../hdr/global.h"
# define BUFF_TIME 50
# define X_ADD 80
# define Y_ADD 350

BigThugInspire::BigThugInspire(Character *character)
{
	PlaySound(gameState.audio.mageCast, Channels::MAGE_CAST, 0);
	BigThugInspire::character = character;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.attacks.bigThugBuff);
	character->sprite->dest.x -= X_ADD;
	character->sprite->dest.y -= Y_ADD;
	SDL_Rect dest = character->sprite->dest;
	dest.y += 1500;
	dest.x += 600;
	dest.w -= 500;
	buffLights[0] = new Sprite(gameState.textures.attacks.buffLight[0], dest, NULL, NULL, 0, FLIP_NONE);
	buffLights[1] = new Sprite(gameState.textures.attacks.buffLight[1], dest, NULL, NULL, 0, FLIP_NONE);
	buffLights[0]->orderLayer = character->sprite->orderLayer;
	buffLights[0]->z = character->sprite->z + 0.2f;
	buffLights[1]->orderLayer = character->sprite->orderLayer;
	buffLights[1]->z = character->sprite->z - 0.2f;
	gameState.render->AddSprite(buffLights[0], BATTLEGROUND_LAYER);
	gameState.render->AddSprite(buffLights[1], BATTLEGROUND_LAYER);
	counter = 0;
	done = false;
	createBuff = false;
}

void BigThugInspire::ManageAlpha()
{
	if (buffLights[0] == NULL)
		return ;
	if (counter < 18)
		return ;
	int count = counter - 18;
	float unit = 255.0f / 30.0f;
	float amount = 255.0f - (unit * (float)count);
	int use = rounding(amount);
	if (use < 5)
	{
		delete buffLights[0];
		delete buffLights[1];
		buffLights[0] = NULL;
		buffLights[1] = NULL;
		return ;
	}
	buffLights[0]->AlphaMod(use);
	buffLights[1]->AlphaMod(use);
}

void BigThugInspire::Update()
{
	createBuff = false;
	if (done)
		return ;
	ManageAlpha();
	if (counter == 13)
		createBuff = true;
	if (counter > BUFF_TIME)
		done = true;
	counter++;
}

void BigThugInspire::Destroy()
{
	if (buffLights[0] != NULL)
		delete buffLights[0];
	if (buffLights[1] != NULL)
		delete buffLights[1];
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.bigThugIdle[0]);
	character->sprite->dest.x += X_ADD;
	character->sprite->dest.y += Y_ADD;
}
