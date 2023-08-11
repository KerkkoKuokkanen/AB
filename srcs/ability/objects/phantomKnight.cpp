
#include "../../../hdr/global.h"

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
		currText = (currText == 0) ? 1 : 0;
		if (currText == 0)
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

void PhantomKnight::Destroy()
{
	gameState.battle.ground->map[position.y][position.x].blocked = false;
	if (knight != NULL)
		delete knight;
	if (stand != NULL)
		delete stand;
}
