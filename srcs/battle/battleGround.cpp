
#include "../../hdr/global.h"

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
	MoveInit(rend);
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
		add.orderLayer = i * 2;
		adder.push_back(add);
	}
	sprites.push_back(adder);
}

void BattleGround::ChangeUp()
{
	if (currentHeight == maxHeight)
		return ;
	currentHeight += 1;
	int currSprite = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].height >= currentHeight)
			{
				sprites[currSprite][currentHeight].ClearAlphaMod();
				if ((sprites[currSprite].size() - 1) <= currentHeight)
					map[i][j].active = true;
				if (map[i][j].character != NULL)
					map[i][j].character->sprite->ClearAlphaMod();
			}
			currSprite++;
		}
	}
}

void BattleGround::ChangeDown()
{
	if (currentHeight == 0)
		return ;
	currentHeight -= 1;
	int currSprite = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].height > currentHeight)
			{
				sprites[currSprite][currentHeight + 1].AlphaMod(alpha);
				map[i][j].active = false;
				if (map[i][j].character != NULL)
					map[i][j].character->sprite->AlphaMod(alpha);
			}
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
		std::vector<int> adder;
		unsigned int width = map[i].size() * gameState.battle.xDist;
		xStart = -(width / 2);
		for (int j = 0; j < map[i].size(); j++)
		{
			adder.push_back(-1);
			maxHeight = (maxHeight < map[i][j].height) ? map[i][j].height : maxHeight;
			minHeight = (minHeight > map[i][j].height) ? map[i][j].height : minHeight;
			CreateTile(map, i, j, xStart, yStart, everyOther);
		}
		toolMap.push_back(adder);
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
	t_GMU gmu = { 0, 0, 0, NULL, true, false, false };
	t_GMU one = { 0, 1, 0, NULL, true, false, false };
	t_GMU two = { 0, 2, 0, NULL, true, false, false };
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tst = {gmu, gmu, gmu, one, gmu, gmu, gmu, one, two, one, gmu};
	std::vector<t_GMU> tststs = {gmu, gmu, one, one, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tstststs = {gmu, gmu, gmu, one, one, two, two, one, gmu, gmu, gmu};
	map.clear();
	map = {tsts, tsts, tsts, tsts, tsts, tst, tstststs, tstststs, tstststs, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tst};
	CreateBattleGround(map);
}

void BattleGround::PlaceCharacter(SDL_Point &position, Character *character)
{
	if (position.x < 0 || position.y < 0 || position.y >= map.size() || position.x >= map[position.y].size())
	{
		printf("Battleground: position out of bounds\n");
		return ;
	}
	int index = position.y * map[0].size() + position.x;
	SDL_Rect location = sprites[index][sprites[index].size() - 1].dest;
	Vector place = GetCharacterCoord(position, character);
	character->Position(place);
	character->sprite->orderLayer = position.y * 2 + 1;
	map[position.y][position.x].character = character;
	map[position.y][position.x].blocked = true;
	map[position.y][position.x].character->setCoord(position);
}

void BattleGround::StartBattle(std::vector<Character> &characters, std::vector<SDL_Point> &mapPos)
{
	CreateMap();
	if (characters.size() != mapPos.size())
	{
		printf("BattleGround: size does not match\n");
		return ;
	}
	for (int i = 0; i < characters.size(); i++)
	{
		t_Troop add;
		add.character = &characters[i];
		add.clicked = false;
		BattleGround::characters.push_back(add);
		BattleGround::characters[i].character->AddToRender();
		PlaceCharacter(mapPos[i], BattleGround::characters[i].character);
	}
}

SDL_Rect BattleGround::getTileDest(SDL_Point pos)
{
	int index = pos.y * map[0].size() + pos.x;
	SDL_Rect ret = sprites[index][sprites[index].size() - 1].dest;
	return (ret);
}

void BattleGround::HighLightBlock(SDL_Point pos, Uint8 r, Uint8 g, Uint8 b)
{
	int index = pos.y * map[0].size() + pos.x;
	sprites[index][sprites[index].size() - 1].ColorMod(r, g, b);
}

void BattleGround::ResetBlockColor(SDL_Point pos)
{
	int index = pos.y * map[0].size() + pos.x;
	sprites[index][sprites[index].size() - 1].ClearColorMod();
}

Sprite *BattleGround::GetSprite(SDL_Point pos)
{
	int index = pos.y * map[0].size() + pos.x;
	return(&sprites[index][sprites[index].size() - 1]);
}

void BattleGround::RemoveCharacter(Character *character)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j].character != NULL)
			{
				if (map[i][j].character == character)
				{
					map[i][j].character = NULL;
					break ;
				}
			}
		}
	}
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i].character == character)
		{
			characters.erase(characters.begin() + i);
			break ;
		}
	}
	ClearMovables();
}

void BattleGround::Update()
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (!characters[i].character->clicked && characters[i].clicked)
		{
			characters[i].clicked = false;
			ClearMovables();
			break ;
		}
	}
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i].character->Update();
		if (characters[i].character->clicked && !characters[i].clicked)
		{
			characters[i].clicked = true;
			SetMovables(characters[i].character);
		}
	}
	IterBlocks();
	MoveCharacter();
}
