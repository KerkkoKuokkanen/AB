
#include "../../hdr/global.h"
#define SPRITE_AMOUNT 25

int offset = 50;

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

void HostEyesEffect::CreateSprites()
{
	SDL_Point place = {character->sprite->dest.x, character->sprite->dest.y};
	SDL_Rect dest = {place.x + 5000, place.y + 2500, 300, 300};
	pos = {(float)place.x + 5000.0f, (float)place.y + 2500.0f};
	genPos = pos;
	for (int i = 0; i < SPRITE_AMOUNT; i++)
	{
		dest.x += offset;
		Sprite *add = new Sprite(gameState.textures.KillParticle[0], dest, NULL, NULL, 0, FLIP_NONE);
		gameState.render->AddSprite(add, PARTICLE_LAYER);
		sprites.push_back(add);
		counters.push_back(0.0f + (0.25f * (float)i));
	}
}

HostEyesEffect::HostEyesEffect(Character *character, Character *target, float topAmount, bool top)
{
	HostEyesEffect::character = character;
	HostEyesEffect::target = target;
	CreateSprites();
	SDL_Rect dest = target->sprite->dest;
	SDL_Point temp = {(int)(dest.x + dest.w / 2.2f), dest.y + dest.h / 3};
	SDL_FPoint targ = {(float)temp.x, (float)temp.y};
	tPos = targ;
	Vector dist(targ.x - pos.x, targ.y - pos.y);
	totalDist = dist.Magnitude();
	HostEyesEffect::top = top;
	dist = dist.Normalized();
	genDir = {dist.x, dist.y};
	topAmount = (fabs(topAmount) < 10.0f) ? 10.0f : topAmount;
	HostEyesEffect::topAmount = topAmount;
}

void HostEyesEffect::MoveSprites()
{
	float volume = 340.0f;
	Vector newDir(dir.x, dir.y);
	vectorRotate(newDir, PI * 0.5f);
	for (int i = 0; i < sprites.size(); i++)
	{
		float ret = sin(counters[i]);
		Vector add(newDir.x * (volume * ret), newDir.y * (volume * ret));
		sprites[i]->dest.x += add.x;
		sprites[i]->dest.y += add.y;
	}
}

void HostEyesEffect::PlaceParts()
{
	SDL_Rect ogDest = sprites[0]->dest;
	ogDest.x = rounding(pos.x);
	ogDest.y = rounding(pos.y);
	for (int i = 0; i < sprites.size(); i++)
	{
		SDL_Rect used = sprites[i]->dest;
		used.x = ogDest.x + rounding(dir.x * offset * i);
		used.y = ogDest.y + rounding(dir.y * offset * i);
		sprites[i]->dest = used;
	}
}

void HostEyesEffect::ManageColors()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		float ret = 1.0f - fabs(sin(counters[i]));
		float r = 141.0f * ret;
		float g = 35.0f * ret;
		float b = 194.0f *ret;
		int ru = 10 + rounding(r);
		int gu = 10 + rounding(g);
		int bu = 10 + rounding(b);
		sprites[i]->ColorMod(ru, gu, bu);
	}
}

void HostEyesEffect::MovePos()
{
	genPos.x += genDir.x * 155.0f;
	genPos.y += genDir.y * 155.0f;
	float mag = Vector(tPos.x - genPos.x, tPos.y - genPos.y).Magnitude();
	float portion = 1.0f - mag / totalDist;
	float add = (-(portion * portion) + portion) * topAmount;
	Vector addDir(genDir.x, genDir.y);
	float multi = (top) ? -1.0f : 1.0f;
	vectorRotate(addDir, PI * 0.5f * multi);
	SDL_FPoint newPos;
	newPos.x = genPos.x + (addDir.x * add);
	newPos.y = genPos.y + (addDir.y * add);
	Vector newDir(newPos.x - pos.x, newPos.y - pos.y);
	newDir = newDir.Normalized();
	dir = {newDir.x, newDir.y};
	pos.x = newPos.x;
	pos.y = newPos.y;
}

bool HostEyesEffect::CheckIfDone()
{
	SDL_Rect dest = sprites[sprites.size() - 1]->dest;
	int x = dest.x;
	int y = dest.y;
	SDL_Surface *sur = getSurface(target);
	if (MenuHoverCheck(sur, target->sprite->dest, x, y))
		return (true);
	return (false);
}

void HostEyesEffect::Update()
{
	if (done)
		return ;
	MovePos();
	PlaceParts();
	MoveSprites();
	ManageColors();
	if (CheckIfDone())
	{
		done = true;
		return ;
	}
	for (int i = 0; i < counters.size(); i++)
		counters[i] += 0.4f;
}

void HostEyesEffect::CreateParticles()
{
	SDL_Rect dest = sprites[SPRITE_AMOUNT / 2]->dest;
	SDL_Point place = {dest.x + 150, dest.y + 150};
	for (int i = 0; i < 120; i++)
	{
		Vector dir(0.0f, -1.0f);
		float angle = float_rand() * PI;
		angle = (rand() % 2 == 0) ? angle : -angle;
		vectorRotate(dir, angle);
		float speed = float_rand() * 50.0f + 50.0f;
		Color used = getColor();
		int life = rand() % 10 + 22;
		float drag = 1.0f + float_rand() * 0.2f;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)place.x, (float)place.y), speed, used,
																							used, life, drag, false);
	}
}

void HostEyesEffect::Destroy()
{
	for (int i = 0; i < sprites.size(); i++)
		delete sprites[i];
	sprites.clear();
}
