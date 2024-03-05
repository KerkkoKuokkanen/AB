
#include "../../../hdr/global.h"
#define TB 1400
#define TBO 700
#define TN 1100
#define TNO 550

static int GetYMinus(int last)
{
	float value = -0.440508f * (float)last + 526.810176f;
	int ret = rounding(value);
	return (ret);
}

static t_Ability *GetCurrAbility(int ability, Character *character)
{
	if (character == NULL)
		return (NULL);
	for (int i = 0; i < character->abilities.size(); i++)
	{
		if (character->abilities[i].type == ability)
			return (&character->abilities[i]);
	}
	return (NULL);
}

static std::string GetAbilityEnergyString(t_Ability *ability)
{
	if (ability == NULL)
		return ("");
	std::string ret = "Critical: ";
	int cost = ability->critChance;
	ret += std::to_string(cost);
	ret += "%";
	return (ret);
}

static std::string GetAbilityDamageString(t_Ability *ability, Character *character)
{
	if (ability == NULL)
		return ("");
	std::string ret = "Damage: ";
	float abilityMulti = (float)ability->damage / 100.0f;
	int min = rounding((float)character->stats.baseDamageLow * abilityMulti);
	int max = rounding((float)character->stats.baseDamageHigh * abilityMulti);
	if (ability->type == HEALTH_TRANSFER)
	{
		t_HealthTransfer *use = (t_HealthTransfer*)ability->stats;
		min = use->amount;
		max = use->amount;
	}
	ret += std::to_string(min);
	ret += "-";
	ret += std::to_string(max);
	return (ret);
}

static std::string AccuracyAddition(t_Ability *ability)
{
	if (ability->type != SMITH_BUFF)
		return ("");
	t_BuffAndDebuff *used = (t_BuffAndDebuff*)ability->stats;
	int chance = used->debuffChance;
	std::string add = ", ";
	add += std::to_string(chance);
	add += "%";
	return (add);
}

static std::string GetAccuracyString(t_Ability *ability)
{
	if (ability == NULL)
		return ("");
	std::string ret = "Accuracy: ";
	int accuracy = ability->baseChance;
	ret += std::to_string(accuracy);
	ret += "%";
	ret += AccuracyAddition(ability);
	return (ret);
}

static std::string GetAdditionToRange(t_Ability *ability)
{
	if (ability->type != TELEPORT && ability->type != HEALTH_TRANSFER)
		return ("");
	std::string ret = ", ";
	int range = 0;
	if (ability->type == TELEPORT)
	{
		t_Teleport *use = (t_Teleport*)ability->stats;
		range = use->secondRange;
	}
	else if (ability->type == HEALTH_TRANSFER)
	{
		t_HealthTransfer *use = (t_HealthTransfer*)ability->stats;
		range = use->secondRange;
	}
	bool dot = (range % 2 != 0) ? true : false;
	int truu = (range == 0) ? 0 : range / 2;
	ret += std::to_string(truu);
	if (!dot)
	{
		ret += ".0";
		return (ret);
	}
	ret += ".5";
	return (ret);
}

static std::string GetRangeString(t_Ability *range, int cSing)
{
	if (range == NULL)
		return ("");
	std::string ret = "Range: ";
	int rage = range->range;
	if (range->type == GENERIC_TOOL_THROW && cSing == LION)
		rage += 1;
	bool dot = (rage % 2 != 0) ? true : false;
	int truu = (rage == 0) ? 0 : rage / 2;
	ret += std::to_string(truu);
	if (!dot)
	{
		ret += ".0";
		ret += GetAdditionToRange(range);
		return (ret);
	}
	ret += ".5";
	ret += GetAdditionToRange(range);
	return (ret);
}

static std::string GetFatiqueCost(t_Ability *ability)
{
	if (ability == NULL)
		return ("");
	std::string ret = "Fatique: ";
	int fat = ability->fatigue;
	ret += std::to_string(fat);
	return (ret);
}

static std::string GetEnergyShit(t_Ability *ability)
{
	if (ability == NULL)
		return ("");
	std::string ret = "Energy: ";
	int cost = ability->cost;
	ret += std::to_string(cost);
	return (ret);
}

