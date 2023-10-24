
#include "../../hdr/global.h"
#define NAIL_AMOUNT 120
#define PARTICLE_AMOUNT 500
#define MAX_SPEED 400.0f

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

static SDL_Point GetPlace(SDL_Point position)
{
	int xAdd = rand() % 300;
	int yAdd = rand() % 300;
	if (rand() % 2 == 0)
		xAdd = -xAdd;
	if (rand() % 2 == 0)
		yAdd = -yAdd;
	SDL_Point ret = {position.x + xAdd, position.y + yAdd};
	return (ret);
}

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 75)
		return (Color(61, 27, 17));
	if (hit > 43)
		return (Color(207, 152, 2));
	if (hit > 9)
		return (Color(207, 46, 2));
	return (Color(3, 1, 1));
}

void NailBombBlast::CreateParticles()
{
	int amount = (int)(PARTICLE_AMOUNT * amountMulti);
	for (int i = 0; i < amount; i++)
	{
		int xAdd = (rand() % 150) - (rand() % 150);
		int yAdd = (rand() % 150) - (rand() % 150);
		Vector dir = GetDirection();
		float drag = 1.06f + float_rand() * 0.1f;
		float speed = (rand() % 6 == 0) ? (float)(rand() % 550 + 50) * speedMulti : GetSpeed(dir) * 1.3f * speedMulti;
		Vector place((float)(position.x + xAdd), (float)(position.y + yAdd));
		int life = rand() % 10 + 40;
		Color used = GetColor();
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, used, used, life, drag, false);
	}
}

void NailBombBlast::CreateNails()
{
	int amount = (int)(NAIL_AMOUNT * amountMulti);
	for (int i = 0; i < amount; i++)
	{
		Vector dir = GetDirection();
		float speed = GetSpeed(dir) * (float_rand() + 0.1f) * speedMulti;
		SDL_FPoint direction = {dir.x, dir.y};
		float angle = vectorAngle(Vector(0.0f, -1.0f), dir);
		float dec = degree(angle);
		if (dir.x < 0.0f)
			dec = -dec;
		SDL_Point pos = GetPlace(position);
		Sprite *nail = new Sprite(gameState.textures.attacks.nail, {pos.x, pos.y, 500, 500}, NULL, NULL, dec, FLIP_NONE);
		gameState.render->AddSprite(nail, OBJECT_LAYER);
		int life = rand() % 5 + 23;
		nails.push_back({life, direction, speed, nail});
	}
}

NailBombBlast::NailBombBlast(SDL_Point position, unsigned int type)
{
	NailBombBlast::position = position;
	type = (type > 10) ? 10 : type;
	NailBombBlast::type = type;
	float unit = 0.5f / 10.0f;
	amountMulti = 1.0f - (unit * type);
	speedMulti = 1.0f - (unit * type);
	CreateNails();
	CreateParticles();
	gameState.updateObjs.info->AddBombEffect((void*)this, NAIL_BOMB);
}

void NailBombBlast::UpdateNailAlpha(t_Nail &nail)
{
	if (nail.life > 10)
		return ;
	float unit = 255.0f / 10.0f;
	float alpha = unit * (float)nail.life;
	int used = rounding(alpha);
	if (used < 0)
		used = 0;
	nail.sprite->AlphaMod(used);
}

void NailBombBlast::UpdateNailPosition(t_Nail &nail)
{
	SDL_FPoint dir = nail.direction;
	SDL_Rect dest = nail.sprite->dest;
	SDL_FPoint pos = {(float)dest.x, (float)dest.y};
	pos.x += dir.x * nail.speed;
	pos.y += dir.y * nail.speed;
	nail.sprite->Position(Vector(pos.x, pos.y));
	if (nail.life > 10)
		return ;
	SDL_Rect nDest = nail.sprite->dest;
	nail.sprite->dest = {nDest.x + 7, nDest.y + 7, nDest.w - 14, nDest.h - 14};
}

void NailBombBlast::Update()
{
	if (done)
		return ;
	if (nails.size() == 0)
	{
		done = true;
		return ;
	}
	for (int i = 0; i < nails.size(); i++)
	{
		if (nails[i].life <= 0)
		{
			delete nails[i].sprite;
			nails.erase(nails.begin() + i);
			i = (nails.size() == 0) ? 0 : i - 1;
			continue ;
		}
		UpdateNailAlpha(nails[i]);
		UpdateNailPosition(nails[i]);
		nails[i].life -= 1;
	}
}

void NailBombBlast::Destroy()
{
	for (int i = 0; i < nails.size(); i++)
		delete nails[i].sprite;
	nails.clear();
}
