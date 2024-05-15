
#include "../../hdr/global.h"
#define COUNT_TIME 4
#define PART_DISTANCE 600

static Color GetColor()
{
	static Color colors[] = {Color(140, 117, 41), Color(240, 212, 120), Color(161, 127, 35)};
	return (colors[rand() % 3]);
}

static SDL_FPoint GetGeneralDirection(Character *caster, Character *target)
{
	SDL_Rect d1 = gameState.battle.ground->getTileDest(caster->position);
	SDL_Rect d2 = gameState.battle.ground->getTileDest(target->position);
	SDL_Point p1 = {d1.x, d1.y};
	SDL_Point p2 = {d2.x, d2.y};
	Vector dir((float)(p2.x - p1.x), (float)(p2.y - p1.y));
	dir = dir.Normalized();
	SDL_FPoint ret = {dir.x, dir.y};
	return (ret);
}

static Vector GetPartDir(SDL_FPoint generalDir)
{
	Vector send(generalDir.x, generalDir.y);
	float angle = float_rand() * (PI * 0.2f);
	angle = (rand() % 2 == 0) ? angle : -angle;
	vectorRotate(send, angle);
	return (send);
}

ShieldBashEffect::ShieldBashEffect(Character *caster, Character *target)
{
	ShieldBashEffect::target = target;
	targetSur = getSurface(target);
	generalDirection = GetGeneralDirection(caster, target);
	partCount = rand() % PART_DISTANCE;
	gameState.updateObjs.info->AddShieldBashEffect(this);
}

void ShieldBashEffect::CreateParticles(int start, int end)
{
	float wUnit = (float)target->sprite->dest.w / (float)targetSur->w;
	float hUnit = (float)target->sprite->dest.h / (float)targetSur->h;
	Uint32 *pixels = (Uint32*)targetSur->pixels;
	SDL_Rect dest = target->sprite->dest;
	for (int y = start; y < end; y++)
	{
		for (int x = 0; x < targetSur->w; x++)
		{
			if (pixels[(y * targetSur->w) + x] == 0)
				continue ;
			partCount++;
			if (partCount >= PART_DISTANCE)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir = GetPartDir(generalDirection);
				float speed = rand() % 600 + 300;
				int life = rand() % 20 + 22;
				float drag = 1.1f;
				t_Particle add = gameState.updateObjs.partManager->ReturnModPartWithText(gameState.textures.KillParticle[0], dir,
								Vector(xP, yP), speed, GetColor(), Color(1, 1, 1), life, drag, false, 0.0f);
				particles.push_back(add);
				partCount = 0;
			}
		}
	}
}

void ShieldBashEffect::Update()
{
	if (done)
		return ;
	if (count < COUNT_TIME)
	{
		int unit = targetSur->h / COUNT_TIME;
		CreateParticles(unit * count, unit * (count + 1));
	}
	if (count >= (COUNT_TIME))
	{
		for (int i = 0; i < particles.size(); i++)
			gameState.updateObjs.partManager->AddModParticle(particles[i]);
		particles.clear();
		done = true;
	}
	count++;
}

void ShieldBashEffect::Destroy()
{
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i].part->sprite;
		delete particles[i].part;
	}
	particles.clear();
}
