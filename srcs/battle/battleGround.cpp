
#include "../../hdr/global.h"

//512, 320

BattleGround::BattleGround(unsigned int layer, SDL_Renderer *rend)
{
	t_SpriteData add;
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isometric_block(16).png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isometric_block (25).png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isometric_block(16)Hi.png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isoHiLeft.png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isoHiRight.png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/ReguBlock/isometric_block(16)hiNoRim.png");
	add.srect = {0, 0, 496, 540};
	tiles.push_back(add);
	BattleGround::layer = layer;
}

static int HLeft(std::vector<std::vector<t_GMU>> &map, int i, int j, bool other)
{
	if (i == 0)
		return (0);
	if (!other && j == 0)
		return (0);
	if (!other)
		return (map[i - 1][j - 1].height);
	return (map[i - 1][j].height);
}

static int HRight(std::vector<std::vector<t_GMU>> &map, int i, int j, bool other)
{
	if (i == 0)
		return (0);
	if (other && j == (map[i].size() - 1))
		return (0);
	if (other)
		return (map[i - 1][j + 1].height);
	return (map[i - 1][j].height);
}

int BattleGround::GetSprite(std::vector<std::vector<t_GMU>> &map, int i, int j, int iter, bool other)
{
	if (iter == map[i][j].height)
	{
		if (map[i][j].height == 0)
			return (REGULAR_BLOCK);
		int hleft = HLeft(map, i, j, other);
		int hright = HRight(map, i, j, other);
		if (hleft < map[i][j].height && hright < map[i][j].height)
			return (TOP_CORNER_BLOCK);
		if (hleft < map[i][j].height)
			return (TOP_LEFT_BLOCK);
		if (hright < map[i][j].height)
			return (TOP_RIGHT_BLOCK);
		return (TOP_REGULAR_BLOCK);
	}
	return (FILLER_BLOCK);
}

void BattleGround::CreateTile(std::vector<std::vector<t_GMU>> &map, int i, int j, int xStart, int yStart, bool other)
{
	int xder = (other) ? gameState.battle.xDist / 2 : 0;
	std::vector<Sprite> adder;
	for (int iter = 0; iter <= map[i][j].height; iter++)
	{
		SDL_Rect dest = {
			xStart + (gameState.battle.xDist * j) + xder,
			yStart + (gameState.battle.defaultYAdd * i) - (gameState.battle.yHeightAdd * iter),
			gameState.battle.xDist + 20,	//this " + 20 " just for preventing pixel jitter
			gameState.battle.yDist
		};
		int image = GetSprite(map, i, j, iter, other);
		Sprite add(tiles[image].texture, dest, &tiles[image].srect, NULL, 0, FLIP_NONE);
		adder.push_back(add);
	}
	sprites.push_back(adder);
}

void BattleGround::ChangeUp()
{
	if (currentHeight == maxHeight)
	{
		printf("battleGround: height already max\n");
		return ;
	}
	currentHeight += 1;
	int currSprite = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			currSprite++;
		}
	}
}

void BattleGround::ChangeDown()
{
	if (currentHeight == 0)
	{
		printf("battleGround: height at zero\n");
		return ;
	}
	currentHeight -= 1;
	int currSprite = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].height > currentHeight)
				sprites[currSprite][currentHeight + 1].AlphaMod(alpha);
			currSprite++;
		}
	}
}

void BattleGround::ChangeMapHeight(bool down)
{
	if (map.size() == 0)
	{
		printf("battleGround: trying to change map with no size\n");
		return ;
	}
	if (down)
	{
		ChangeDown();
		return ;
	}
	ChangeUp();
}

void BattleGround::CreateBattleGround(std::vector<std::vector<t_GMU>> &map)
{
	if (map.size() == 0)
	{
		printf("battleGround: map with no size\n");
		return ;
	}
	unsigned int height = map.size() * gameState.battle.defaultYAdd;
	int xStart, yStart = -(height / 2);
	bool everyOther = false;
	maxHeight = map[0][0].height; minHeight = map[0][0].height;
	for (int i = 0; i < map.size(); i++)
	{
		unsigned int width = map[i].size() * gameState.battle.xDist;
		xStart = -(width / 2);
		for (int j = 0; j < map[i].size(); j++)
		{
			maxHeight = (maxHeight < map[i][j].height) ? map[i][j].height : maxHeight;
			minHeight = (minHeight > map[i][j].height) ? map[i][j].height : minHeight;
			CreateTile(map, i, j, xStart, yStart, everyOther);
		}
		everyOther = (everyOther) ? false : true;
	}
	currentHeight = maxHeight;
	for (int i = 0; i < sprites.size(); i++)
	{
		for (int j = 0; j < sprites[i].size(); j++)
			gameState.render->AddSprite(&sprites[i][j], layer);
	}
}

void BattleGround::CreateMap()
{
	t_GMU gmu = { 0, 0 };
	t_GMU one = { 0, 1 };
	t_GMU two = { 0, 2 };
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tst = {gmu, gmu, gmu, one, gmu, gmu, gmu, one, two, one, gmu};
	std::vector<t_GMU> tststs = {gmu, gmu, one, one, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tstststs = {gmu, gmu, gmu, one, one, two, two, one, gmu, gmu, gmu};
	map.clear();
	map = {tsts, tsts, tsts, tsts, tsts, tst, tstststs, tstststs, tstststs, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tst};
	CreateBattleGround(map);
}
