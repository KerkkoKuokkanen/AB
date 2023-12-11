
#include "../../hdr/global.h"

static bool ValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static Character *GetCharacter(int index, SDL_Point pos)
{
	switch (index)
	{
		case 0:
		{
			int x = getXToLeft(pos);
			int y = pos.y - 1;
			if (ValidPosition({x, y}))
				return (gameState.battle.ground->map[y][x].character);
			break ;
		}
		case 1:
		{
			int x = getXToLeft(pos);
			int y = pos.y + 1;
			if (ValidPosition({x, y}))
				return (gameState.battle.ground->map[y][x].character);
			break ;
		}
		case 2:
		{
			int x = getXToRight(pos);
			int y = pos.y - 1;
			if (ValidPosition({x, y}))
				return (gameState.battle.ground->map[y][x].character);
			break ;
		}
		case 3:
		{
			int x = getXToRight(pos);
			int y = pos.y + 1;
			if (ValidPosition({x, y}))
				return (gameState.battle.ground->map[y][x].character);
			break ;
		}
	}
	return (NULL);
}

void ToolBox::AssignDefaultOnGroundAbilities(Character *target)
{
	if (gameState.updateObjs.abilities->active)
		return ;
	if (!ToolExists(target, SUPPLY) && supplyAmount != 0)
	{
		target->abilities.push_back({SUPPLY, 2, 0, 0, 200, StatStructs::SUPPLY, (-1), 0, 0, NULL});
		int index = target->abilities.size() - 1;
		target->abilities[index].stats = (void*)malloc(sizeof(t_Supply));
		t_Supply *used = (t_Supply*)target->abilities[index].stats;
		used->amount = 30;
	}
	if (!ToolExists(target, GENERIC_TOOL_THROW))
	{
		target->abilities.push_back({GENERIC_TOOL_THROW, 2, 15, 0, 200, StatStructs::THROWABLE, (-1), 0, 0, NULL});
		int index = target->abilities.size() - 1;
		target->abilities[index].stats = (void*)malloc(sizeof(t_Throwable));
		t_Throwable *used = (t_Throwable*)target->abilities[index].stats;
		used->range = 9;
	}
	if (target->cSing == SMITH && !ToolExists(target, PICK_UP_TOOLS))
	{
		target->abilities.push_back({PICK_UP_TOOLS, 0, 5, 0, 200, (-1), (-1), 0, 0, NULL});
		int index = target->abilities.size() - 1;
		target->abilities[index].stats = NULL;
	}
}

void ToolBox::CheckIfInTargetCharacters(Character *target)
{
	for (int i = 0; i < targetCharacters.size(); i++)
	{
		if (targetCharacters[i].target == target)
		{
			targetCharacters[i].found = true;
			return ;
		}
	}
	targetCharacters.push_back({target, true});
}

void ToolBox::RemoveOnGroundAbilities(Character *target)
{
	for (int i = 0; i < target->abilities.size(); i++)
	{
		if (target->abilities[i].type == GENERIC_TOOL_THROW)
		{
			if (target->abilities[i].stats != NULL)
				free(target->abilities[i].stats);
			target->abilities.erase(target->abilities.begin() + i);
		}
	}
	for (int i = 0; i < target->abilities.size(); i++)
	{
		if (target->abilities[i].type == SUPPLY)
		{
			if (target->abilities[i].stats != NULL)
				free(target->abilities[i].stats);
			target->abilities.erase(target->abilities.begin() + i);
		}
	}
	for (int i = 0; i < target->abilities.size(); i++)
	{
		if (target->abilities[i].type == PICK_UP_TOOLS)
		{
			if (target->abilities[i].stats != NULL)
				free(target->abilities[i].stats);
			target->abilities.erase(target->abilities.begin() + i);
		}
	}
}

void ToolBox::ManageOnGroundAbilities()
{
	if (inHand || arch != NULL)
		return ;
	if (gameState.updateObjs.abilities->active)
		return ;
	for (int i = 0; i < targetCharacters.size(); i++)
		targetCharacters[i].found = false;
	for (int i = 0; i < 4; i++)
	{
		Character *ret = GetCharacter(i, targPos);
		if (ret == NULL)
			continue ;
		if (ret->ally == false)
			continue ;
		CheckIfInTargetCharacters(ret);
		AssignDefaultOnGroundAbilities(ret);
	}
	for (int i = 0; i < targetCharacters.size(); i++)
	{
		if (targetCharacters[i].found == false)
		{
			RemoveOnGroundAbilities(targetCharacters[i].target);
			targetCharacters.erase(targetCharacters.begin() + i);
			i--;
			if (targetCharacters.size() == 0)
				i = 0;
		}
	}
}

void ToolBox::ManageToolBoxNotInHand()
{
	if (inHand)
		return ;
	if (sprite->getTexture() != gameState.textures.chars.toolBox)
		sprite->setTexture(gameState.textures.chars.toolBox);
	UpdateThrowArch();
	DisplayToolBoxNumber();
	if (gameState.battle.ground->map[targPos.y][targPos.x].active == false && arch == NULL)
		sprite->AlphaMod(35);
	else
		sprite->ClearAlphaMod();
}
