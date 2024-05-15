
#include "../hdr/global.h"
#include "../hdr/ow/owHeader.h"

t_GameState gameState;
t_AiMoveMaps moveMaps;

void TempInitBattle()
{
	Character *thief = new Character(THIEF);
	Character *thief1 = new Character(LION);
	Character *skele = new Character(THUG, false);
	Character *skele4 = new Character(THUG, false);
	Character *skele5 = new Character(THUG, false);
	static std::vector<Character*> chars = {thief1, thief, skele, skele4, skele5};
	SDL_Point point = {5, 11};
	SDL_Point point1 = {6, 11};
	SDL_Point point11 = {7, 11};
	SDL_Point point2 = {3, 11};
	SDL_Point point4 = {2, 12};
	SDL_Point point5 = {5, 13};
	SDL_Point possi = {3, 12};
	SDL_Point tester = {5, 12};
	std::vector<SDL_Point> pnt = {point2, point4, point, tester, point1};
	gameState.battle.ground->StartBattle(chars, pnt);
	gameState.updateObjs.UI->SetCharacters(chars);
	new TurnOrder(chars);
	gameState.updateObjs.abilities->SetMap();
	gameState.updateObjs.objUpdate = new OBJ_Update;
	ResetStatusUpdates();
}

void StartBattle()
{
	TempInitBattle();
	new Object(ObjectSigns::TREE, {0, 0});
	new Object(ObjectSigns::TREE, {3, 8});
	new Object(ObjectSigns::BUSH, {1, 10});
	new Object(ObjectSigns::STUMP, {5, 14});
	new Object(ObjectSigns::DEAD_TREE, {5, 6});
	new Object(ObjectSigns::DEAD_TREE, {4, 5});
	new Object(ObjectSigns::DEAD_TREE, {2, 0});
	new Object(ObjectSigns::DEAD_TREE, {2, 2});
	Sprite *filter = new Sprite(gameState.textures.filter, {-60000, -60000, 150000, 110000}, NULL, NULL, 0, FLIP_NONE, true);
	filter->AlphaMod(15);
	filter->ColorMod(1, 1, 1);
	gameState.render->AddSprite(filter, FILTER_LAYER);
	Sprite *backGround = new Sprite(gameState.textures.backGround, {-60000, -60000, 150000, 110000}, NULL, NULL, 0, FLIP_NONE, true);
	backGround->ColorMod(28, 28, 28);
	gameState.render->AddSprite(backGround, BACK_GROUND);
	CreateTheMoveMaps();
	InitObjHolder();
	gameState.updateObjs.info->InitInfo();
	gameState.backGround = backGround;
}

void MainLoop()
{
	clock_t start, end;
	StartBattle();
	while (true)
	{
		start = clock();
		Utility();
		AiManaging();
		if (CheckForTurnChange())
			gameState.updateObjs.turnOrder->ActivateTurnChange();
		ObjUpdate();
		gameState.render->RenderAll();
		end = clock();
		SDL_Delay(figure_the_delay(start, end));
	}
}

void Battle()
{
	InitBattle();
	MainLoop();
}

int main()
{
	init(&gameState.wr);
	//OverWorldLoop();
	Battle();
	return (0);
}
