
#include "../../../hdr/ow/tiles/tileDataHolder.h"
#include "../../../hdr/ow/owHeader.h"
#include "../../../hdr/ow/owKeys.h"

static void GetOwTileData(std::vector<std::vector<t_TileData>> &data, std::vector<std::vector<MapTile*>> &tiles)
{
	for (int i = 0; i < 100; i++)
	{
		std::vector<t_TileData> adder;
		std::vector<MapTile*> adder2;
		data.push_back(adder);
		tiles.push_back(adder2);
		for (int j = 0; j < 100; j++)
		{
			int x = rand() % 65;
			int y = rand() % 65;
			t_TileData add;
			add.textureType = 0;
			add.sRect = {x, y, 64, 64};
			data[i].push_back(add);
			tiles[i].push_back(NULL);
		}
	}
}

static int RangeBetween(SDL_Point one, SDL_Point two)
{
	int first = abs(one.x - two.x);
	int second = abs(one.y - two.y);
	return (first + second);
}

TileDataHolder::TileDataHolder(const char *address)
{
	SetTheHolder(this);
	if (address == NULL)
	{
		GetOwTileData(mapData, mapTiles);
		int h = mapData.size();
		int w = mapData[0].size();
		position = {10, 10};
		gameCamera.x = position.x * DIMENTIONS + DIMENTIONS / 2;
		gameCamera.y = position.y * DIMENTIONS + DIMENTIONS / 2;
	}
	player = new Player();
}

bool TileDataHolder::ValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.y < 0)
		return (false);
	if (pos.y >= mapData.size())
		return (false);
	if (pos.x >= mapData[0].size())
		return (false);
	return (true);
}

void TileDataHolder::BringTiles()
{
	int goDist = activeRange * 2 + 1;
	SDL_Point start = {position.x - activeRange, position.y - activeRange};
	for (int i = 0; i < goDist; i++)
	{
		int currY = start.y + i;
		for (int j = 0; j < goDist; j++)
		{
			int currX = start.x + j;
			if (!ValidPosition({currX, currY}))
				continue ;
			if (RangeBetween({currX, currY}, position) > activeRange)
				continue ;
			if (mapTiles[currY][currX] != NULL)
				continue ;
			t_TileData &ref = mapData[currY][currX];
			SDL_Texture *ret = GetCorrespondingTileText(ref.textureType);
			SDL_Point place = {DIMENTIONS * currX, DIMENTIONS * currY};
			mapTiles[currY][currX] = new MapTile(ret, ref.sRect, place);
			broughtTiles.push_back({currX, currY});
		}
	}
}

void TileDataHolder::UpdateTiles()
{
	for (int i = 0; i < broughtTiles.size(); i++)
	{
		SDL_Point pos = broughtTiles[i];
		int dist = RangeBetween(pos, position);
		if (mapTiles[pos.y][pos.x] == NULL)
		{
			broughtTiles.erase(broughtTiles.begin() + i);
			i = (broughtTiles.size() == 0) ? 0 : i - 1;
			continue ;
		}
		if (dist > activeRange)
		{
			delete mapTiles[pos.y][pos.x];
			mapTiles[pos.y][pos.x] = NULL;
			broughtTiles.erase(broughtTiles.begin() + i);
			i = (broughtTiles.size() == 0) ? 0 : i - 1;
			continue ;
		}
		mapTiles[pos.y][pos.x]->Update();
		if (dist > range)
			mapTiles[pos.y][pos.x]->Deactivate();
		else
			mapTiles[pos.y][pos.x]->Activate();
	}
}

bool TileDataHolder::SetPosition(SDL_Point pos, int time)
{
	if (!ValidPosition(pos))
		return (false);
	TileDataHolder::position = pos;
	SDL_Point startPosition = {position.x * DIMENTIONS + DIMENTIONS / 2, position.y * DIMENTIONS + DIMENTIONS / 2};
	gameCamera.camMover.SetCameraMove({gameCamera.x, gameCamera.y}, startPosition, time);
	return (true);
}

void TileDataHolder::Update()
{
	if (player != NULL)
		player->Update();
	BringTiles();
	UpdateTiles();
	mapTiles[position.y][position.x]->IsCurrentPos();
}

void TileDataHolder::Destroy()
{
	if (player != NULL)
		delete player;
	for (int i = 0; i < broughtTiles.size(); i++)
	{
		SDL_Point pos = broughtTiles[i];
		delete mapTiles[pos.y][pos.x];
		mapTiles[pos.y][pos.x] = NULL;
	}
	broughtTiles.clear();
}
