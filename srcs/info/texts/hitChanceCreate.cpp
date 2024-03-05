
#include "../../../hdr/global.h"
#define TN 1600
#define TNO 800

static int GetYMinus(int last)
{
	float value = -0.440508f * (float)last + 526.810176f;
	int ret = rounding(value);
	return (ret);
}

void HitChanceBubble::CreateBubble()
{
	bubble = new TextBubble({0, 0});
	bubble->SetMouseFollow({0, 0});
	bubble->SetFollowCorner(2);
	Character *active = gameState.updateObjs.UI->GetActiveCharacter();
	t_Ability *ability = gameState.updateObjs.abilities->ability;
	int chance = GetChance(active, currHover, ability);
	Sprite *add1 = new Sprite(gameState.textures.hitSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
	add1->ColorMod(175, 175, 175);
	std::string add2 = " ";
	add2 += std::to_string(chance);
	add2 += "%";
	Snippet *add22 = new Snippet(add2.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
	bubble->AddSpriteToBubble(add1, {500, 750});
	bubble->AddSnippetToBubble(add22, {2700, 1150});
	switch (ability->type)
	{
		case DAGGER_THROW:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.bleedSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case DAGGER_SLASH:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.bleedSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case FLAME_SLASH:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.statuses.burns[2], {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case FLAME_BLAST:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.statuses.burns[2], {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case INCINERATE:
		{
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case LION_SMACK:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.questionMark, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case HAMMER_SMACK:
		{
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case GO_FOR_THE_HEAD:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.questionMark, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case SMITH_BUFF:
		{
			delete bubble;
			bubble = new TextBubble({0, 0});
			bubble->SetMouseFollow({0, 0});
			bubble->SetFollowCorner(2);
			Sprite *adder1 = new Sprite(gameState.textures.buffSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_VERTICAL, true);
			adder1->ColorMod(255, 60, 22);
			int bleed = GetStatusChance(ability, active, currHover);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(adder1, {500, 750});
			bubble->AddSnippetToBubble(add4, {2700, 1150});
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case LIGHTNING_BOLT:
		{
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case ROCK_FALL:
		{
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case HOST_EYES:
		{
			delete bubble;
			bubble = new TextBubble({0, 0});
			bubble->SetMouseFollow({0, 0});
			bubble->SetFollowCorner(2);
			Sprite *adder1 = new Sprite(gameState.textures.hostSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			int bleed = GetStatusChance(ability, active, currHover);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(adder1, {500, 750});
			bubble->AddSnippetToBubble(add4, {2700, 1150});
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case AXE_SLASH:
		{
			if (active->statuses.toxicBlade.size() > 0)
			{
				int bleed = GetStatusChance(ability, active, currHover);
				Sprite *add3 = new Sprite(gameState.textures.poisonSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
				std::string blee = " ";
				blee += std::to_string(bleed);
				blee += "%";
				Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
				bubble->AddSpriteToBubble(add3, {500, 4750});
				bubble->AddSnippetToBubble(add4, {2700, 5150});
				bubble->SetUpOutline(500, GetYMinus(4750));
			}
			else
				bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case AXE_JUMP:
		{
			if (active->statuses.toxicBlade.size() > 0)
			{
				int bleed = GetStatusChance(ability, active, currHover);
				Sprite *add3 = new Sprite(gameState.textures.poisonSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
				std::string blee = " ";
				blee += std::to_string(bleed);
				blee += "%";
				Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
				bubble->AddSpriteToBubble(add3, {500, 4750});
				bubble->AddSnippetToBubble(add4, {2700, 5150});
				bubble->SetUpOutline(500, GetYMinus(4750));
			}
			else
				bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case NAIL_BOMB:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.bleedSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case ACID_BOMB:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.poisonSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case SLOW_BOMB:
		{
			delete bubble;
			bubble = new TextBubble({0, 0});
			bubble->SetMouseFollow({0, 0});
			bubble->SetFollowCorner(2);
			Sprite *adder1 = new Sprite(gameState.textures.slowSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			int bleed = GetStatusChance(ability, active, currHover);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(adder1, {500, 750});
			bubble->AddSnippetToBubble(add4, {2700, 1150});
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case FLAIL_STRIKE:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.bleedSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case SHILED_BASH:
		{
			int bleed = GetStatusChance(ability, active, currHover);
			Sprite *add3 = new Sprite(gameState.textures.questionMark, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(add3, {500, 4750});
			bubble->AddSnippetToBubble(add4, {2700, 5150});
			bubble->SetUpOutline(500, GetYMinus(4750));
			break ;
		}
		case ACID_RAIN:
		{
			delete bubble;
			bubble = new TextBubble({0, 0});
			bubble->SetMouseFollow({0, 0});
			bubble->SetFollowCorner(2);
			Sprite *adder1 = new Sprite(gameState.textures.poisonSymbol, {0, 0, 2000, 2000}, NULL, NULL, 0, FLIP_NONE, true);
			int bleed = GetStatusChance(ability, active, currHover);
			std::string blee = " ";
			blee += std::to_string(bleed);
			blee += "%";
			Snippet *add4 = new Snippet(blee.c_str(), FontTypes::GOOGLE_TEXT_SMALL, true, {0, 0}, TN, TNO, TEXT_BUBBLE_LAYER, true);
			bubble->AddSpriteToBubble(adder1, {500, 750});
			bubble->AddSnippetToBubble(add4, {2700, 1150});
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
		case TELEPORT:
		{
			bubble->SetUpOutline(500, GetYMinus(1150));
			break ;
		}
	}
	bubble->DisableOutline();
}

