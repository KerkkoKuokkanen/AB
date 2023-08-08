
#include "../hdr/global.h"

t_GameState gameState;

void TempInitBattle()
{
	Character thief(LION);
	Character thief2(PYRO);
	Character skele(SKELE, false);
	Character skele2(SKELE, false);
	Character thief3(THIEF);
	Character thief4(THIEF);
	Character skele3(SKELE, false);
	Character skele6(SKELE, false);
	static std::vector<Character> chars = {thief, thief2, skele, skele2, thief3, thief4, skele3, skele6};
	SDL_Point point = {8, 6};
	SDL_Point point2 = {3, 12};
	SDL_Point point3 = {9, 2};
	SDL_Point point4 = {8, 10};
	SDL_Point point5 = {7, 6};
	SDL_Point point6 = {2, 12};
	SDL_Point point7 = {9, 3};
	SDL_Point point10 = {5, 6};
	static std::vector<SDL_Point> pnt = {point, point2, point3, point4, point5, point6, point7, point10};
	gameState.battle.ground->StartBattle(chars, pnt);
	gameState.updateObjs.UI->SetCharacters(chars);
	new TurnOrder(chars);
	gameState.updateObjs.abilities->SetMap();
}

int MainLoop(t_wr &wr)
{
	clock_t start, end;
	TempInitBattle();
	Object nree(ObjectSigns::TREE, {0, 0});
	Object bree(ObjectSigns::TREE, {3, 8});
	Object cree(ObjectSigns::BUSH, {1, 10});
	Object dree(ObjectSigns::STUMP, {5, 14});
	Object gree(ObjectSigns::DEAD_TREE, {5, 7});
	Object lree(ObjectSigns::DEAD_TREE, {4, 5});
	Object p1ree(ObjectSigns::DEAD_TREE, {2, 0});
	Object p2ree(ObjectSigns::DEAD_TREE, {2, 2});
	while (true)
	{
		start = clock();
		Utility();
		gameState.battle.ground->Update();
		if (gameState.keys.space == 1)
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
	t_wr wr;
	init(&wr);
	MainLoop(wr);
	return (0);
}
