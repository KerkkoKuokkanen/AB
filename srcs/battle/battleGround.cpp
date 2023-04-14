
#include "../../hdr/global.h"

//512, 320

BattleGround::BattleGround(unsigned int layer, SDL_Renderer *rend)
{
	t_SpriteData add;
	add.texture = get_texture(rend, "sprites/Grass1_Color.png");
	add.srect = {0, 0, 2048, 2048};
	tiles.push_back(add);
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
	unsigned int height = map.size() * gameState.battle.yDist;
	int xStart = -(width / 2), yStart = -(height / 2);
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			SDL_Rect dest = {
				xStart + (gameState.battle.xDist * j),
				yStart + (gameState.battle.yDist * i),
				gameState.battle.xDist,
				gameState.battle.yDist
			};
			t_SpriteData *sData = GetSprite();
			Sprite add(sData->texture, dest, &sData->srect, NULL, 0, FLIP_NONE);
			sprites.push_back(add);
		}
	}
	for (int i = 0; i < sprites.size(); i++)
		gameState.render->AddSprite(&sprites[i], layer);
}

void CreateGroundTest()
{
	t_GMU gmu = {0};
	std::vector<t_GMU> tsts = {gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu, gmu};
	std::vector<std::vector<t_GMU>> ts = {tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts, tsts};
	gameState.battle.ground->CreateBattleGround(ts);
}
