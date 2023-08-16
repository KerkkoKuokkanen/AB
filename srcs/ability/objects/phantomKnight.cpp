
#include "../../../hdr/global.h"
#define PART_AMOUNT 300

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 91)
		return (Color(255, 255, 255));
	if (hit < 70)
		return (Color(0, 76, 255));
	if (hit > 25)
		return (Color(0, 217, 255));
	if (hit > 10)
		return (Color(0, 255, 213));
	return (Color(1, 1, 1));
}

PhantomKnight::PhantomKnight(Character *character, t_Ability *ability, SDL_Point pos)
{
	gameState.battle.ground->map[pos.y][pos.x].blocked = true;
	PhantomKnight::character = character;
	position = pos;
	currentTurn = gameState.updateObjs.turnOrder->turnCount;
	t_PhantomKnight *use = (t_PhantomKnight*)ability->stats;
	hp = use->hits;
	turns = use->turns;
	SDL_Rect tDest = gameState.battle.ground->getTileDest(pos);
	SDL_Rect dest = {tDest.x - 400, tDest.y - 5650, 6800, 8160};
	knight = new Sprite(gameState.textures.chars.lionIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
	stand = new Sprite(gameState.textures.stands.lionStand, dest, NULL, NULL, 0, FLIP_NONE);
	knight->ColorMod(0, 217, 255);
	stand->ColorMod(0, 217, 255);
	knight->AlphaMod(170);
	stand->AlphaMod(170);
	knight->orderLayer = pos.y;
	stand->orderLayer = pos.y;
	int height = gameState.battle.ground->map[pos.y][pos.x].height;
	knight->setDepth((float)height * (float)BATTLE_DEPTH_UNIT + 8.0f);
	stand->setDepth((float)height * (float)BATTLE_DEPTH_UNIT + 7.0f);
	gameState.render->AddSprite(knight, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(stand, BATTLEGROUND_LAYER);
}

void PhantomKnight::UpdateSprites()
{
	if (!gameState.battle.ground->map[position.y][position.x].active || gameState.modes.filterMode == 1)
	{
		knight->AlphaMod(35);
		stand->AlphaMod(35);
	}
	else
	{
		knight->AlphaMod(170);
		stand->AlphaMod(170);
	}
	if (gameState.updateObjs.characterAnimIter == 50)
	{
		if (gameState.updateObjs.characterAnimIndex == 0)
			knight->setTexture(gameState.textures.chars.lionIdle[0]);
		else
			knight->setTexture(gameState.textures.chars.lionIdle[1]);
	}
}

void PhantomKnight::CheckTurns()
{
	if (!cTurn && character->turn)
	{
		turns -= 1;
		cTurn = true;
	}
	else if (cTurn && !character->turn)
		cTurn = false;
}

void PhantomKnight::Update()
{
	if (done)
		return ;
	UpdateSprites();
	CheckTurns();
	if (character == NULL || turns <= 0 || hp <= 0 || character->killed)
		done = true;
}

void PhantomKnight::CreateParticles()
{
	SDL_Point pos = {knight->dest.x + 3100, knight->dest.y + 4000};
	for (int i = 0; i < PART_AMOUNT; i++)
	{
		int xAdd = rand() % 1000;
		int yAdd = rand() % 2600;
		xAdd = (rand() % 2 == 0) ? -xAdd : xAdd;
		yAdd = (rand() % 2 == 0) ? -yAdd : yAdd;
		float angle = float_rand() * (2.0f * PI);
		Vector dir(0.0f, -1.0f);
		vectorRotate(dir, angle);
		float drag = 1.02f + float_rand() * 0.1f;
		float speed = rand() % 160 + 40;
		Vector place((float)(pos.x + xAdd), (float)(pos.y + yAdd));
		int life = rand() % 40 + 60;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), Color(1, 1, 1), life, drag, false);
	}
}

void PhantomKnight::Destroy()
{
	CreateParticles();
	gameState.battle.ground->map[position.y][position.x].blocked = false;
	if (knight != NULL)
		delete knight;
	if (stand != NULL)
		delete stand;
}