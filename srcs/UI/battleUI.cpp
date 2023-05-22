
#include "../../hdr/global.h"

CharacterUI::CharacterUI()
{
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
	SDL_Rect but = {
		rounding((float)gameState.screen.width / 1.455f),
		rounding((float)gameState.screen.height / 1.153f),
		rounding((float)gameState.screen.width / 33.0f),
		rounding((float)gameState.screen.width / 33.0f)
	};
	for (int i = 0; i < BUTTON_RESERVE; i++)
	{
		buttons[i].button = new Button(gameState.textures.turnDone, but, but);
		buttons[i].button->Deactivate();
		buttons[i].buttonSign = 0;
		buttons[i].used = false;
		if (i == 0)
			buttons[i].used = true;
	}
	active = true; // change later when something else than only battle
}

void CharacterUI::GetAbilities()
{
	if (activeCharacter == NULL)
		return ;
	
}

void CharacterUI::getActive()
{
	bool visited = false;
	bool outCome = false;
	int index = 0;
	for (int i = 0; i < characters.size() - 1; i++)
	{
		if (characters[i]->turn && characters[i]->ally)
		{
			index = i;
			outCome = true;
			break ;
		}
	}
	if (gameState.updateObjs.turnOrder->stuffHappening)
		outCome = false;
	if (outCome && !turnActive)
	{
		health->Activate();
		armor->Activate();
		for (int i = 0; i < BUTTON_RESERVE; i++)
		{
			if (buttons[i].used)
				buttons[i].button->Activate();
		}
		turnActive = true;
		activeCharacter = characters[index];
		return ;
	}
	if (!outCome && turnActive)
	{
		health->Deactivate();
		armor->Deactivate();
		for (int i = 0; i< BUTTON_RESERVE; i++)
			buttons[i].button->Deactivate();
		turnActive = false;
	}
}

void CharacterUI::HandleButtonAction(int value, int buttonIndex)
{
	if (value == NO_CONTACT)
		return ;
	switch (buttons[buttonIndex].buttonSign)
	{
		case 0:
			if (value == BUTTON_PRESS)
				gameState.updateObjs.turnOrder->ActivateTurnChange();
			break ;
	}
}

void CharacterUI::Update()
{
	getActive();
	if (!turnActive)
		return ;
	int h = activeCharacter->stats.health, heal = activeCharacter->stats.maxHealth;
	int a = activeCharacter->stats.armor, arm = activeCharacter->stats.maxArmor;
	health->Update(h, heal, 99, 10, 9);
	armor->Update(a, arm, 64, 64, 64);
	for (int i = 0; i < BUTTON_RESERVE; i++)
	{
		if (buttons[i].used)
			HandleButtonAction(buttons[i].button->Update(), i);
	}
}

void CharacterUI::SetCharacters(std::vector<Character> &characters)
{
	for (int i = 0; i < characters.size() - 1; i++)
		CharacterUI::characters.push_back(&characters[i]);
}

void CharacterUI::RemoveCharacter(Character *character)
{
	for (int i = 0; i < characters.size() - 1; i++)
	{
		if (characters[i] == character)
		{
			characters.erase(characters.begin() + i);
			break ;
		}
	}
	if (character == activeCharacter)
	{
		activeCharacter = NULL;
		health->Deactivate();
		armor->Deactivate();
		for (int i = 0; i< BUTTON_RESERVE; i++)
			buttons[i].button->Deactivate();
		turnActive = false;
	}
}

void CharacterUI::Destroy()
{
	characters.clear();
	health->Destroy();
	armor->Destroy();
	delete health;
	delete armor;
}

