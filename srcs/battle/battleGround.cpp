
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
	BattleGround::layer = layer;
}

t_SpriteData *BattleGround::GetSprite(int sprite)
{
	
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
	for (int i = 0; i < map.size(); i++)
	{
		unsigned int width = map[i].size() * gameState.battle.xDist;
		xStart = -(width / 2);
		for (int j = 0; j < map[i].size(); j++)
		{
			
		}
		everyOther = (everyOther) ? false : true;
	}
	for (int i = 0; i < sprites.size(); i++)
		gameState.render->AddSprite(&sprites[i], layer);
}

void CreateGroundTest()
{
	t_GMU gmu = { 0, 0 };
	t_GMU one = { 0, 1 };
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<t_GMU> tst = {gmu, gmu, gmu, one, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<std::vector<t_GMU>> ts = {tsts, tsts, tsts, tsts, tst, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tst};
	gameState.battle.ground->CreateBattleGround(ts);
}
