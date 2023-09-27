
#include "../../hdr/global.h"
#define TIME 35

static Color getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit > 70)
		return (Color(130, 73, 158));
	if (hit > 50)
		return (Color(44, 0, 66));
	return (Color(141, 35, 194));
}

HostEffect::HostEffect(Character *target)
{
	HostEffect::character = target;
	target->setAnimationActive(true);
	gameState.updateObjs.info->AddHostEffect(this);
}

void HostEffect::UpdateColor()
{
	float r = 255.0f - 194.0f;
	float g = 255.0f - 3.0f;
	float b = 255.0f - 252.0f;
	float ru = r / 17.0f;
	float gu = g / 17.0f;
	float bu = b / 17.0f;
	if (counter < 18)
	{
		//194, 3, 252
		int rs = rounding(255.0f - (ru * (float)counter));
		int gs = rounding(255.0f - (gu * (float)counter));
		int bs = rounding(255.0f - (bu * (float)counter));
		character->sprite->ColorMod(rs, gs, bs);
		return ;
	}
	float count = (float)counter - 18.0f;
	int rs = rounding(194.0f + (ru * (float)count));
	int gs = rounding(3.0f + (gu * (float)count));
	int bs = rounding(252.0f + (bu * (float)count));
	if (rs > 255 || gs > 255 || bs > 255)
	{
		character->sprite->ClearColorMod();
		return ;
	}
	character->sprite->ColorMod(rs, gs, bs);
}

void HostEffect::CreateParticles()
{
	SDL_Rect dest = character->sprite->dest;
	SDL_Point place = {(int)(dest.x + dest.w / 2.2f), dest.y + dest.h / 3};
	for (int i = 0; i < 180; i++)
	{
		float xAdder = (float)(rand() % 900 - rand() % 900);
		float yAdder = (float)(rand() % 3000 - rand() % 1200);
		Vector dir(0.0f, -1.0f);
		float angle = float_rand() * PI * 0.57f;
		angle = (rand() % 2 == 0) ? angle : -angle;
		vectorRotate(dir, angle);
		float speed = float_rand() * 200.0f + 100.0f;
		Color used = getColor();
		int life = rand() % 10 + 32;
		float drag = 1.0f + float_rand() * 0.2f;
		float yAdd = -float_rand() * 0.08f;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)place.x + xAdder, (float)place.y + yAdder), speed, used,
																						used, life, drag, false, yAdd);
	}
}

void HostEffect::Update()
{
	if (done)
		return ;
	UpdateColor();
	if (counter == 2)
		PlaySound(gameState.audio.hostEyes[0], Channels::HOST_EYES1, 0);
	if (counter == 12)
		CreateParticles();
	counter++;
	if (counter >= TIME)
		done = true;
}

void HostEffect::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->ClearColorMod();
}
