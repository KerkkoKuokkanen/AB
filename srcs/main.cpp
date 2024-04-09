
#include "../hdr/global.h"

t_GameState gameState;
t_AiMoveMaps moveMaps;

void TempInitBattle()
{
	Character thief(BIG_THUG);
	Character thief1(THIEF);
	Character thief2(THIEF);
	Character skele(BIG_THUG, false);
	Character skele2(THUG, false);
	Character skele3(THUG, false);
	static std::vector<Character> chars = {thief1, thief2, skele, skele2, skele3};
	SDL_Point point = {5, 11};
	SDL_Point point1 = {6, 11};
	SDL_Point point2 = {4, 11};
	SDL_Point point4 = {3, 12};
	SDL_Point point5 = {5, 13};
	SDL_Point possi = {4, 12};
	static std::vector<SDL_Point> pnt = {point4, possi, point, point1, point5};
	gameState.battle.ground->StartBattle(chars, pnt);
	gameState.updateObjs.UI->SetCharacters(chars);
	new TurnOrder(chars);
	gameState.updateObjs.abilities->SetMap();
	static OBJ_Update objUpdate;
	gameState.updateObjs.objUpdate = &objUpdate;
	ResetStatusUpdates();
}

void StartBattle()
{
	TempInitBattle();
	static Object nree(ObjectSigns::TREE, {0, 0});
	static Object bree(ObjectSigns::TREE, {3, 8});
	static Object cree(ObjectSigns::BUSH, {1, 10});
	static Object dree(ObjectSigns::STUMP, {5, 14});
	static Object gree(ObjectSigns::DEAD_TREE, {5, 6});
	static Object lree(ObjectSigns::DEAD_TREE, {4, 5});
	static Object p1ree(ObjectSigns::DEAD_TREE, {2, 0});
	static Object p2ree(ObjectSigns::DEAD_TREE, {2, 2});
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
}

int MainLoop()
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
	return (0);
}

int main()
{
	init(&gameState.wr);
	MainLoop();
	return (0);
}
