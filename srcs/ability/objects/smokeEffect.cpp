
#include "../../../hdr/global.h"

SmokeEffect::SmokeEffect(SDL_Point pos)
{
	SmokeEffect::pos = pos;
	SDL_Rect dest = gameState.battle.ground->GetSprite(pos)->dest;
	tileDest = dest;
	dest.y -= 3700;
	dest.x += 500;
	dest.w -= 900;
	dest.h += 800;
	dest.y += 2000;
	firstSmoke = new Sprite(gameState.textures.smokes[0], dest, NULL, NULL, 0, FLIP_NONE);
	dest.y -= 2750;
	secondSmoke = new Sprite(gameState.textures.smokes[1], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(firstSmoke, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(secondSmoke, BATTLEGROUND_LAYER);
	firstSmoke->AlphaMod(200);
	secondSmoke->AlphaMod(145);
	firstSmoke->orderLayer = pos.y + 1;
	secondSmoke->orderLayer = pos.y;
	int height = gameState.battle.ground->map[pos.y][pos.x].height;
	firstSmoke->setDepth(height * BATTLE_DEPTH_UNIT + 9);
	secondSmoke->setDepth(height * BATTLE_DEPTH_UNIT + 9);
	orientation = 0;
}

void SmokeEffect::SwitchOrdering()
{
	int height = gameState.battle.ground->map[pos.y][pos.x].height;
	if (orientation == 0)
	{
		orientation = 1;
		firstSmoke->Move(Vector(0.0f, -1100.0f));
		firstSmoke->orderLayer = pos.y;
		firstSmoke->AlphaMod(145);
		secondSmoke->Move(Vector(0.0f, 1100.0f));
		secondSmoke->orderLayer = pos.y + 1;
		secondSmoke->AlphaMod(200);
		return ;
	}
	orientation = 0;
	firstSmoke->Move(Vector(0.0f, 1100.0f));
	firstSmoke->orderLayer = pos.y + 1;
	firstSmoke->AlphaMod(200);
	secondSmoke->Move(Vector(0.0f, -1100.0f));
	secondSmoke->orderLayer = pos.y;
	secondSmoke->AlphaMod(145);
}

void SmokeEffect::Update()
{
	if (gameState.updateObjs.characterAnimIter == 50)
		SwitchOrdering();
}

void SmokeEffect::Destroy()
{
	delete firstSmoke;
	delete secondSmoke;
}
