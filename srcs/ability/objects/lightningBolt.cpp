
#include "../../../hdr/global.h"
#define DONE 45

static Color getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit > 70)
		return (Color(50, 197, 227));
	if (hit > 50)
		return (Color(131, 223, 242));
	return (Color(0, 147, 232));
}

LightningBolt::LightningBolt(SDL_Point target)
{
	PlaySound(gameState.audio.lightning, Channels::VOLUME_19, 0);
	LightningBolt::target = target;
	SDL_Rect dest = gameState.battle.ground->getTileDest(target);
	SDL_Rect used = {dest.x - 530, dest.y - 10700, 2400, 11000};
	sprite = new Sprite(gameState.textures.attacks.lightning, used, NULL, NULL, -23, FLIP_NONE);
	Character *ret = gameState.battle.ground->map[target.y][target.x].character;
	sprite->orderLayer = ret->sprite->orderLayer;
	sprite->z = ret->sprite->z + 1.0f;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	SetScreenShake(500, 7);
}

void LightningBolt::UpdateAlpha()
{
	if (counter < 30)
		return ;
	float unit = 255.0f / 13.0f;
	int count = counter - 30;
	float alpha = 255.0f - unit * (float)count;
	int used = rounding(alpha);
	if (used < 0)
		used = 0;
	if (used > 255)
		used = 255;
	sprite->AlphaMod(used);
}

void LightningBolt::MoveLightning()
{
	SDL_Rect dest = sprite->dest;
	dest.x += 10;
	dest.y += 10;
	sprite->dest = dest;
}

void LightningBolt::CreateParticles()
{
	SDL_Point place = {sprite->dest.x + 3300, sprite->dest.y + 9700};
	for (int i = 0; i < 240; i++)
	{
		Vector dir(0.0f, -1.0f);
		float angle = float_rand() * PI;
		angle = (rand() % 2 == 0) ? angle : -angle;
		vectorRotate(dir, angle);
		float speed = float_rand() * 80.0f + 80.0f;
		Color used = getColor();
		int life = rand() % 10 + 55;
		float drag = 1.0f + float_rand() * 0.1f;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)place.x, (float)place.y), speed, used,
																							used, life, drag, false);
	}
}

void LightningBolt::Update()
{
	createDamage = false;
	if (done)
		return ;
	UpdateAlpha();
	MoveLightning();
	if (counter == 0)
		CreateParticles();
	if (counter == 4)
		createDamage = true;
	counter++;
	if (counter >= 45)
		done = true;
}

void LightningBolt::Destroy()
{
	delete sprite;
}
