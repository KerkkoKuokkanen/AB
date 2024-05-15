
#include "../../hdr/global.h"

void ParticleManager::ManageColorChange(Particle *part)
{
	if (part->life < PART_LIFE)
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

void ParticleManager::ManageModColor(t_Particle *part)
{
	float r = (float)part->sr - (float)part->r;
	float g = (float)part->sg - (float)part->g;
	float b = (float)part->sb - (float)part->b;
	float rUnit = r / (float)part->total;
	float gUnit = g / (float)part->total;
	float bUnit = b / (float)part->total;
	Uint8 red = (int)part->r + (int)(rUnit * part->lifeTime);
	Uint8 green = (int)part->g + (int)(gUnit * part->lifeTime);
	Uint8 blue = (int)part->b + (int)(bUnit * part->lifeTime);
	part->part->sprite->ColorMod(red, green, blue);
}

void ParticleManager::ManageModAlpha(t_Particle *part)
{
	float max = (float)part->total / 3.0f;
	if (part->lifeTime > max)
		return ;
	float unit = 255.0f / max;
	int alpha = (Uint8)(unit * (max - (max - (float)part->lifeTime)));
	Uint8 use = (alpha > 255) ? 255 : (Uint8)alpha;
	part->part->sprite->AlphaMod(use);
}

void ParticleManager::ManageYAdd(t_Particle *part)
{
	part->dir.y += part->yAdd;
	part->part->setDirection(Vector(part->dir.x, part->dir.y));
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
	for (int i = 0; i < modParts.size(); i++)
	{
		if (modParts[i].part->active == true)
		{
			ManageModColor(&modParts[i]);
			ManageModAlpha(&modParts[i]);
			ManageYAdd(&modParts[i]);
			modParts[i].part->Update();
			modParts[i].lifeTime -= 1;
		}
		else
		{
			delete modParts[i].part->sprite;
			delete modParts[i].part;
			modParts.erase(modParts.begin() + i);
		}
	}
}

void ParticleManager::CreateModParticleWithTexture(SDL_Texture *text, Vector dir, Vector place, float speed, Color start, Color end,
												int life, float drag, bool staticSprite, float yAdd, SDL_Rect dest)
{
	t_Particle particle;
	particle.part = new Particle;
	particle.part->initWithTexture(text, dest);
	particle.part->Activate();
	particle.part->setPosition(place);
	particle.part->setDirection(dir);
	particle.part->setLifeTime(life);
	particle.part->setSpeed(speed);
	particle.part->SetDrag(drag);
	particle.part->sprite->ColorMod(start.r, start.g, start.b);
	particle.part->sprite->ClearAlphaMod();
	if (staticSprite)
		particle.part->sprite->setStatic(true);
	particle.r = end.r; particle.g = end.g; particle.b = end.b;
	particle.sr = start.r; particle.sg = start.g; particle.sb = start.b;
	particle.lifeTime = life; particle.total = life;
	particle.yAdd = yAdd;
	particle.dir.x = dir.x; particle.dir.y = dir.y;
	modParts.push_back(particle);
}

t_Particle ParticleManager::ReturnModPartWithText(SDL_Texture *text, Vector dir, Vector place, float speed, Color start, Color end,
												int life, float drag, bool staticSprite, float yAdd, SDL_Rect dest)
{
	t_Particle particle;
	particle.part = new Particle;
	particle.part->initWithTexture(text, dest);
	particle.part->Activate();
	particle.part->setPosition(place);
	particle.part->setDirection(dir);
	particle.part->setLifeTime(life);
	particle.part->setSpeed(speed);
	particle.part->SetDrag(drag);
	particle.part->sprite->ColorMod(start.r, start.g, start.b);
	particle.part->sprite->ClearAlphaMod();
	if (staticSprite)
		particle.part->sprite->setStatic(true);
	particle.r = end.r; particle.g = end.g; particle.b = end.b;
	particle.sr = start.r; particle.sg = start.g; particle.sb = start.b;
	particle.lifeTime = life; particle.total = life;
	particle.yAdd = yAdd;
	particle.dir.x = dir.x; particle.dir.y = dir.y;
	return (particle);
}

void ParticleManager::CreateModParticle(Vector dir, Vector place, float speed, Color start, Color end,
															int life, float drag, bool staitcSprite, float yAdd)
{
	t_Particle particle;
	particle.part = new Particle;
	particle.part->init();
	particle.part->Activate();
	particle.part->setPosition(place);
	particle.part->setDirection(dir);
	particle.part->setLifeTime(life);
	particle.part->setSpeed(speed);
	particle.part->SetDrag(drag);
	particle.part->sprite->ColorMod(start.r, start.g, start.b);
	particle.part->sprite->ClearAlphaMod();
	if (staitcSprite)
		particle.part->sprite->setStatic(true);
	particle.r = end.r; particle.g = end.g; particle.b = end.b;
	particle.sr = start.r; particle.sg = start.g; particle.sb = start.b;
	particle.lifeTime = life; particle.total = life;
	particle.yAdd = yAdd;
	particle.dir.x = dir.x; particle.dir.y = dir.y;
	modParts.push_back(particle);
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

void ParticleManager::AddModParticle(t_Particle &modPart)
{
	modPart.part->Activate();
	modParts.push_back(modPart);
}

void ParticleManager::Destroy()
{
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i]->sprite;
		delete particles[i];
	}
	for (int i = 0; i < modParts.size(); i++)
	{
		delete modParts[i].part->sprite;
		delete modParts[i].part;
	}

}
