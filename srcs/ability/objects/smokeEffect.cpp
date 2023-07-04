
#include "../../../hdr/global.h"

SmokeEffect::SmokeEffect(SDL_Point pos)
{
	SmokeEffect::pos = pos;
	SDL_Rect dest = gameState.battle.ground->GetSprite(pos)->dest;
	tileDest = dest;
	dest.y -= 4800;
	dest.x -= 600;
	dest.w += 1200;
	dest.h += 3700;
	firstSmoke = new Sprite(gameState.textures.smokes[0], dest, NULL, NULL, 0, FLIP_NONE);
	secondSmoke = new Sprite(gameState.textures.smokes[1], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(firstSmoke, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(secondSmoke, BATTLEGROUND_LAYER);
	firstSmoke->AlphaMod(235);
	secondSmoke->AlphaMod(235);
	firstSmoke->orderLayer = pos.y + 1;
	secondSmoke->orderLayer = pos.y;
	int height = gameState.battle.ground->map[pos.y][pos.x].height;
	firstSmoke->setDepth(height * BATTLE_DEPTH_UNIT + 1);
	secondSmoke->setDepth((float)height * (float)BATTLE_DEPTH_UNIT + 7.5f);
	orientation = 0;
}

void SmokeEffect::SwitchOrdering()
{
	if (orientation == 0)
	{
		orientation = 1;
		firstSmoke->setTexture(gameState.textures.smokes[2]);
		secondSmoke->setTexture(gameState.textures.smokes[3]);
		return ;
	}
	orientation = 0;
	firstSmoke->setTexture(gameState.textures.smokes[0]);
	secondSmoke->setTexture(gameState.textures.smokes[1]);
}

void SmokeEffect::Update()
{
	if (gameState.updateObjs.characterAnimIter == 50)
		SwitchOrdering();
	if (!gameState.battle.ground->map[pos.y][pos.x].active)
	{
		firstSmoke->Deactivate();
		secondSmoke->Deactivate();
	}
	else
	{
		firstSmoke->Activate();
		secondSmoke->Activate();
	}
}

void SmokeEffect::Destroy()
{
	delete firstSmoke;
	delete secondSmoke;
}