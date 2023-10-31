
#include "../../hdr/global.h"
#define SCALE_FACTOR 600.0f

CharacterUI::CharacterUI()
{
	SDL_Rect dest1 = {-25000, 44000, 50000, 3200};
	SDL_Rect dest2 = {-25000, 40500, 25000, 3100};
	SDL_Rect dest3 = {0, 40500, 25000, 3100};
	health = new Bar(dest1, true);
	armor = new Bar(dest2, true);
	fatigue = new FatigueBar(dest3, true);
	armor->ChangeTextureToNarrow();
	health->leftNumberOffset = {-500, 300};
	health->rightNumberOffset = {1480, 300};
	health->slash->dest.w += 100;
	armor->slash->dest.y -= 50;
	armor->leftNumberOffset = {-330, 340};
	armor->rightNumberOffset = {1100, 340};
	fatigue->slash->dest.w += 350;
	fatigue->slash->dest.y -= 50;
	fatigue->leftNumberOffset = {-300, 260};
	fatigue->rightNumberOffset = {1200, 260};
	SDL_Rect but = {21800, 35500, 3500, 3500};
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
	Vector pos(-25200.0f, 35800.0f);
	float diff = 2110.0f;
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

void CharacterUI::CreateButton(SDL_Rect dest, SDL_Texture *text, int sign, int cost, int fatigue)
{
	int index = GetButtonIndex();
	buttons[index].buttonSign = sign;
	buttons[index].used = true;
	buttons[index].button->SetTexture(text);
	buttons[index].button->SetDest(dest);
	buttons[index].button->SetClickBox(dest);
	buttons[index].energyCost = cost;
	buttons[index].fatigueCost = fatigue;
}

void CharacterUI::GetAbilities()
{
	if (activeCharacter == NULL)
		return ;
	SDL_Rect dest = {21800, 35500, 3500, 3500};
	int diff = 3075;
	for (int i = 0; i < activeCharacter->abilities.size(); i++)
	{
		dest.x = 21800 - (diff * (7 - i));
		if (i >= 7)
		{
			dest.x = 21800 - (diff * (14 - i));
			dest.y = 30500;
		}
		switch (activeCharacter->abilities[i].type)
		{
			case DAGGER_THROW:
				CreateButton(dest, gameState.textures.thiefAbilites[0], DAGGER_THROW, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case SMOKE_BOMB:
				CreateButton(dest, gameState.textures.thiefAbilites[1], SMOKE_BOMB, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case DAGGER_SLASH:
				CreateButton(dest, gameState.textures.thiefAbilites[2], DAGGER_SLASH, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case FLAME_PORT:
				CreateButton(dest, gameState.textures.pyroAbilities[0], FLAME_PORT, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case FLAME_SLASH:
				CreateButton(dest, gameState.textures.pyroAbilities[1], FLAME_SLASH, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case FLAME_BLAST:
				CreateButton(dest, gameState.textures.pyroAbilities[2], FLAME_BLAST, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case INCINERATE:
				CreateButton(dest, gameState.textures.pyroAbilities[3], INCINERATE, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case LION_SMACK:
				CreateButton(dest, gameState.textures.lionAbilities[0], LION_SMACK, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case PHANTOM_KNIGHT:
				CreateButton(dest, gameState.textures.lionAbilities[1], PHANTOM_KNIGHT, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case ROTATE:
				CreateButton(dest, gameState.textures.lionAbilities[2], ROTATE, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case HAMMER_SMACK:
				CreateButton(dest, gameState.textures.smithAbilities[0], HAMMER_SMACK, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case THROW_TOOLBOX:
				CreateButton(dest, gameState.textures.smithAbilities[1], THROW_TOOLBOX, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case SUPPLY_ALLY:
				CreateButton(dest, gameState.textures.smithAbilities[2], SUPPLY_ALLY, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case SUPPLY:
				CreateButton(dest, gameState.textures.reSupply, SUPPLY, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case GENERIC_TOOL_THROW:
				CreateButton(dest, gameState.textures.throwObj, GENERIC_TOOL_THROW, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case PICK_UP_TOOLS:
				CreateButton(dest, gameState.textures.smithAbilities[3], PICK_UP_TOOLS, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case SMITH_BUFF:
				CreateButton(dest, gameState.textures.smithAbilities[4], SMITH_BUFF, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case LIGHTNING_BOLT:
				CreateButton(dest, gameState.textures.mageAbilities[0], LIGHTNING_BOLT, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case ROCK_FALL:
				CreateButton(dest, gameState.textures.mageAbilities[1], ROCK_FALL, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case HOST_EYES:
				CreateButton(dest, gameState.textures.mageAbilities[2], HOST_EYES, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case AXE_SLASH:
				CreateButton(dest, gameState.textures.raiderAbilities[0], AXE_SLASH, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case AXE_JUMP:
				CreateButton(dest, gameState.textures.raiderAbilities[1], AXE_JUMP, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case TOXIC_BLADE:
				CreateButton(dest, gameState.textures.raiderAbilities[2], TOXIC_BLADE, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case RAIDER_BLOCK:
				CreateButton(dest, gameState.textures.raiderAbilities[3], RAIDER_BLOCK, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case NAIL_BOMB:
				CreateButton(dest, gameState.textures.alchemistAbilities[0], NAIL_BOMB, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case ACID_BOMB:
				CreateButton(dest, gameState.textures.alchemistAbilities[1], ACID_BOMB, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
			case SLOW_BOMB:
				CreateButton(dest, gameState.textures.alchemistAbilities[2], SLOW_BOMB, activeCharacter->abilities[i].cost, activeCharacter->abilities[i].fatigue);
				break ;
		}
	}
}

void CharacterUI::DeactivateUI()
{
	overCharacterUI = false;
	health->Deactivate();
	armor->Deactivate();
	fatigue->Deactivate();
	if (statuses != NULL)
		delete statuses;
	statuses = NULL;
	for (int i = 0; i< BUTTON_RESERVE; i++)
		buttons[i].button->Deactivate();
	for (int i = 0; i < ENERGYS; i++)
		energys[i]->Deactivate();
}

bool CharacterUI::AbilitiesMatch()
{
	for (int i = 0; i < BUTTON_RESERVE; i++)
	{
		if (buttons[i].used == false)
			continue ;
		bool visited = false;
		for (int i = 0; i < activeCharacter->abilities.size(); i++)
		{
			if (buttons[i].buttonSign == activeCharacter->abilities[i].type)
			{
				visited = true;
				break ;
			}
		}
		if (!visited)
			return (false);
	}
	return (true);
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
		fatigue->Activate();
		if (activeCharacter != characters[index])
		{
			activeCharacter = characters[index];
			for (int i = 1; i < BUTTON_RESERVE; i++)
				buttons[i].used = false;
			GetAbilities();
		}
		statuses = new Statuses(activeCharacter, 1900, 1200, 590, true);
		statuses->Postion(Vector(-24800.0f, 32900.0f));
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

void CharacterUI::ShowEnergy(int cost, bool moving)
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
	if (moving)
		fatigue->ShowFatigue(cost * 1.5f);
}

void CharacterUI::UseEnergy(int cost, bool moving)
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
	if (moving)
		activeCharacter->stats.fatigue += cost * 1.5f;
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

void CharacterUI::PollAbilities()
{
	if (activeCharacter == NULL)
		return ;
	for (int i = 1; i < BUTTON_RESERVE; i++)
		buttons[i].used = false;
	GetAbilities();
	for (int i = 1; i < BUTTON_RESERVE; i++)
	{
		buttons[i].button->Deactivate();
		if (buttons[i].used)
			buttons[i].button->Activate();
	}
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
	ManageTurnText();
	if (!turnActive)
		return ;
	PollAbilities();
	health->Update(activeCharacter, true);
	armor->Update(activeCharacter, false);
	fatigue->Update(activeCharacter);
	statuses->Update();
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
	if (gameState.updateObjs.abilities->active && !gameState.updateObjs.abilities->inMotion)
		fatigue->ShowFatigue(gameState.updateObjs.abilities->ability->fatigue);
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
	delete health;
	delete armor;
	if (text == NULL)
		delete text;
	if (texts != NULL)
		SDL_DestroyTexture(texts);
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
	if (statuses->GetMouseOverStatuses())
	{
		overCharacterUI = true;
		return ;
	}
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
	if (buttons[buttonIndex].energyCost != 0 && buttons[buttonIndex].energyCost < activeCharacter->moves)
		ShowEnergy(buttons[buttonIndex].energyCost);
	fatigue->ShowFatigue(buttons[buttonIndex].fatigueCost);
	if (buttons[buttonIndex].buttonSign == 0 && value == BUTTON_PRESS)
	{
		gameState.updateObjs.turnOrder->ActivateTurnChange();
		return ;
	}
	if (value != BUTTON_PRESS || buttons[buttonIndex].energyCost > activeCharacter->moves)
		return ;
	int fat = buttons[buttonIndex].fatigueCost + activeCharacter->stats.fatigue;
	if (fat > activeCharacter->stats.maxFatigue)
		return ;
	switch (buttons[buttonIndex].buttonSign)
	{
		case DAGGER_THROW:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(DAGGER_THROW), activeCharacter);
			break ;
		case SMOKE_BOMB:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SMOKE_BOMB), activeCharacter);
			break ;
		case DAGGER_SLASH:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(DAGGER_SLASH), activeCharacter);
			break ;
		case FLAME_PORT:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(FLAME_PORT), activeCharacter);
			break ;
		case FLAME_SLASH:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(FLAME_SLASH), activeCharacter);
			break ;
		case FLAME_BLAST:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(FLAME_BLAST), activeCharacter);
			break ;
		case INCINERATE:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(INCINERATE), activeCharacter);
			break ;
		case LION_SMACK:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(LION_SMACK), activeCharacter);
			break ;
		case PHANTOM_KNIGHT:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(PHANTOM_KNIGHT), activeCharacter);
			break ;
		case ROTATE:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(ROTATE), activeCharacter);
			break ;
		case HAMMER_SMACK:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(HAMMER_SMACK), activeCharacter);
			break ;
		case THROW_TOOLBOX:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(THROW_TOOLBOX), activeCharacter);
			break ;
		case SUPPLY_ALLY:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SUPPLY_ALLY), activeCharacter);
			break ;
		case PICK_UP_TOOLS:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(PICK_UP_TOOLS), activeCharacter);
			break ;
		case SUPPLY:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SUPPLY), activeCharacter);
			break ;
		case GENERIC_TOOL_THROW:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(GENERIC_TOOL_THROW), activeCharacter);
			break ;
		case SMITH_BUFF:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SMITH_BUFF), activeCharacter);
			break ;
		case LIGHTNING_BOLT:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(LIGHTNING_BOLT), activeCharacter);
			break ;
		case ROCK_FALL:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(ROCK_FALL), activeCharacter);
			break ;
		case HOST_EYES:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(HOST_EYES), activeCharacter);
			break ;
		case AXE_SLASH:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(AXE_SLASH), activeCharacter);
			break ;
		case AXE_JUMP:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(AXE_JUMP), activeCharacter);
			break ;
		case TOXIC_BLADE:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(TOXIC_BLADE), activeCharacter);
			break ;
		case RAIDER_BLOCK:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(RAIDER_BLOCK), activeCharacter);
			break ;
		case NAIL_BOMB:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(NAIL_BOMB), activeCharacter);
			break ;
		case ACID_BOMB:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(ACID_BOMB), activeCharacter);
			break ;
		case SLOW_BOMB:
			gameState.updateObjs.abilities->SetAbility(GetCharacterAbility(SLOW_BOMB), activeCharacter);
			break ;
	}
}
