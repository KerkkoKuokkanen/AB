
#include "../../../hdr/global.h"

static int GetToxicBladeIndex(Character *character)
{
	int min = character->statuses.toxicBlade[0].turns;
	int index = 0;
	for (int i = 0; i < character->statuses.toxicBlade.size(); i++)
	{
		if (min > character->statuses.toxicBlade[i].turns)
		{
			index = i;
			min = character->statuses.toxicBlade[i].turns;
		}
	}
	return (index);
}

static void CheckForApplyPoison(Character *character, Character *target, t_Ability *ability)
{
	if (character->statuses.toxicBlade.size() == 0)
		return ;
	int index = GetToxicBladeIndex(character);
	int stacks = character->statuses.toxicBlade[index].stacks;
	character->statuses.toxicBlade.erase(character->statuses.toxicBlade.begin() + index);
	if (!StatusApply(ability, character, target, true))
	{
		CreateTextSnippet(character, target, "MISS", 900, Color(28, 138, 0));
		return ;
	}
	gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(28, 138, 0), 0);
	std::string used;
	used += std::to_string(stacks);
	used += " poison";
	const char *ret = used.c_str();
	CreateTextSnippet(character, target, ret, 1000, Color(28, 138, 0));
	target->statuses.poison.push_back({stacks, 3});
}

void Abilities::UpdateRaiderAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case AXE_SLASH:
		{
			AxeSlash *used = (AxeSlash*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
				{
					CreateDamage();
					CheckForApplyPoison(character, target, ability);
				}
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
		case AXE_JUMP:
		{
			AxeJumpAnim *used = (AxeJumpAnim*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
				{
					std::vector<SDL_Point> point = {target->position};
					damager.AddDamage(ability, character, point);
					CheckForApplyPoison(character, target, ability);
				}
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
		case TOXIC_BLADE:
		{
			ToxinBuff *used = (ToxinBuff*)anim.animation;
			used->Update();
			if (used->addStatus)
			{
				t_ToxicBlade *add = (t_ToxicBlade*)ability->stats;
				for (int i = 0; i < add->hits; i++)
					character->statuses.toxicBlade.push_back({add->stacks, add->turns});
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case RAIDER_BLOCK:
		{
			RaiderBlock *used = (RaiderBlock*)anim.animation;
			used->Update();
			if (used->createBuff)
			{
				t_RaiderBlock *used = (t_RaiderBlock*)ability->stats;
				AddBuffToCharacter(character, {BuffTypes::PROTECTION, 1, used->precentage, false, BuffDebuffId::RAIDER_PROT});
				gameState.updateObjs.turnOrder->ActivateTurnChange(true);
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
