
#include "../../hdr/global.h"

bool ControlSetter::CheckIfCanDo()
{
	if (gameState.updateObjs.abilities->active || gameState.updateObjs.turnOrder->turnStartActive ||
		gameState.updateObjs.turnOrder->turnChange)
		return (false);
	return (true);
}

Character *ControlSetter::CheckActiveCharacter()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *used = gameState.battle.ground->characters[i].character;
		if (used->clicked && !used->killed)
			return (used);
	}
	return (NULL);
}

bool ControlSetter::CheckValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	if (gameState.battle.ground->map[pos.y][pos.x].blocked && gameState.battle.ground->map[pos.y][pos.x].character == NULL)
		return (false);
	if (gameState.battle.ground->map[pos.y][pos.x].character != NULL && gameState.battle.ground->map[pos.y][pos.x].character->ally == character->ally)
		return (false);
	return (true);
}

void ControlSetter::CreateSingle(SDL_Point pos)
{
	Control *add = new Control(pos, character->ally);
	controls.push_back(add);
}

void ControlSetter::CreateControlsFromPostion(SDL_Point pos)
{
	int xLeft = getXToLeft(pos);
	int xRight = getXToRight(pos);
	SDL_Point pos1 = {xLeft, pos.y - 1};
	SDL_Point pos2 = {xLeft, pos.y + 1};
	SDL_Point pos3 = {xRight, pos.y - 1};
	SDL_Point pos4 = {xRight, pos.y + 1};
	if (CheckValid(pos1))
		CreateSingle(pos1);
	if (CheckValid(pos2))
		CreateSingle(pos2);
	if (CheckValid(pos3))
		CreateSingle(pos3);
	if (CheckValid(pos4))
		CreateSingle(pos4);
}

void ControlSetter::CreatePhantomControls()
{
	t_Ability *ability = NULL;
	for (int i = 0; i < character->abilities.size(); i++)
	{
		if (character->abilities[i].type == PHANTOM_KNIGHT)
		{
			ability = &character->abilities[i];
			break ;
		}
	}
	if (ability == NULL)
		return ;
	t_PhantomKnight *used = (t_PhantomKnight*)ability->stats;
	if (!used->opportunity)
		return ;
	for (int i = 0; i < gameState.updateObjs.abilities->effectUpdater.effects.size(); i++)
	{
		t_AbilityEffect *effect = &gameState.updateObjs.abilities->effectUpdater.effects[i];
		if (effect->ability->type == PHANTOM_KNIGHT)
		{
			PhantomKnight *phant = (PhantomKnight*)effect->effect;
			if (phant->character == character)
				CreateControlsFromPostion(phant->position);
		}
	}
}

void ControlSetter::AddAdditionalControls()
{
	if (character->cSing != KNIGHT)
		return ;
	if (character->statuses.controlZone <= 0)
		return ;
	SDL_Point pos = character->position;
	SDL_Point checks[8] = {
		GetPositionFromCoordinates(pos, {-2, -2}),
		GetPositionFromCoordinates(pos, {0, -2}),
		GetPositionFromCoordinates(pos, {2, -2}),
		GetPositionFromCoordinates(pos, {1, 0}),
		GetPositionFromCoordinates(pos, {2, 2}),
		GetPositionFromCoordinates(pos, {0, 2}),
		GetPositionFromCoordinates(pos, {-2, 2}),
		GetPositionFromCoordinates(pos, {-1, 0})
	};
	for (int i = 0; i < 8; i++)
	{
		if (CheckValid(checks[i]))
			CreateSingle(checks[i]);
	}
}

void ControlSetter::CreateControls()
{
	CreateControlsFromPostion(character->position);
	CreatePhantomControls();
	AddAdditionalControls();
}

void ControlSetter::Update()
{
	if (!CheckIfCanDo())
	{
		ClearControlled();
		return ;
	}
	Character *used = CheckActiveCharacter();
	if (used == NULL)
	{
		ClearControlled();
		return ;
	}
	if (used->moving || used->damaged)
	{
		ClearControlled();
		return ;
	}
	if (used == character)
	{
		for (int i = 0; i < controls.size(); i++)
			controls[i]->Update();
		return ;
	}
	ClearControlled();
	character = used;
	CreateControls();
}

void ControlSetter::ClearControlled()
{
	for (int i = 0; i < controls.size(); i++)
		delete controls[i];
	controls.clear();
	character = NULL;
}

void ControlSetter::Destroy()
{
	ClearControlled();
}