void UiTextUpdater::CreateBubble()
{
	Character *character = gameState.updateObjs.UI->GetActiveCharacter();
	t_Ability *curr = GetCurrAbility(currentAbility, character);
	std::string cost = GetAbilityEnergyString(curr);
	std::string damage = GetAbilityDamageString(curr, character);
	std::string accuracy = GetAccuracyString(curr);
	std::string range = GetRangeString(curr, character->cSing);
	std::string fatique = GetFatiqueCost(curr);
	std::string energy = GetEnergyShit(curr);
	switch (currentAbility)
	{
		case DAGGER_THROW:
		{
			Snippet *add1 = new Snippet("Dagger Throw", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SMOKE_BOMB:
		{
			Snippet *add1 = new Snippet("Smoke Bomb", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case DAGGER_SLASH:
		{
			Snippet *add1 = new Snippet("Dagger Slash", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case FLAME_PORT:
		{
			Snippet *add1 = new Snippet("Flame Teleport", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case FLAME_SLASH:
		{
			Snippet *add1 = new Snippet("Flame Slash", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case FLAME_BLAST:
		{
			Snippet *add1 = new Snippet("Flame Blast", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case INCINERATE:
		{
			Snippet *add1 = new Snippet("Incinerate", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case LION_SMACK:
		{
			Snippet *add1 = new Snippet("Lion Smack", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case PHANTOM_KNIGHT:
		{
			Snippet *add1 = new Snippet("Phantom Knight", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case ROTATE:
		{
			Snippet *add1 = new Snippet("Rotate", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case HAMMER_SMACK:
		{
			Snippet *add1 = new Snippet("Hammer Hit", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case GO_FOR_THE_HEAD:
		{
			Snippet *add1 = new Snippet("Go For The Head", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case THROW_TOOLBOX:
		{
			Snippet *add1 = new Snippet("Tool Throw", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SUPPLY_ALLY:
		{
			Snippet *add1 = new Snippet("Direct Supply", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SUPPLY:
		{
			Snippet *add1 = new Snippet("Supply", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case GENERIC_TOOL_THROW:
		{
			Snippet *add1 = new Snippet("Tool Throw", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case PICK_UP_TOOLS:
		{
			Snippet *add1 = new Snippet("Pick Tools", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SMITH_BUFF:
		{
			Snippet *add1 = new Snippet("Inspire", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case LIGHTNING_BOLT:
		{
			Snippet *add1 = new Snippet("Lightning Bolt", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case ROCK_FALL:
		{
			Snippet *add1 = new Snippet("Meteor Fall", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case HOST_EYES:
		{
			Snippet *add1 = new Snippet("Host Eyes", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case AXE_SLASH:
		{
			Snippet *add1 = new Snippet("Axe Slash", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case AXE_JUMP:
		{
			Snippet *add1 = new Snippet("Axe Lunge", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case TOXIC_BLADE:
		{
			Snippet *add1 = new Snippet("Toxic Blade", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case RAIDER_BLOCK:
		{
			Snippet *add1 = new Snippet("Block", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case NAIL_BOMB:
		{
			Snippet *add1 = new Snippet("Nail Bomb", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case ACID_BOMB:
		{
			Snippet *add1 = new Snippet("Acid Flask", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SLOW_BOMB:
		{
			Snippet *add1 = new Snippet("Slow Bomb", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case FLAIL_STRIKE:
		{
			Snippet *add1 = new Snippet("Flail Strike", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case SHILED_BASH:
		{
			Snippet *add1 = new Snippet("Shield Bash", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case CONTROL_ZONE:
		{
			Snippet *add1 = new Snippet("Control Zone", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case ACID_RAIN:
		{
			Snippet *add1 = new Snippet("Acid Rain", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case TELEPORT:
		{
			Snippet *add1 = new Snippet("Teleport", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(0, 115, 255);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
		case HEALTH_TRANSFER:
		{
			Snippet *add1 = new Snippet("Health Transfer", FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TB, TBO, TEXT_BUBBLE_LAYER, true);
			add1->SetColor(247, 66, 0);
			bubble->AddSnippetToBubble(add1, {500, 250});
			break ;
		}
	}
	Snippet *add2 = new Snippet(cost.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add3 = new Snippet(damage.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add4 = new Snippet(accuracy.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add5 = new Snippet(range.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add6 = new Snippet(fatique.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	Snippet *add7 = new Snippet(energy.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSnippetToBubble(add3, {500, 3000});
	bubble->AddSnippetToBubble(add2, {500, 7000});
	bubble->AddSnippetToBubble(add4, {500, 5000});
	bubble->AddSnippetToBubble(add5, {500, 9000});
	bubble->AddSnippetToBubble(add7, {500, 11000});
	bubble->AddSnippetToBubble(add6, {500, 13000});
	bubble->SetUpOutline(500, GetYMinus(13000));
}
