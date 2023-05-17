
#include "../../hdr/global.h"

void ParticleManager::ManageColorChange(Particle *part)
{
	if (part->life > PART_LIFE)
		return ;
	int iter = part->ogLife - part->life;
	if (iter >= PART_LIFE)
		return ;
	float unit = 80.0f / (float)PART_LIFE;
	int value = rounding(unit * (float)iter);
	if (value < 2)
		value = 2;
	part->sprite->ColorMod(value, value, value);
}

void ParticleManager::ManageAlphaChange(Particle *part)
{
	if (part->life > 80)
		return ;
	float aUnit = 255.0f / 80.0f;
	int alpha = rounding(aUnit * part->life);
	part->sprite->AlphaMod(alpha);
}

void ParticleManager::Update()
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->active == true)
		{
			ManageAlphaChange(particles[i]);
			ManageColorChange(particles[i]);
			particles[i]->Update();
		}
		else
		{
			delete particles[i]->sprite;
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

void ParticleManager::CreateParticle(Vector dir, Vector place, float speed)
{
	Particle *part = new Particle;
	part->init();
	part->Activate();
	part->setPosition(place);
	part->setDirection(dir);
	part->setLifeTime(PART_LIFE + rand() % 80);
	part->setSpeed(speed);
	part->sprite->ColorMod(2, 2, 2);
	part->sprite->ClearAlphaMod();
	particles.push_back(part);
}
