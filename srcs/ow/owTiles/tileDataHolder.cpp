
#include "../../../hdr/ow/tiles/tileDataHolder.h"
#include "../../../hdr/ow/owHeader.h"
#define START_POS -30000

static void GetOwTileData(std::vector<std::vector<t_TileData>> &data, std::vector<std::vector<MapTile*>> &tiles)
{
	for (int i = 0; i < 20; i++)
	{
		std::vector<t_TileData> adder;
		std::vector<MapTile*> adder2;
		data.push_back(adder);
		tiles.push_back(adder2);
		for (int j = 0; j < 20; j++)
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

TileDataHolder::TileDataHolder(const char *address)
{
	if (address == NULL)
	{
		GetOwTileData(mapData, mapTiles);
		int h = mapData.size();
		int w = mapData[0].size();
		position = {w / 2, h / 2};
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
	SDL_Point posCurr = {START_POS, START_POS};
	for (int i = 0; i < mapData.size(); i++)
	{
		posCurr.x = START_POS;
		for (int j = 0; j < mapData[0].size(); j++)
		{
			if (mapTiles[i][j] == NULL)
			{
				t_TileData &ref = mapData[i][j];
				SDL_Texture *ret = GetCorrespondingTileText(ref.textureType);
				mapTiles[i][j] = new MapTile(ret, ref.sRect, posCurr);
				posCurr.x += DIMENTIONS;
			}
		}
		posCurr.y += DIMENTIONS;
	}
}

void TileDataHolder::UpdateTiles()
{
	for (int i = 0; i < mapTiles.size(); i++)
	{
		for (int j = 0; j < mapTiles.size(); j++)
		{
			if (mapTiles[i][j] == NULL)
				continue ;
			mapTiles[i][j]->Update();
		}
	}
}

void TileDataHolder::SetCamera()
{
	if (mapTiles[position.y][position.x] == NULL)
		return ;
	SDL_Point place = mapTiles[position.y][position.x]->GetDestPoint();
	gameCamera.x = place.x;
	gameCamera.y = place.y;
}

void TileDataHolder::Update()
{
	BringTiles();
	UpdateTiles();
	SetCamera();
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
