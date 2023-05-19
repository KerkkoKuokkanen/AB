
#include "../../hdr/global.h"

CharacterUI::CharacterUI()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
		characters.push_back(gameState.battle.ground->characters[i].character);
	SDL_Rect dest1 = {
		rounding((float)gameState.screen.width / 3.725f),
		gameState.screen.height - rounding((float)gameState.screen.height / 10.0f) + rounding((float)gameState.screen.height / 22.0f),
		rounding((float)gameState.screen.width / 2.2f),
		rounding((float)gameState.screen.height / 20.0f)
	};
	SDL_Rect dest2 = {
		rounding((float)gameState.screen.width / 3.725f),
		gameState.screen.height - rounding((float)gameState.screen.height / 7.5f) + rounding((float)gameState.screen.height / 22.0f),
		rounding((float)gameState.screen.width / 2.2f),
		rounding((float)gameState.screen.height / 20.0f)
	};
	health = new Bar(dest1);
	armor = new Bar(dest2);
	active = true; // change later when something else than only battle
}

void CharacterUI::Update()
{
	health->Update(100, 100, 99, 10, 9);
	armor->Update(100, 100, 64, 64, 64);
}

void CharacterUI::Destroy()
{
	characters.clear();
	health->Destroy();
	armor->Destroy();
	delete health;
	delete armor;
}

