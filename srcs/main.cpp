
#include "../hdr/global.h"

t_GameState gameState;
t_AiMoveMaps moveMaps;

void TempInitBattle()
{
	Character thief(WITCH);
	Character thief1(SMITH);
	Character skele(SKELE, false);
	Character thief2(LION);
	Character thief3(THIEF);
	Character thief4(PYRO);
	Character thief5(MAGE);
	Character thief6(ALCHEMIST);
	Character thief7(RAIDER);
	Character thief8(KNIGHT);
	static std::vector<Character> chars = {thief, thief1, skele, thief2, thief3, thief4, thief5, thief6, thief7, thief8};
	SDL_Point point = {5, 11};
	SDL_Point point1 = {6, 10};
	SDL_Point point2 = {4, 11};
	SDL_Point point3 = {3, 11};
	SDL_Point point4 = {2, 11};
	SDL_Point point5 = {7, 12};
	SDL_Point point6 = {7, 13};
	SDL_Point point7 = {7, 14};
	SDL_Point point8 = {5, 12};
	SDL_Point point9 = {3, 12};
	static std::vector<SDL_Point> pnt = {point, point1, point2, point3, point4, point5, point6, point7, point8, point9};
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
