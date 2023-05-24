
#include "../../hdr/global.h"

CharacterUI::CharacterUI()
{
	SDL_Rect dest1 = {-25000, 44000, 50000, 3200};
	SDL_Rect dest2 = {-25000, 40500, 50000, 3200};
	health = new Bar(dest1);
	armor = new Bar(dest2);
	SDL_Rect but = {21270, 35800, 3300, 3300};
	for (int i = 0; i < BUTTON_RESERVE; i++)
	{
		buttons[i].button = new Button(gameState.textures.turnDone, but, but);
		buttons[i].button->Deactivate();
		buttons[i].buttonSign = 0;
		buttons[i].used = false;
		if (i == 0)
			buttons[i].used = true;
	}
	Vector pos(-24500.0f, 36000.0f);
	float diff = 2100.0f;
	for (int i = 0; i < ENERGYS; i++)
	{
		energys[i] = new Energy;
		energys[i]->Position(Vector(pos.x + (diff * i), pos.y));
	}
	active = true; // change later when something else than only battle
}

void CharacterUI::GetAbilities()
{
	if (activeCharacter == NULL)
		return ;
}

void CharacterUI::DeactivateUI()
{
	health->Deactivate();
	armor->Deactivate();
	for (int i = 0; i< BUTTON_RESERVE; i++)
		buttons[i].button->Deactivate();
	for (int i = 0; i < ENERGYS; i++)
		energys[i]->Deactivate();
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
		activeCharacter = characters[index];
		for (int i = 0; i < BUTTON_RESERVE; i++)
		{
			if (buttons[i].used)
				buttons[i].button->Activate();
		}
		for (int i = 0; i < ENERGYS; i++)
		{
			energys[i]->Activate();
			if (i >= activeCharacter->moves)
				energys[i]->Used();
		}
		turnActive = true;
		return ;
	}
	if (!outCome && turnActive)
	{
		DeactivateUI();
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
		DeactivateUI();
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

