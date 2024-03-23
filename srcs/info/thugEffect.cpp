
#include "../../hdr/global.h"
#define POINT_DIST 26
#define POINT_DIST2 22

SDL_Point *thugPartPoints = NULL;
SDL_Point *thugPartPoints2 = NULL;

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
	thugPartPoints = (SDL_Point*)malloc(sizeof(SDL_Point) * size);
	for (int i = 0; i < points.size(); i++)
	{
		SDL_Point pos = {rounding(points[i].x), rounding(points[i].y)};
		thugPartPoints[i] = pos;
	}
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
	thugPartPoints = (SDL_Point*)malloc(sizeof(SDL_Point) * size);
	for (int i = 0; i < points.size(); i++)
	{
		SDL_Point pos = {rounding(points[i].x), rounding(points[i].y)};
		thugPartPoints[i] = pos;
	}
	points.clear();
}

void InitThugParts()
{
	GetFirst();
	GetSecond();
}
