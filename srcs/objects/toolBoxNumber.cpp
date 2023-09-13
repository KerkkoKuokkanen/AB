
#include "../../hdr/global.h"

static bool CheckIfCan(SDL_Point pos)
{
	if (gameState.battle.ground->map[pos.y][pos.x].marked == false)
		return (false);
	if (gameState.updateObjs.hover.overMenu)
		return (false);
	if (gameState.updateObjs.hover.overCharacterUI)
		return (false);
	if (gameState.updateObjs.hover.overTurnOrder)
		return (false);
	return (true);
}

void ToolBox::CreateSymbol()
{
	SDL_Rect dest = gameState.battle.ground->getTileDest(targPos);
	SDL_Rect used = {dest.x + 2600, dest.y - 1100, 1300, 1300};
	symbol = new Sprite(gameState.textures.supplyToolSymbol, used, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(symbol, INFO_LAYER);
}

void ToolBox::CreateNumber()
{
	SDL_Rect dest = gameState.battle.ground->getTileDest(targPos);
	std::string num = std::to_string(supplyAmount);
	int len = num.length();
	int x = dest.x + 2230;
	if (len > 1)
		x -= 500;
	const char *used = num.c_str();
	number = new Snippet(used, FontTypes::GOOGLE_TEXT, true, {x, dest.y - 1000}, 1000, 500, TEXT_LAYER, false);
	number->SetOutlineAmount(40);
	number->SetColor(210, 210, 210);
}

void ToolBox::ManageDisplayNumbers()
{
	if (supplyAmount < 0)
		supplyAmount = 0;
	if (symbol == NULL)
		CreateSymbol();
	if (number == NULL)
		CreateNumber();
	if (number != NULL)
	{
		const char *text = number->GetText();
		int num = atoi(text);
		if (num != supplyAmount)
		{
			delete number;
			CreateNumber();
		}
	}
}

void ToolBox::DisplayToolBoxNumber()
{
	if (!CheckIfCan(targPos) || arch != NULL)
	{
		if (number != NULL)
			delete number;
		if (symbol != NULL)
			delete symbol;
		number = NULL;
		symbol = NULL;
		return ;
	}
	ManageDisplayNumbers();
}
