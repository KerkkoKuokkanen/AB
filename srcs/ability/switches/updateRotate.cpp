
#include "../../../hdr/global.h"

static bool ValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static bool ThisIsThePosition(SDL_Point pos)
{
	int x = pos.x;
	int y = pos.y;
	if (ValidPosition(pos))
	{
		if (gameState.battle.ground->map[y][x].additional.object != NULL)
		{
			if (gameState.battle.ground->map[y][x].additional.type == AdditionalObjects::TOOLBOX)
			{
				ToolBox *box = (ToolBox*)gameState.battle.ground->map[y][x].additional.object;
				if (box->GetSupplyAmount() > 0)
					return (true);
			}
		}
	}
	return (false);
}

void Abilities::IncudeToolPoints()
{
	SDL_Point pos = character->position;
	SDL_Point test = {getXToLeft(pos), pos.y - 1};
	if (ThisIsThePosition(test))
		tileSelector->IncludePoint(test);
	test = {test.x, pos.y + 1};
	if (ThisIsThePosition(test))
		tileSelector->IncludePoint(test);
	test = {getXToRight(pos), pos.y - 1};
	if (ThisIsThePosition(test))
		tileSelector->IncludePoint(test);
	test = {test.x, pos.y + 1};
	if (ThisIsThePosition(test))
		tileSelector->IncludePoint(test);
}

void Abilities::UpdateRotate(int index)
{
	Rotate *rotate = (Rotate*)animations[index].animation;
	rotate->Update();
	if (rotate->done)
	{
		delete rotate;
		animations.erase(animations.begin() + index);
	}
}

bool Abilities::CheckGenericAnimations(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case ROTATE:
			UpdateRotate(index);
			return (true);
		case SUPPLY:
		{
			Supply *used = (Supply*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			return (true);
		}
		case GENERIC_TOOL_THROW:
		{
			GenericToolThrow *used = (GenericToolThrow*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			return (true);
		}
	}
	return (false);
}
