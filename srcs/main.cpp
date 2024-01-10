
#include "../hdr/global.h"

t_GameState gameState;
t_AiMoveMaps moveMaps;

void TempInitBattle()
{
	Character thief(THIEF);
	Character skele(THIEF, false);
	static std::vector<Character> chars = {thief, skele};
	SDL_Point point = {5, 11};
	SDL_Point point2 = {8, 11};
	static std::vector<SDL_Point> pnt = {point, point2};
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
