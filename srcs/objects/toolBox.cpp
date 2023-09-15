
#include "../../hdr/global.h"

ToolBox::ToolBox(Character *character)
{
	ToolBox::character = character;
	SDL_Rect dest = character->sprite->dest;
	sprite = new Sprite(gameState.textures.chars.handTools[1], dest, NULL, NULL, 0, FLIP_NONE);
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
}

void ToolBox::UpdateToolBoxInHand()
{
	if (!inHand)
		return ;
	SDL_Rect dest = character->sprite->dest;
	float angle = character->sprite->getAngle();
	SDL_Texture *text = character->sprite->getTexture();
	if (text == gameState.textures.chars.smithIdle[0])
		sprite->setTexture(gameState.textures.chars.handTools[0]);
	else if (text == gameState.textures.chars.smithIdle[1])
		sprite->setTexture(gameState.textures.chars.handTools[1]);
	else if (text == gameState.textures.attacks.hammerSmack[0])
		sprite->setTexture(gameState.textures.chars.handTools[2]);
	else if (text == gameState.textures.attacks.smithBuff)
		sprite->setTexture(gameState.textures.chars.handTools[3]);
	sprite->setAngle(angle);
	sprite->dest = dest;
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	sprite->AlphaMod(character->sprite->getAlpha());
}

bool ToolBox::ToolExists(Character *target, int toolSign)
{
	for (int i = 0; i < target->abilities.size(); i++)
	{
		if (target->abilities[i].type == toolSign)
			return (true);
	}
	return (false);
}

void ToolBox::RemoveInHandAbilities()
{
	for (int i = 0; i < character->abilities.size(); i++)
	{
		if (character->abilities[i].type == THROW_TOOLBOX)
		{
			if (character->abilities[i].stats != NULL)
				free(character->abilities[i].stats);
			character->abilities.erase(character->abilities.begin() + i);
		}
	}
	for (int i = 0; i < character->abilities.size(); i++)
	{
		if (character->abilities[i].type == SUPPLY_ALLY)
		{
			if (character->abilities[i].stats != NULL)
				free(character->abilities[i].stats);
			character->abilities.erase(character->abilities.begin() + i);
		}
	}
}

void ToolBox::InHandAbilities()
{
	if (!ToolExists(character, THROW_TOOLBOX))
	{
		character->abilities.push_back({THROW_TOOLBOX, 0, 8, 200, StatStructs::THROWABLE, (-1), NULL});
		int index = character->abilities.size() - 1;
		character->abilities[index].stats = (void*)malloc(sizeof(t_Throwable));
		t_Throwable *used = (t_Throwable*)character->abilities[index].stats;
		used->range = 9;
	}
	if (!ToolExists(character, SUPPLY_ALLY))
	{
		character->abilities.push_back({SUPPLY_ALLY, 0, 12, 200, StatStructs::SUPPLY, (-1), NULL});
		int index = character->abilities.size() - 1;
		character->abilities[index].stats = (void*)malloc(sizeof(t_Supply));
		t_Supply *used = (t_Supply*)character->abilities[index].stats;
		used->amount = 30;
	}
}

void ToolBox::ManageSmithAbilities()
{
	if (inHand)
		InHandAbilities();
	else
		RemoveInHandAbilities();
}

void ToolBox::UpdateThrowArch()
{
	if (arch == NULL)
		return ;
	arch->Update();
	if (arch->done)
	{
		delete arch;
		sprite->orderLayer = targPos.y;
		sprite->setDepth(gameState.battle.ground->map[targPos.y][targPos.x].height * BATTLE_DEPTH_UNIT + 8);
		arch = NULL;
		CreateDust({sprite->dest.x + 1000, sprite->dest.y + 5200}, Vector(-1.0f, -1.0f));
		CreateDust({sprite->dest.x + 1400, sprite->dest.y + 5200}, Vector(1.0f, -1.0f));
		SetScreenShake(250, 6);
		PlaySound(gameState.audio.boxLand, Channels::BOX_LANDING, 0);
		PlaySound(gameState.audio.boxLand2, Channels::BOX_LANDING2, 0);
	}
}

void ToolBox::Update()
{
	UpdateToolBoxInHand();
	ManageToolBoxNotInHand();
	ManageSmithAbilities();
	ManageOnGroundAbilities();
}

void ToolBox::RemoveFromMapPosition()
{
	if (gameState.battle.ground->map[targPos.y][targPos.x].additional.object != NULL)
	{
		if (gameState.battle.ground->map[targPos.y][targPos.x].additional.type == AdditionalObjects::TOOLBOX)
		{
			ToolBox *ret = (ToolBox*)gameState.battle.ground->map[targPos.y][targPos.x].additional.object;
			if (ret == this)
			{
				gameState.battle.ground->map[targPos.y][targPos.x].blocked = false;
				gameState.battle.ground->map[targPos.y][targPos.x].additional = {-1, NULL};
			}
		}
	}
}

void ToolBox::SetToolBoxBack()
{
	inHand = true;
	RemoveFromMapPosition();
	for (int i = 0; i < targetCharacters.size(); i++)
		RemoveOnGroundAbilities(targetCharacters[i].target);
	targetCharacters.clear();
	if (number != NULL)
		delete number;
	if (symbol != NULL)
		delete symbol;
	number = NULL;
	symbol = NULL;
	targetCharacters.clear();
}

void ToolBox::SupplyTarget(Character *target)
{
	supplyAmount -= 1;
	new SupplyEffect(target);
	float max = (float)target->stats.maxFatigue;
	float amount = max * 0.35f;
	int reduce = rounding(amount);
	target->stats.fatigue -= reduce;
	if (target->stats.fatigue < 0)
		target->stats.fatigue = 0;
	if (supplyAmount == 0)
	{
		for (int i = 0; i < targetCharacters.size(); i++)
		{
			Character *targ = targetCharacters[i].target;
			for (int j = 0; j < targ->abilities.size(); j++)
			{
				if (targ->abilities[j].type == SUPPLY)
				{
					if (targ->abilities[j].stats != NULL)
						free(targ->abilities[j].stats);
					targ->abilities.erase(targ->abilities.begin() + j);
				}
			}
		}
	}
}

void ToolBox::SetToolThrow(SDL_Point target)
{
	if (!inHand)
		RemoveFromMapPosition();
	else
		supplyAmount = 4;	//Upgrade supply amount here!
	inHand = false;
	SDL_Rect dest = gameState.battle.ground->getTileDest(target);
	if (arch != NULL)
		delete arch;
	sprite->ClearAlphaMod();
	arch = new ThrowArch(sprite, {sprite->dest.x, sprite->dest.y}, {dest.x + 1300, dest.y - 3600}, 12.0f, 450.0f);
	targPos = target;
	gameState.battle.ground->map[target.y][target.x].blocked = true;
	gameState.battle.ground->map[target.y][target.x].additional = {AdditionalObjects::TOOLBOX, this};
	PlaySound(gameState.audio.toolThrow, Channels::TOOL_THROW, 0);
}
