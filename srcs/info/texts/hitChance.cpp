
#include "../../../hdr/global.h"
#define COUNT_TIME 1
#define ALPHA_TIME 10

static bool InAcceptedAbilities(int ability)
{
	static int acc[] = {SMOKE_BOMB, FLAME_PORT, PHANTOM_KNIGHT, ROTATE,
						THROW_TOOLBOX, SUPPLY_ALLY, SUPPLY, GENERIC_TOOL_THROW,
						PICK_UP_TOOLS, TOXIC_BLADE, RAIDER_BLOCK, CONTROL_ZONE,
						HEALTH_TRANSFER};
	for (int i = 0; i < 13; i++)
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
		gameState.updateObjs.info->InfoBarDeactivate(false);
		Deleting();
		return ;
	}
	int current = gameState.updateObjs.abilities->ability->type;
	if (currAbility != current || hovered != currHover)
	{
		gameState.updateObjs.info->InfoBarDeactivate(false);
		Deleting();
		counter = 0;
		currAbility = current;
		currHover = hovered;
		return ;
	}
	counter = (counter > 30) ? counter : counter + 1;
	if (counter == COUNT_TIME || (bubble != NULL && gameState.keys.click == RELEASE_CLICK))
	{
		if (bubble != NULL)
			delete bubble;
		CreateBubble();
	}
	if (bubble != NULL)
	{
		gameState.updateObjs.info->InfoBarDeactivate(true);
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
