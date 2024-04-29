
#include "../../../hdr/global.h"

void CreateTheMoveMaps()
{
	int height = gameState.battle.ground->map.size();
	int width = gameState.battle.ground->map[0].size();
	moveMaps.abilities = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	moveMaps.staticMoves = (t_MovementMap**)malloc(sizeof(t_MovementMap*) * height);
	for (int i = 0; i < height; i++)
	{
		moveMaps.abilities[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		moveMaps.staticMoves[i] = (t_MovementMap*)malloc(sizeof(t_MovementMap) * width);
		for (int j = 0; j < width; j++)
		{
			SDL_Point pos = {j, i};
			moveMaps.abilities[i][j].start = pos;
			moveMaps.staticMoves[i][j].start = pos;
			moveMaps.abilities[i][j].map = (int**)malloc(sizeof(int*) * height);
			moveMaps.staticMoves[i][j].map = (int**)malloc(sizeof(int*) * height);
			for (int k = 0; k < height; k++)
			{
				moveMaps.abilities[i][j].map[k] = (int*)malloc(sizeof(int) * width);
				moveMaps.staticMoves[i][j].map[k] = (int*)malloc(sizeof(int) * width);
			}
			findMovables(moveMaps.abilities[i][j].map, 200, pos);
			findMovablesStatic(moveMaps.staticMoves[i][j].map, 200, pos);
		}
	}
}

void CopyStatusesFromTheCharacter(t_AiCharacter *aiChar, Character *character)
{
	for (int i = 0; i < character->statuses.bleed.size(); i++)
		aiChar->statuses.bleed.push_back(character->statuses.bleed[i]);
	for (int i = 0; i < character->statuses.buffs.size(); i++)
		aiChar->statuses.buffs.push_back(character->statuses.buffs[i]);
	for (int i = 0; i < character->statuses.burns.size(); i++)
		aiChar->statuses.burns.push_back(character->statuses.burns[i]);
	for (int i = 0; i < character->statuses.deBuffs.size(); i++)
		aiChar->statuses.deBuffs.push_back(character->statuses.deBuffs[i]);
	for (int i = 0; i < character->statuses.poison.size(); i++)
		aiChar->statuses.poison.push_back(character->statuses.poison[i]);
	for (int i = 0; i < character->statuses.toxicBlade.size(); i++)
		aiChar->statuses.toxicBlade.push_back(character->statuses.toxicBlade[i]);
	aiChar->statuses.hosting = character->statuses.hosting;
	aiChar->statuses.hosted = character->statuses.hosted;
	aiChar->statuses.controlZone = character->statuses.controlZone;
	aiChar->statuses.stun = character->statuses.stun;
	aiChar->statuses.slowed = character->statuses.slowed;
	aiChar->statuses.frenzy = character->statuses.frenzy;
}

static t_AiCharacter *SetTheCharacter(Character *character)
{
	if (character == NULL)
		return (NULL);
	t_AiCharacter *used = GetAiCharacterFromHolder();
	used->alive = !character->killed;
	used->armor = character->stats.armor;
	used->health = character->stats.health;
	used->fatigue = character->stats.fatigue;
	used->moves = character->moves;
	used->character = character;
	used->position = character->position;
	CopyStatusesFromTheCharacter(used, character);
	return (used);
}

static t_AiMapObj SetTheObj(Object *obj)
{
	t_AiMapObj ret;
	if (obj == NULL)
	{
		ret.obj = false;
		ret.size = 0;
		return (ret);
	}
	ret.obj = true;
	ret.size = obj->size;
	return (ret);
}

t_AiCharacter *GetTheStartingTurnForAi(t_AiMapUnit **map)
{
	Character *used = NULL;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->turn)
		{
			used = gameState.battle.ground->characters[i].character;
			break ;
		}
	}
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (map[i][j].character == NULL)
				continue ;
			if (map[i][j].character->character == used)
			{
				if (map[i][j].character->character->killed)
					return (NULL);
				return (map[i][j].character);
			}
		}
	}
	return (NULL);
}

static int **GetMoveMap()
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	int **ret = (int**)malloc(sizeof(int*) * h);
	for (int i = 0; i < h; i++)
		ret[i] = (int*)malloc(sizeof(int) * w);
	return (ret);
}

void FreeMoveMap(int **map)
{
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
		free(map[i]);
	free(map);
}

