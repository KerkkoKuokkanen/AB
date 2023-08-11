
#include "../../../hdr/global.h"

void CreateParticlesForSmokeEffect(SDL_Point pos)
{
	SetScreenShake(500, 4);
	SDL_Rect dest = gameState.battle.ground->getTileDest(pos);
	Vector place(dest.x + 3150, dest.y + 2300);
	for (int i = 0; i < 50; i++)
	{
		int lifeTime = rand() % 40 + 60;
		float angle = float_rand() * (PI / 1.8f);
		angle = (rand() % 2 == 0) ? angle : -angle;
		float speed = (float)(rand() % 500 + 200);
		Vector dir(0.0f, -1.0f);
		int colVal = rand() % 80 + 170;
		Color col(colVal, colVal, colVal);
		vectorRotate(dir, angle);
		float yAdd = float_rand() / 50.0f;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, col,
											Color(10, 10, 10), lifeTime, 1.05f, false, yAdd);
	}
}

void SmokeEffect::CheckIfDone()
{
	if (character != NULL && character->killed == false)
	{
		if (!turn && character->turn)
		{
			turn = true;
			time -= 1;
		}
		else if (turn && !character->turn)
			turn = false;
		return ;
	}
	if (!turn && gameState.updateObjs.turnOrder->turnStartActive)
	{
		turn = true;
		time -= 1;
	}
	else if (turn && !gameState.updateObjs.turnOrder->turnStartActive)
		turn = false;
}

SmokeEffect::SmokeEffect(Character *character, t_Ability *ability, SDL_Point pos)
{
	SmokeEffect::character = character;
	SmokeEffect::pos = pos;
	t_LastingEffect *use = (t_LastingEffect*)ability->stats;
	time = use->turns;
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
	firstSmoke->setDepth(height * BATTLE_DEPTH_UNIT + 2.5f);
	secondSmoke->setDepth((float)height * (float)BATTLE_DEPTH_UNIT + 7.5f);
	orientation = 0;
	CreateParticlesForSmokeEffect(pos);
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
	if (done)
		return ;
	if (gameState.updateObjs.characterAnimIter == 50)
		SwitchOrdering();
	if (!gameState.battle.ground->map[pos.y][pos.x].active || gameState.modes.filterMode == 1)
	{
		firstSmoke->AlphaMod(35);
		secondSmoke->AlphaMod(35);
	}
	else
	{
		firstSmoke->ClearAlphaMod();
		secondSmoke->ClearAlphaMod();
	}
	CheckIfDone();
	if (time <= 0)
		done = true;
}

void SmokeEffect::Destroy()
{
	delete firstSmoke;
	delete secondSmoke;
}
