
#include "../../../hdr/ow/tiles/tileDataHolder.h"
#include "../../../hdr/ow/owHeader.h"

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
	mule = new Sprite(owState.textures.mule, {0, 0, DIMENTIONS, DIMENTIONS}, NULL, NULL, 0, FLIP_NONE);
	mule->orderLayer = 2;
	owState.renderer->AddSprite(mule, TILE_LAYER);
	if (address == NULL)
	{
		GetOwTileData(mapData, mapTiles);
		int h = mapData.size();
		int w = mapData[0].size();
		position = {10, 10};
		gameCamera.x = position.x * DIMENTIONS + DIMENTIONS / 2;
		gameCamera.y = position.y * DIMENTIONS + DIMENTIONS / 2;
		return ;
	}
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
	//mapTiles[position.y][position.x]->IsCurrentPos();
	mule->dest.x = DIMENTIONS * position.x;
	mule->dest.y = DIMENTIONS * position.y;
}

void TileDataHolder::SetPosition(SDL_Point pos)
{
	if (!ValidPosition(pos))
		return ;
	bool turnPossible = (pos.x == position.x) ? false : true;
	if (turnPossible)
	{
		if (pos.x > position.x)
			mule->setFlip(FLIP_HORIZONTAL);
		else
			mule->setFlip(FLIP_NONE);
	}
	TileDataHolder::position = pos;
	SDL_Point startPosition = {position.x * DIMENTIONS + DIMENTIONS / 2, position.y * DIMENTIONS + DIMENTIONS / 2};
	gameCamera.camMover.SetCameraMove({gameCamera.x, gameCamera.y}, startPosition, 12);
}

void TileDataHolder::Update()
{
	BringTiles();
	UpdateTiles();
}

void TileDataHolder::Destroy()
{
	for (int i = 0; i < mapTiles.size(); i++)
	{
		for (int j = 0; j < mapTiles[0].size(); j++)
		{
			if (mapTiles[i][j] == NULL)
				continue ;
			delete mapTiles[i][j];
		}
	}
}
