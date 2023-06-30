
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
		buttons[i].energyCost = 0;
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

int CharacterUI::GetButtonIndex()
{
	int ret = 0;
	for (int i = 0; i < BUTTON_RESERVE; i++)
	{
		if (!buttons[i].used)
		{
			ret = i;
			break ;
		}
	}
	return (ret);
}

void CharacterUI::CreateButton(SDL_Rect dest, SDL_Texture *text, int sign, int cost)
{
	int index = GetButtonIndex();
	buttons[index].buttonSign = sign;
	buttons[index].used = true;
	buttons[index].button->SetTexture(text);
	buttons[index].button->SetDest(dest);
	buttons[index].button->SetClickBox(dest);
	buttons[index].energyCost = cost;
}

void CharacterUI::GetAbilities()
{
	if (activeCharacter == NULL)
		return ;
	Vector pos(-24500.0f, 36000.0f);
	SDL_Rect dest = {21270, 35800, 3300, 3300};
	int diff = 2900;
	for (int i = 0; i < activeCharacter->abilities.size(); i++)
	{
		dest.x = 21270 - (diff * (7 - i));
		if (i >= 7)
		{
			dest.x = 21270 - (diff * (14 - i));
			dest.y = 31100;
		}
		switch (activeCharacter->abilities[i].type)
		{
			case DAGGER_THROW:
				CreateButton(dest, gameState.textures.thiefAbilites[0], DAGGER_THROW, activeCharacter->abilities[i].cost);
				break ;
			case SMOKE_BOMB:
				CreateButton(dest, gameState.textures.thiefAbilites[1], SMOKE_BOMB, activeCharacter->abilities[i].cost);
				break ;
		}
	}
}

void CharacterUI::DeactivateUI()
{
	overCharacterUI = false;
	health->Deactivate();
	armor->Deactivate();
	for (int i = 0; i< BUTTON_RESERVE; i++)
		buttons[i].button->Deactivate();
	for (int i = 0; i < ENERGYS; i++)
		energys[i]->Deactivate();
}

void CharacterUI::getActive()
{
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
	if (gameState.updateObjs.turnOrder->stuffWithOutMove)
		outCome = false;
	if (outCome && !turnActive)
	{
		health->Activate();
		armor->Activate();
		if (activeCharacter != characters[index])
		{
			activeCharacter = characters[index];
			for (int i = 1; i < BUTTON_RESERVE; i++)
				buttons[i].used = false;
			GetAbilities();
		}
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

bool CharacterUI::NoOneKilled()
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i]->killed)
			return (false);
	}
	return (true);
}

void CharacterUI::ShowEnergy(int cost)
{
	if (cost == 0)
		return ;
	if (cost > activeCharacter->moves)
		return ;
	int start = activeCharacter->moves - 1;
	for (int i = 0; i < cost; i++)
	{
		energys[start]->energy->ClearColorMod();
		start--;
	}
}

void CharacterUI::UseEnergy(int cost)
{
	if (cost == 0 || cost > activeCharacter->moves)
		return ;
	int start = activeCharacter->moves - 1;
	for (int i = 0; i < cost; i++)
	{
		energys[start]->Used(true);
		start--;
	}
	activeCharacter->moves -= cost;
}

t_Ability *CharacterUI::GetCharacterAbility(int type)
{
	for (int i = 0; i < activeCharacter->abilities.size(); i++)
	{
		if (activeCharacter->abilities[i].type == type)
			return (&activeCharacter->abilities[i]);
	}
	return (NULL);
}

void CharacterUI::ClearEnergys()
{
	if (gameState.updateObjs.abilities->active)
		return ;
	for (int i = 0; i < ENERGYS; i++)
		energys[i]->energy->ColorMod(190, 190, 190);
}

