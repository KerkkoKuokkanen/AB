
#include "../../../hdr/global.h"
#define TIME_OUT 700
#define PART_DISTANCE 1800

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 70)
		return (Color(168, 11, 0));
	if (hit > 40)
		return (Color(64, 9, 5));
	return (Color(186, 70, 61));
}

HealthTransfer::HealthTransfer(Character *start, Character *end)
{
	HealthTransfer::start = start;
	HealthTransfer::end = end;
	sur = getSurface(start);
	start->setAnimationActive(true);
	SDL_Rect dest = end->sprite->dest;
	int x = dest.x + dest.w / 2;
	int y = dest.y + dest.h / 2;
	goal = {x, y};
}

void HealthTransfer::CreateParticles(int yStart, int yEnd)
{
	float wUnit = (float)start->sprite->dest.w / (float)sur->w;
	float hUnit = (float)start->sprite->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = start->sprite->dest;
	int y = yStart;
	while (y < yEnd)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			partCounter++;
			if (partCounter >= PART_DISTANCE)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir(0.0f, -1.0f);
				float angle = float_rand() * (PI);
				angle = (rand() % 2 == 0) ? -angle : angle;
				vectorRotate(dir, angle);
				float speed = rand() % 200 + 200;
				Sprite *used = new Sprite(gameState.textures.KillParticle[0], {rounding(xP), rounding(yP), 400, 400}, NULL, NULL, 0, FLIP_NONE);
				Color ret = GetColor();
				used->ColorMod(ret.r, ret.g, ret.b);
				t_HealthParticle add = {used, {dir.x, dir.y}, speed, 0.0f, 0};
				used->Deactivate();
				gameState.render->AddSprite(used, PARTICLE_LAYER);
				particles.push_back(add);
				partCounter = 0;
			}
		}
		y++;
	}
}

void HealthTransfer::ManageCreatingParticles()
{
	if (counter >= 5)
		return ;
	if (counter < 4)
	{
		int unit = sur->h / 4;
		CreateParticles(unit * counter, unit * (counter + 1));
	}
	if (counter == 4)
	{
		totalAmount = particles.size();
		for (int i = 0; i < particles.size(); i++)
			particles[i].sprite->Activate();
		start->setAnimationActive(false);
	}
}

Vector HealthTransfer::GetGoalDirection(int index)
{
	SDL_Rect place = particles[index].sprite->dest;
	SDL_Point dir = {goal.x - place.x, goal.y - place.y};
	Vector ret = Vector((float)(dir.x), (float)(dir.y)).Normalized();
	return (ret);
}

bool HealthTransfer::CheckIfAtGoal(int index)
{
	SDL_Rect dest = particles[index].sprite->dest;
	int x = dest.x;
	int y = dest.y;
	SDL_Surface *sur = getSurface(end);
	if (MenuHoverCheck(sur, end->sprite->dest, x, y))
		return (true);
	SDL_Point mag = {x - goal.x, y - goal.y};
	float len = Vector((float)mag.x, (float)mag.y).Magnitude();
	if (len < 900.0f)
		return (true);
	if (counter > 100 && particles.size() <= totalAmount * 0.1f)
		return (true);
	return (false);
}

void HealthTransfer::ManageParticleMoving()
{
	if (counter < 5)
		return ;
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].dirChangeStrength = 0.01f * (float)particles[i].time;
		Vector goalDir = GetGoalDirection(i);
		particles[i].direction.x += goalDir.x * particles[i].dirChangeStrength;
		particles[i].direction.y += goalDir.y * particles[i].dirChangeStrength;
		Vector newDir = Vector(particles[i].direction.x, particles[i].direction.y).Normalized();
		particles[i].direction = {newDir.x, newDir.y};
		float xAdd = particles[i].direction.x * particles[i].speed;
		float yAdd = particles[i].direction.y * particles[i].speed;
		particles[i].sprite->Move(Vector(xAdd, yAdd));
		particles[i].time++;
		if (CheckIfAtGoal(i))
		{
			PlaySound(gameState.audio.healPart, Channels::VOLUME_3, 0);
			delete particles[i].sprite;
			particles.erase(particles.begin() + i);
			i = (particles.size() == 0) ? 0 : i - 1;
		}
	}
}

void HealthTransfer::ManageParticles()
{
	ManageCreatingParticles();
	ManageParticleMoving();
	if (counter >= 5 && particles.size() == 0)
	{
		createEffect = true;
		done = true;
	}
}

void HealthTransfer::Update()
{
	createDamage = false;
	createEffect = false;
	if (done)
		return ;
	if (start != NULL)
	{
		if (start->killed)
			start = NULL;
	}
	ManageParticles();
	if (counter == 6)
		createDamage = true;
	counter++;
	if (counter >= TIME_OUT)
		done = true;
}

void HealthTransfer::Destroy()
{
	for (int i = 0; i < particles.size(); i++)
		delete particles[i].sprite;
}
