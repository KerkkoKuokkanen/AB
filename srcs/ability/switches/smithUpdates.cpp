
#include "../../../hdr/global.h"

static bool ValidPosition(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static bool ThisIsThePosition(Character *character, SDL_Point pos)
{
	int x = pos.x;
	int y = pos.y;
	if (ValidPosition(pos))
	{
		if (gameState.battle.ground->map[y][x].additional.object != NULL)
		{
			if (gameState.battle.ground->map[y][x].additional.type == AdditionalObjects::TOOLBOX)
				return (true);
		}
	}
	return (false);
}

static void CreateSmithBuffDebuff(Character *target, t_Ability *ability)
{
	t_BuffAndDebuff *used = (t_BuffAndDebuff*)ability->stats;
	if (target->ally)
	{
		AddBuffToCharacter(target, {BuffTypes::ACCURACY, used->turns, used->amount, true, BuffDebuffId::NO_ID});
		return ;
	}
	AddDeBuffToCharacter(target, {BuffTypes::ACCURACY, used->turns, used->amount, true, BuffDebuffId::NO_ID});
}

SDL_Point Abilities::FindToolBox(TileSelector *selec)
{
	SDL_Point pos = character->position;
	int x = getXToLeft(pos);
	int y = pos.y - 1;
	if (ThisIsThePosition(character, {x, y}))
	{
		SDL_Point ret = {x, y};
		selec->IncludePoint(ret);
	}
	y = pos.y + 1;
	if (ThisIsThePosition(character, {x, y}))
	{
		SDL_Point ret = {x, y};
		selec->IncludePoint(ret);
	}
	x = getXToRight(pos);
	y = pos.y - 1;
	if (ThisIsThePosition(character, {x, y}))
	{
		SDL_Point ret = {x, y};
		selec->IncludePoint(ret);
	}
	y = pos.y + 1;
	if (ThisIsThePosition(character, {x, y}))
	{
		SDL_Point ret = {x, y};
		selec->IncludePoint(ret);
	}
	SDL_Point ret = {0, 0};
	return (ret);
}

void Abilities::UpdateSmithAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case HAMMER_SMACK:
		{
			HammerSmack *used = (HammerSmack*)anim.animation;
			used->Update();
			if (used->damage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case THROW_TOOLBOX:
		{
			ToolThrowAnim *used = (ToolThrowAnim*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SUPPLY_ALLY:
		{
			SupplyAlly *used = (SupplyAlly*)anim.animation;
			used->Update();
			if (used->removeFat)
			{
				t_Supply *use = (t_Supply*)ability->stats;
				int amount = use->amount;
				Character *target = used->target;
				int maxFat = target->stats.maxFatigue;
				float multi = (float)amount / 100.0f;
				int reduce = rounding((float)maxFat * multi);
				target->stats.fatigue -= reduce;
				if (target->stats.fatigue < 0)
					target->stats.fatigue = 0;
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case PICK_UP_TOOLS:
		{
			PickUpTools *used = (PickUpTools*)anim.animation;
			used->Update();
			if (used->done)
			{
				ToolBox *ret = used->GetToolBoxPointer();
				ret->SetToolBoxBack(character);
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SMITH_BUFF:
		{
			SmithBuff *used = (SmithBuff*)anim.animation;
			used->Update();
			if (used->createBuff)
				CreateSmithBuffDebuff(target, ability);
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case GO_FOR_THE_HEAD:
		{
			GoForTheHead *used = (GoForTheHead*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