void GetAiMapMoves(t_AiCharacter *aiChar, t_AiMapUnit **map)
{
	SDL_Point pos = aiChar->position;
	int moves = aiChar->moves;
	if (aiChar->statuses.slowed != 0)
		moves /= 2;
	findMovablesNormal(map, moves, pos);
}

static void SetSmokeAdd(t_AiMapUnit &unit, SDL_Point pos)
{
	if (!CheckIfSmoked(pos))
	{
		unit.adds.smoke = {false, 0, NULL};
		return ;
	}
	for (int i = 0; i < gameState.updateObjs.abilities->effectUpdater.effects.size(); i++)
	{
		t_AbilityEffect &effect = gameState.updateObjs.abilities->effectUpdater.effects[i];
		if (effect.ability->type == SMOKE_BOMB && effect.pos.x == pos.x && effect.pos.y == pos.y)
		{
			SmokeEffect *used = (SmokeEffect*)effect.effect;
			int ret = used->getTime();
			Character *thh = used->getCharacter();
			unit.adds.smoke = {true, ret, thh};
			return ;
		}
	}
	return ;
}

static void SetPhantomAdd(t_AiMapUnit &unit, SDL_Point pos)
{
	t_GMU *point = &gameState.battle.ground->map[pos.y][pos.x];
	if (point->additional.type == AdditionalObjects::PHANTOM_KNIGHT)
	{
		PhantomKnight *used = (PhantomKnight*)point->additional.object;
		unit.adds.phantom.isIt = true;
		unit.adds.phantom.turns = used->GetTurns();
		unit.adds.phantom.parent = used->character;
		return ;
	}
	unit.adds.phantom.isIt = false;
	unit.adds.phantom.parent = NULL;
	unit.adds.phantom.turns = 0;
}

static void SetToolBoxAdd(t_AiMapUnit &unit, SDL_Point pos)
{
	t_GMU *point = &gameState.battle.ground->map[pos.y][pos.x];
	if (point->additional.type == AdditionalObjects::TOOLBOX)
	{
		ToolBox *used = (ToolBox*)point->additional.object;
		unit.adds.toolBox.isIt = true;
		unit.adds.toolBox.parent = point->character;
		unit.adds.toolBox.turns = 1;
		return ;
	}
	unit.adds.toolBox.isIt = false;
	unit.adds.toolBox.parent = NULL;
	unit.adds.toolBox.turns = 0;
}

void SetAiMapAdds(t_AiMapUnit &unit, SDL_Point pos)
{
	t_GMU *point = &gameState.battle.ground->map[pos.y][pos.x];
	SetSmokeAdd(unit, pos);
	SetPhantomAdd(unit, pos);
	SetToolBoxAdd(unit, pos);
}

void SetAiDataMapInitial(t_AiMapUnit **map)
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *point = &gameState.battle.ground->map[i][j];
			map[i][j].blocked = point->blocked;
			map[i][j].height = point->height;
			map[i][j].character = SetTheCharacter(point->character);
			map[i][j].obj = SetTheObj(point->obj);
			SetAiMapAdds(map[i][j], {j, i});
			map[i][j].movable = TOOL_MAP_SIGN;
		}
	}
}

void ReturnCharQToHolder(t_AiCharacter **charQ)
{
	int i = 0;
	while (charQ[i] != NULL)
	{
		ReturnAiCharacter(charQ[i]);
		i++;
	}
	free(charQ[i]);
	free(charQ);
}

static void ShiftCharQToLeft(int size, t_AiCharacter **charQ)
{
	t_AiCharacter *first = charQ[0];
	for (int i = 0; i < (size - 1); i++)
		charQ[i] = charQ[i + 1];
	charQ[size - 1] = first;
}

static void OrderCharQ(int size, t_AiCharacter **charQ)
{
	if (size == 0)
		return ;
	while (true)
	{
		if (charQ[0]->character->turn)
			break ;
		ShiftCharQToLeft(size, charQ);
	}
}

t_AiCharacter **GetCharQForAi()
{
	int size = gameState.battle.ground->characters.size();
	t_AiCharacter **characters = (t_AiCharacter**)malloc(sizeof(t_AiCharacter*) * (size + 1));
	int i = 0;
	while (i < gameState.updateObjs.turnOrder->indicators.size())
	{
		characters[i] = SetTheCharacter(gameState.updateObjs.turnOrder->indicators[i].character);
		i++;
	}
	OrderCharQ(i, characters);
	characters[i] = NULL;
	return (characters);
}

