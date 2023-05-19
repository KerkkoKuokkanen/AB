
#include "../hdr/global.h"

t_GameState gameState;

void TempInitBattle()
{
	Character thief(THIEF);
	Character thief2(THIEF);
	Character skele(SKELE, false);
	Character skele2(SKELE, false);
	Character thief3(THIEF);
	Character thief4(THIEF);
	Character skele3(SKELE, false);
	Character skele4(SKELE, false);
	Character skele5(SKELE, false);
	Character skele6(SKELE, false);
	static std::vector<Character> chars = {thief, thief2, skele, skele2, thief3, thief4, skele3, skele4, skele5, skele6};
	SDL_Point point = {8, 6};
	SDL_Point point2 = {3, 12};
	SDL_Point point3 = {9, 2};
	SDL_Point point4 = {8, 14};
	SDL_Point point5 = {7, 6};
	SDL_Point point6 = {2, 12};
	SDL_Point point7 = {9, 5};
	SDL_Point point8 = {1, 1};
	SDL_Point point9 = {0, 0};
	SDL_Point point10 = {3, 3};
	static std::vector<SDL_Point> pnt = {point, point2, point3, point4, point5, point6, point7, point8, point9, point10};
	gameState.battle.ground->StartBattle(chars, pnt);
	new TurnOrder(chars);
}

int MainLoop(t_wr &wr)
{
	clock_t start, end;
	TempInitBattle();
	bool killed = false;
	while (1)
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