void CharacterUI::Update()
{
	overCharacterUI = false;
	getActive();
	if (!turnActive)
		return ;
	int h = activeCharacter->stats.health, heal = activeCharacter->stats.maxHealth;
	int a = activeCharacter->stats.armor, arm = activeCharacter->stats.maxArmor;
	health->Update(heal, h, 99, 10, 9);
	armor->Update(arm, a, 64, 64, 64);
	CheckIfMouseOver();
	for (int i = 0; i < BUTTON_RESERVE && !activeCharacter->moving; i++)
	{
		if (buttons[i].used)
		{
			buttons[i].button->ClearColor();
			if (!overCharacterUI)
				HandleButtonAction(buttons[i].button->Update(), i);
		}
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

void CharacterUI::CheckIfMouseOver()
{
	const SDL_Rect temp1 = {-25000, 44000, 50000, 3200};
	const SDL_Rect temp2 = {-25000, 40500, 50000, 3200};
	const SDL_FRect hold1 = staitcTranslateSprite(temp1);
	const SDL_FRect hold2 = staitcTranslateSprite(temp2);
	const SDL_Rect dest1 = {(int)hold1.x, (int)hold1.y, (int)hold1.w, (int)hold1.h};
	const SDL_Rect dest2 = {(int)hold2.x, (int)hold2.y, (int)hold2.w, (int)hold2.h};
	int x = gameState.keys.staticMouseX, y = gameState.keys.staticMouseY;
	if (MenuHoverCheck(gameState.surfaces.bar[0], dest1, x, y))
	{
		overCharacterUI = true;
		return ;
	}
	if (MenuHoverCheck(gameState.surfaces.bar[0], dest2, x, y))
	{
		overCharacterUI = true;
		return ;
	}
	if (MenuHoverCheck(gameState.surfaces.bar[1], dest1, x, y))
	{
		overCharacterUI = true;
		return ;
	}
	if (MenuHoverCheck(gameState.surfaces.bar[1], dest2, x, y))
	{
		overCharacterUI = true;
		return ;
	}
	for (int i = 0; i < ENERGYS; i++)
	{
		const SDL_Rect tmp1 = energys[i]->stand->dest;
		const SDL_FRect hld1 = staitcTranslateSprite(tmp1);
		const SDL_Rect dst1 = {(int)hld1.x, (int)hld1.y, (int)hld1.w, (int)hld1.h};
		if (MenuHoverCheck(gameState.surfaces.energy[0], dst1, x, y))
		{
			overCharacterUI = true;
			return ;
		}
		if (energys[i]->energy->getStatus())
		{
			const SDL_Rect tmp2 = energys[i]->energy->dest;
			const SDL_FRect hld2 = staitcTranslateSprite(tmp2);
			const SDL_Rect dst2 = {(int)hld2.x, (int)hld2.y, (int)hld2.w, (int)hld2.h};
			if (MenuHoverCheck(gameState.surfaces.energy[1], dst2, x, y))
			{
				overCharacterUI = true;
				return ;
			}
		}
	}
}

void CharacterUI::HandleButtonAction(int value, int buttonIndex)
{
	if (value == NO_CONTACT)
		return ;
	overCharacterUI = true;
	if (gameState.updateObjs.abilities->active)
		return ;
	if (buttons[buttonIndex].energyCost != 0 && buttons[buttonIndex].energyCost < activeCharacter->moves)
		ShowEnergy(buttons[buttonIndex].energyCost);
	switch (buttons[buttonIndex].buttonSign)
	{
		case 0:
			if (value == BUTTON_PRESS)
				gameState.updateObjs.turnOrder->ActivateTurnChange();
			break ;
		case DAGGER_THROW:
			if (value == BUTTON_PRESS && buttons[buttonIndex].energyCost <= activeCharacter->moves)
			{
				gameState.updateObjs.abilities->Clear();
				gameState.updateObjs.turnOrder->ResetClicks();
				gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(DAGGER_THROW), activeCharacter);
			}
			break ;
		case SMOKE_BOMB:
			if (value == BUTTON_PRESS && buttons[buttonIndex].energyCost <= activeCharacter->moves)
			{
				gameState.updateObjs.abilities->Clear();
				gameState.updateObjs.turnOrder->ResetClicks();
				gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SMOKE_BOMB), activeCharacter);
			}
			break ;
	}
}
