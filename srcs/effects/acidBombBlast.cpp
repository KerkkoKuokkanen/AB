
#include "../../hdr/global.h"
#define MAX_SPEED 400.0f
#define DONE 33

static int GetAmount(int variation)
{
	if (variation >= 8)
		return (50);
	if (variation >= 5)
		return (60);
	if (variation >= 2)
		return (70);
	return (80);
}

static Vector GetDirection()
{
	Vector dir(0.0f, -1.0f);
	float angle = (rand() % 2 == 0) ? float_rand() * PI : -float_rand() * PI;
	vectorRotate(dir, angle);
	return (dir);
}

static float GetSpeed(Vector dir)
{
	Vector aVec(1.0f, 0.0f);
	if (dir.x < 0.0f)
		aVec.x = -1.0f;
	float angle = (PI * 0.5f) - vectorAngle(aVec, dir);
	if (angle < (PI * 0.1f))
		angle = (PI * 0.1f);
	float unit = MAX_SPEED / (PI * 0.5f);
	float speec = unit * angle;
	return (speec + 100.0f + (float)(rand() % 80));
}

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 75)
		return (Color(16, 99, 39));
	if (hit > 43)
		return (Color(50, 168, 82));
	if (hit > 9)
		return (Color(88, 191, 117));
	return (Color(3, 23, 9));
}

AcidBombBlast::AcidBombBlast(SDL_Point position, unsigned int variation)
{
	variation = (variation > 10) ? 10 : variation;
	AcidBombBlast::position = position;
	AcidBombBlast::variation = variation;
	adder = GetAmount(variation);
	gameState.updateObjs.info->AddBombEffect((void*)this, ACID_BOMB);
	defLife = (10 - variation) + 9;
}

void AcidBombBlast::CreateParticles()
{
	for (int i = 0; i < particleAmount; i++)
	{
		int xAdd = (rand() % 150) - (rand() % 150);
		int yAdd = (rand() % 150) - (rand() % 150);
		Vector dir = GetDirection();
		float drag = 1.06f + float_rand() * 0.1f;
		float speed = (rand() % 6 == 0) ? (float)(rand() % 550 + 50) * 0.7f : GetSpeed(dir) * 1.8f * 0.7f;
		Vector place((float)(position.x + xAdd), (float)(position.y + yAdd));
		int life = rand() % 10 + defLife;
		Color used = GetColor();
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, used, used, life, drag, false);
	}
}

void AcidBombBlast::GetParticleAmount()
{
	float count = (float)counter;
	float amount = -((count * count) / 12.0f) + (float)adder;
	particleAmount = rounding(amount);
	if (particleAmount < 0)
		particleAmount = 0;
}

void AcidBombBlast::Update()
{
	if (done)
		return ;
	GetParticleAmount();
	CreateParticles();
	counter++;
	if (counter >= DONE)
		done = true;
}

void AcidBombBlast::Destroy()
{

}
