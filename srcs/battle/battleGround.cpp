
#include "../../hdr/global.h"

//512, 320

BattleGround::BattleGround(unsigned int layer, SDL_Renderer *rend)
{
	t_SpriteData add;
	add.texture = get_texture(rend, "sprites/ground/isometric_block(16).png");
	add.srect = {3, 0, 500, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/isometric_block (25).png");
	add.srect = {3, 0, 500, 540};
	tiles.push_back(add);
	add.texture = get_texture(rend, "sprites/ground/isometric_block(16) hi.png");
	add.srect = {3, 0, 500, 540};
	tiles.push_back(add);
	BattleGround::layer = layer;
}

t_SpriteData *BattleGround::GetSprite(int sprite)
{
	return (&tiles[sprite]);
}

void BattleGround::AddGroundSprite(int xStart, int yStart, bool everyOther, t_GMU &gmu, int i, int j)
{
	int spriteAmount = 1;
	SDL_Rect dest = {
		xStart + (gameState.battle.xDist * j) + (everyOther == true ? gameState.battle.xDist / 2 : 0),
		yStart + (gameState.battle.defaultYAdd * (i + 1) + 400),
		gameState.battle.xDist,
		gameState.battle.yDist
	};
	t_SpriteData *sData = GetSprite(1);
	Sprite add(sData->texture, dest, &sData->srect, NULL, 0, FLIP_NONE);
	sprites.push_back(add);
	if (gmu.height != 0)
		spriteAmount += gmu.height / gameState.battle.yHeightAdd;
	for (int k = 0; k < spriteAmount; k++)
	{
		SDL_Rect dest = {
			xStart + (gameState.battle.xDist * j) + (everyOther == true ? gameState.battle.xDist / 2 : 0),
			yStart + (gameState.battle.defaultYAdd * i) - (gmu.height - (gameState.battle.yHeightAdd * (spriteAmount - k))),
			gameState.battle.xDist,
			gameState.battle.yDist
		};
		t_SpriteData *sData;
		if (k == 0 && gmu.height == 0)
			sData = GetSprite(0);
		else if (k == spriteAmount - 1)
			sData = GetSprite(2);
		else
			sData = GetSprite(1);
		Sprite add(sData->texture, dest, &sData->srect, NULL, 0, FLIP_NONE);
		sprites.push_back(add);
	}
}

void BattleGround::CreateBattleGround(std::vector<std::vector<t_GMU>> &map)
{
	if (map.size() == 0)
	{
		printf("battleGround: map with no size\n");
		return ;
	}
	unsigned int width = map[0].size() * gameState.battle.xDist;
	unsigned int height = map.size() * gameState.battle.defaultYAdd;
	int xStart = -(width / 2), yStart = -(height / 2);
	bool everyOther = false;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			AddGroundSprite(xStart, yStart, everyOther, map[i][j], i, j);
		}
		if (everyOther)
			everyOther = false;
		else
			everyOther = true;
	}
	for (int i = 0; i < sprites.size(); i++)
		gameState.render->AddSprite(&sprites[i], layer);
}

void CreateGroundTest()
{
	t_GMU gmu = { 0, 0 };
	t_GMU one = { 0, 3000 };
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tst = {gmu, gmu, gmu, one, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<std::vector<t_GMU>> ts = {tsts, tsts, tsts, tsts, tst, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tst};
	gameState.battle.ground->CreateBattleGround(ts);
}
