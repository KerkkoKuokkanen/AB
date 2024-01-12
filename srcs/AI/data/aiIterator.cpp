
#include "../../../hdr/global.h"

void AiIterator::GetPossibleMoves()
{
	GetAiMapMoves(&character, map);
}

void AiIterator::SetDefaultCharacter(SDL_Point pos, t_AiCharacter *character, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character.alive = character->alive;
	map[pos.y][pos.x].character.armor = character->armor;
	map[pos.y][pos.x].character.health = character->health;
	map[pos.y][pos.x].character.fatigue = character->fatigue;
	map[pos.y][pos.x].character.moves = character->moves;
	map[pos.y][pos.x].character.character = character->character;
	map[pos.y][pos.x].character.position = pos;
	std::memcpy(&map[pos.y][pos.x].character.statuses, &character->statuses, sizeof(t_StatusEffects));
}

void AiIterator::SetDefaultNoCharacter(SDL_Point pos, t_AiMapUnit **map)
{
	map[pos.y][pos.x].character.character = NULL;
	map[pos.y][pos.x].character.alive = false;
	map[pos.y][pos.x].character.armor = 0;
	map[pos.y][pos.x].character.health = 0;
	map[pos.y][pos.x].character.fatigue = 0;
	map[pos.y][pos.x].character.moves = 0;
	map[pos.y][pos.x].character.position = {0, 0};
	map[pos.y][pos.x].character.statuses = {};
}

void AiIterator::CalculateMoves(t_AiMapUnit**map, t_AiCharacter character, float startScore, int depth)
{
	AiIterator::depth = depth - 1;
	AiIterator::character = character;
	AiIterator::map = map;
	AiIterator::startScore = startScore;
	action = {startScore, true};
	GetPossibleMoves();
	IterateTheMap();
}

void AiIterator::IterateTheMap()
{
	int h = gameState.battle.ground->map.size();
	int w = gameState.battle.ground->map[0].size();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			CheckForAbility({j, i});
			CheckForMove({j, i});
		}
	}
}

void AiIterator::Destroy()
{
	
}
