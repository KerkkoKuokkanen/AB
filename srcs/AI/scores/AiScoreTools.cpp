
#include "../../../hdr/global.h"

static Character *GetNextInTheList(Character *current)
{
	int index = (-1);
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *charac = gameState.updateObjs.turnOrder->indicators[i].character;
		if (charac == current)
		{
			index = i;
			break ;
		}
	}
	if (index == (-1))
		return (current);
	if (index == gameState.updateObjs.turnOrder->indicators.size() - 1)
		return (gameState.updateObjs.turnOrder->indicators[0].character);
	return (gameState.updateObjs.turnOrder->indicators[index + 1].character);
}

static t_AiCharacter *FindInTheVector(std::vector<t_AiCharacter*> &charQ, Character *find)
{
	for (int i = 0; i < charQ.size(); i++)
	{
		if (charQ[i]->character == find)
			return (charQ[i]);
	}
	printf("error is here in the CrazyLoop with function FindInTheVector\n");
	return (NULL);
}

void OrderTheCharQ(std::vector<t_AiCharacter*> &charQ)
{
	Character *turn = NULL;
	int index = 0;
	for (int i = 0; i < gameState.updateObjs.turnOrder->indicators.size(); i++)
	{
		Character *charac = gameState.updateObjs.turnOrder->indicators[i].character;
		if (charac->turn)
		{
			index = i;
			turn = charac;
			break ;
		}
	}
	if (turn == NULL)
		return ;
	std::vector<t_AiCharacter*> newOrder = {};
	newOrder.push_back(FindInTheVector(charQ, turn));
	while (true)
	{
		Character *next = GetNextInTheList(newOrder[newOrder.size() - 1]->character);
		if (next == turn)
			break ;
		newOrder.push_back(FindInTheVector(charQ, next));
	}
	charQ.clear();
	charQ = newOrder;
}