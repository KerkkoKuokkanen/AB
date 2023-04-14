
#include "../../hdr/global.h"

//512, 320

BattleGround::BattleGround(unsigned int layer, SDL_Renderer *rend)
{
	t_SpriteData add;
	add.texture = get_texture(rend, "sprites/isometric_block(15).png");
	add.srect = {3, 0, 500, 540};
	tiles.push_back(add);
	BattleGround::layer = layer;
}

t_SpriteData *BattleGround::GetSprite()
{
	return (&tiles[0]);
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
		for (int j = 0; j < map[0].size(); j++)
		{
			SDL_Rect dest = {
				xStart + (gameState.battle.xDist * j) + (everyOther == true ? gameState.battle.xDist / 2 : 0),
				yStart + (gameState.battle.defaultYAdd * i),
				gameState.battle.xDist,
				gameState.battle.yDist
			};
			t_SpriteData *sData = GetSprite();
			Sprite add(sData->texture, dest, &sData->srect, NULL, 0, FLIP_NONE);
			sprites.push_back(add);
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
	t_GMU gmu = {0};
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<std::vector<t_GMU>> ts = {tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts};
	gameState.battle.ground->CreateBattleGround(ts);
}