static int GetSmokeSize()
{
	int count = 0;
	for (int i = 0; i < gameState.updateObjs.abilities->effectUpdater.effects.size(); i++)
	{
		if (gameState.updateObjs.abilities->effectUpdater.effects[i].ability->type == SMOKE_BOMB)
			count++;
	}
	return (count);
}

static int GetAdditionalsSize()
{
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	int count = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *used = &gameState.battle.ground->map[i][j];
			if (used->additional.type == AdditionalObjects::PHANTOM_KNIGHT || used->additional.type == AdditionalObjects::TOOLBOX)
				count++;
		}
	}
	return (count);
}

t_AiMapItem *GetItemFromHolder()
{
	t_AiMapItem *ret = (t_AiMapItem*)malloc(sizeof(t_AiMapItem));
	bzero(ret, sizeof(t_AiMapItem));
	return (ret);
}

static t_AiCharacter *GetFromCharQ(Character *character, t_AiCharacter **charQ)
{
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->character == character)
			return (charQ[i]);
	}
	return (NULL);
}

static int SetSmokesToItems(t_AiMapItem **items, t_AiCharacter **charQ)
{
	int index = 0;
	for (int i = 0; i < gameState.updateObjs.abilities->effectUpdater.effects.size(); i++)
	{
		t_AbilityEffect *effect = &gameState.updateObjs.abilities->effectUpdater.effects[i];
		if (effect->ability->type != SMOKE_BOMB)
			continue ;
		SmokeEffect *used = (SmokeEffect*)effect->effect;
		int ret = used->getTime();
		Character *thh = used->getCharacter();
		t_AiMapItem *adder = GetItemFromHolder();
		adder->type = SMOKE_BOMB;
		adder->turns = ret;
		adder->parent = GetFromCharQ(thh, charQ);
		adder->position = effect->pos;
		adder->item = NULL;
		adder->own = NULL;
		items[index] = adder;
		index++;
	}
	return (index);
}

t_AiMapItem **GetItemsForAi(t_AiCharacter **charQ)
{
	int size = GetAdditionalsSize() + GetSmokeSize();
	t_AiMapItem **items = (t_AiMapItem**)malloc(sizeof(t_AiMapItem*) * (size + 1));
	int index = SetSmokesToItems(items, charQ);
	int w = gameState.battle.ground->map[0].size();
	int h = gameState.battle.ground->map.size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			t_GMU *used = &gameState.battle.ground->map[i][j];
			if (used->additional.type == AdditionalObjects::PHANTOM_KNIGHT)
			{
				PhantomKnight *phant = (PhantomKnight*)used->additional.object;
				t_AiMapItem *adder = GetItemFromHolder();
				adder->parent = GetFromCharQ(phant->character, charQ);
				adder->turns = phant->GetTurns();
				adder->position = {j, i};
				adder->type = PHANTOM_KNIGHT;
				adder->item = NULL;
				adder->own = SetTheCharacter(phant->GetThis());
				items[index] = adder;
				index++;
			}
			else if (used->additional.type == AdditionalObjects::TOOLBOX)
			{
				ToolBox *tool = (ToolBox*)used->additional.object;
				t_AiMapItem *adder = GetItemFromHolder();
				adder->parent = NULL;
				adder->turns = 0;
				adder->position = {j, i};
				adder->item = tool;
				adder->type = TOOLS;
				adder->own = SetTheCharacter(tool->GetThis());
				index++;
			}
		}
	}
	items[index] = NULL;
	return (items);
}

void ReturnItemsToHolder(t_AiMapItem **items)
{
	int i = 0;
	while (items[i] != NULL)
	{
		free(items[i]);
		i++;
	}
	free(items[i]);
	free(items);
}

t_AiCharacter *GetTheStartingTurnForAi2(t_AiCharacter **charQ)
{
	Character *used = NULL;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		if (gameState.battle.ground->characters[i].character->turn)
		{
			used = gameState.battle.ground->characters[i].character;
			break ;
		}
	}
	for (int i = 0; charQ[i] != NULL; i++)
	{
		if (charQ[i]->character == used)
		{
			if (charQ[i]->character->killed)
				return (NULL);
			return (charQ[i]);
		}
	}
	return (NULL);
}

t_AiMapUnit **GetTheMap()
{
	t_AiMapUnit **map = GetMapFromHolder();
	SetAiDataMapInitial(map);
	return (map);
}
