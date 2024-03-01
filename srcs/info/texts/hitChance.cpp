
#include "../../../hdr/global.h"
#define COUNT_TIME 5
#define ALPHA_TIME 5

static bool InAcceptedAbilities(int ability)
{
	static int acc[] = {SMOKE_BOMB, FLAME_PORT, PHANTOM_KNIGHT, ROTATE,
						THROW_TOOLBOX, SUPPLY_ALLY, SUPPLY, GENERIC_TOOL_THROW,
						PICK_UP_TOOLS, TOXIC_BLADE, RAIDER_BLOCK, CONTROL_ZONE,
						SMITH_BUFF, HEALTH_TRANSFER};
	for (int i = 0; i < 14; i++)
	{
		if (ability == acc[i])
			return (false);
	}
	return (true);
}

static bool NothingToBeDone()
{
	if (gameState.updateObjs.abilities->active == false)
		return (true);
	if (gameState.updateObjs.abilities->inMotion == true)
		return (true);
	if (gameState.updateObjs.abilities->ability == NULL)
		return (true);
	if (gameState.updateObjs.UI->GetActiveCharacter() == NULL)
		return (true);
	if (!InAcceptedAbilities(gameState.updateObjs.abilities->ability->type))
		return (true);
	return (false);
}

void HitChanceBubble::Deleting()
{
	if (bubble != NULL)
		delete bubble;
	bubble = NULL;
	counter = 0;
	currHover = NULL;
}

void HitChanceBubble::Update(Character *hovered)
{
	if (NothingToBeDone() || hovered == NULL || hovered->ally == true)
	{
		Deleting();
		return ;
	}
	int current = gameState.updateObjs.abilities->ability->type;
	if (currAbility != current || hovered != currHover)
	{
		Deleting();
		counter = 0;
		currAbility = current;
		currHover = hovered;
		return ;
	}
	counter = (counter > 30) ? counter : counter + 1;
	if (counter == COUNT_TIME)
		CreateBubble();
	if (bubble != NULL)
	{
		bubble->Update();
		int count = counter - COUNT_TIME;
		float unit = 255.0f / ALPHA_TIME;
		int alpha = rounding(unit * (float)count);
		if (alpha > 255)
		{
			bubble->ClearAlphaMod();
			return ;
		}
		bubble->SetAlphaMod(alpha);
	}
}
