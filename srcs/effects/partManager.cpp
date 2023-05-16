
#include "../../hdr/global.h"

ParticleManager::ParticleManager()
{
	int i = 0;
	while (i < 5000) // partcile reserve amount
	{
		Particle *part = new Particle;
		part->init();
		part->active = false;
		particles.push_back(part);
		i++;
	}
}

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
		if (particles[i]->active)
		{
			ManageAlphaChange(particles[i]);
			ManageColorChange(particles[i]);
			particles[i]->Update();
		}
		else
			particles[i]->Deactivate();
	}
}

void ParticleManager::AddPartcile()
{
	Particle *part = new Particle;
	part->init();
	part->active = false;
	particles.push_back(part);
}

void ParticleManager::CreateParticle(Vector dir, Vector place, float speed)
{
	int i = 0;
	while (i < particles.size())
	{
		if (particles[i]->active == false)
			break ;
		i++;
	}
	if (i == particles.size())
		AddPartcile();
	particles[i]->Activate();
	particles[i]->setPosition(place);
	particles[i]->setDirection(dir);
	particles[i]->setLifeTime(PART_LIFE + rand() % 80);
	particles[i]->setSpeed(speed);
	particles[i]->sprite->ColorMod(2, 2, 2);
	particles[i]->sprite->ClearAlphaMod();
}
