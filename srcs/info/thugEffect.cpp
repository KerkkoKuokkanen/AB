
#include "../../hdr/global.h"
#define POINT_DIST 26
#define POINT_DIST2 22

int sizeOne = 0;
int sizeTwo = 0;
SDL_Point *thugPartPoints1 = NULL;
SDL_Point *thugPartPoints2 = NULL;
SDL_Surface *surface1 = NULL;
SDL_Surface *surface2 = NULL;

static void GetSecond()
{
	std::vector<SDL_FPoint> points = {};
	SDL_Surface *sur = gameState.surfaces.thugSource2;
	SDL_Rect dest = {0, 0, 6500, 7560};
	float wUnit = (float)dest.w / (float)sur->w;
	float hUnit = (float)dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	int partCount = 0;
	for (int y = 0; y < sur->h; y++)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			partCount++;
			if (partCount >= POINT_DIST2)
			{
				float xP = (wUnit * (float)x);
				float yP = (hUnit * (float)y);
				points.push_back({xP, yP});
				partCount = 0;
			}
		}
	}
	int size = (int)points.size();
	thugPartPoints2 = (SDL_Point*)malloc(sizeof(SDL_Point) * size);
	for (int i = 0; i < points.size(); i++)
	{
		SDL_Point pos = {rounding(points[i].x), rounding(points[i].y)};
		thugPartPoints2[i] = pos;
	}
	sizeTwo = (int)points.size();
	points.clear();
}

static void GetFirst()
{
	std::vector<SDL_FPoint> points = {};
	SDL_Surface *sur = gameState.surfaces.thugSource;
	SDL_Rect dest = {0, 0, 6500, 7560};
	float wUnit = (float)dest.w / (float)sur->w;
	float hUnit = (float)dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	int partCount = 0;
	for (int y = 0; y < sur->h; y++)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			partCount++;
			if (partCount >= POINT_DIST)
			{
				float xP = (wUnit * (float)x);
				float yP = (hUnit * (float)y);
				points.push_back({xP, yP});
				partCount = 0;
			}
		}
	}
	int size = (int)points.size();
	thugPartPoints1 = (SDL_Point*)malloc(sizeof(SDL_Point) * size);
	for (int i = 0; i < points.size(); i++)
	{
		SDL_Point pos = {rounding(points[i].x), rounding(points[i].y)};
		thugPartPoints1[i] = pos;
	}
	sizeOne = (int)points.size();
	points.clear();
}

void InitThugParts()
{
	surface1 = gameState.surfaces.thugSource;
	surface2 = gameState.surfaces.thugSource2;
	GetFirst();
	GetSecond();
}

static Vector GetDirection(SDL_Point pos)
{
	int midX = 6500 / 2;
	int midY = 7560 / 2;
	int x = pos.x - midX;
	int y = pos.y - midY;
	Vector dir = Vector((float)x, (float)y).Normalized();
	dir.y = -0.06f;
	if (abs(x) < 900)
		dir.y = -0.63f;
	return (dir);
}

static float GetSpeed()
{
	int speed = rand() % 200;
	return ((float)speed);
}

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 75)
		return (Color(105, 30, 22));
	if (hit > 40)
		return (Color(138, 13, 0));
	return (Color(179, 46, 32));
}

static void ThugOne(Character *character, int intensity)
{
	SDL_Point pos = {character->sprite->dest.x, character->sprite->dest.y};
	int dist = (100 - intensity <= 0) ? 1 : 100 - intensity;
	int count = rand() % dist;
	while (count < sizeOne)
	{
		int x = pos.x + thugPartPoints1[count].x;
		int y = pos.y + thugPartPoints1[count].y;
		Vector dir = GetDirection({thugPartPoints1[count].x, thugPartPoints1[count].y});
		Vector place((float)x, (float)y);
		float speed = GetSpeed();
		int life = rand() % 60 + 20;
		float drag = 1.0f + float_rand() * 0.1f;
		float yAdd = float_rand() * -0.1f;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), GetColor(), life, drag, false, yAdd);
		count += dist;
	}
}

static void ThugTwo(Character *character, int intensity)
{
	SDL_Point pos = {character->sprite->dest.x, character->sprite->dest.y};
	int dist = (100 - intensity <= 0) ? 1 : 100 - intensity;
	int count = rand() % dist;
	while (count < sizeOne)
	{
		int x = pos.x + thugPartPoints2[count].x;
		int y = pos.y + thugPartPoints2[count].y;
		Vector dir = GetDirection({thugPartPoints2[count].x, thugPartPoints2[count].y});
		Vector place((float)x, (float)y);
		float speed = GetSpeed();
		int life = rand() % 60 + 20;
		float drag = 1.0f + float_rand() * 0.1f;
		float yAdd = float_rand() * -0.1f;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), GetColor(), life, drag, false, yAdd);
		count += dist;
	}
}

void CreateParticlesForThugIntensity0To100(Character *character, int intensity)
{
	if (character->sprite->getTexture() == gameState.textures.chars.thugIdle[0])
		ThugOne(character, intensity);
	else
		ThugTwo(character, intensity);
}
