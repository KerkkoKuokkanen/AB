
#include "../../hdr/global.h"

bool ToolBox::AcceptAbility(int type)
{
	if (type == HEALTH_TRANSFER)
		return (false);
	return (true);
}

ToolBox::ToolBox(Character *character) : Character(TOOLS)
{
	ToolBox::character = character;
	SDL_Rect dest = character->sprite->dest;
	sprite = new Sprite(gameState.textures.chars.handTools[1], dest, NULL, NULL, 0, FLIP_NONE);
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	stand = new Sprite(gameState.textures.stands.toolsStand, dest, NULL, NULL, 0, FLIP_NONE);
	stand->orderLayer = sprite->orderLayer;
	stand->z = sprite->z - 0.1f;
	stand->Deactivate();
	gameState.render->AddSprite(stand, BATTLEGROUND_LAYER);
	Character::sprite = sprite;
	Character::stand = stand;
	Character::stats.maxArmor = 20;
	Character::stats.armor = 20;
	Character::stats.maxHealth = 60;
	Character::stats.health = 60;
	Character::ally = character->ally;
}

void ToolBox::UpdateToolBoxInHand()
{
	if (!inHand)
		return ;
	if (character->killed)
	{
		done = true;
		return ;
	}
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
	if (gameState.updateObjs.abilities->active || character == NULL)
		return ;
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
	character = NULL;
}

void ToolBox::InHandAbilities()
{
	if (gameState.updateObjs.abilities->active)
		return ;
	if (!ToolExists(character, THROW_TOOLBOX))
	{
		character->abilities.push_back({THROW_TOOLBOX, 2, 15, 9, 200, StatStructs::THROWABLE, (-1), 0, 0, true, false, NULL});
		int index = character->abilities.size() - 1;
		character->abilities[index].stats = (void*)malloc(sizeof(t_Throwable));
		t_Throwable *used = (t_Throwable*)character->abilities[index].stats;
		used->range = 9;
	}
	if (!ToolExists(character, SUPPLY_ALLY))
	{
		character->abilities.push_back({SUPPLY_ALLY, 3, 25, 2, 200, StatStructs::SUPPLY, (-1), 0, 0, true, false, NULL});
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
	stand->Deactivate();
	if (arch == NULL)
	{
		if (!inHand)
		{
			stand->Activate();
			stand->z = sprite->z - 0.1f;
			stand->orderLayer = sprite->orderLayer;
			stand->dest = sprite->dest;
		}
		return ;
	}
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
	if (done)
		return ;
	UpdateToolBoxInHand();
	ManageToolBoxNotInHand();
	ManageSmithAbilities();
	ManageOnGroundAbilities();
	stand->dest = sprite->dest;
	targPos = Character::position;
	if (Character::stats.health <= 0 && delayerStart == false)
	{
		gameState.updateObjs.killer->AddCharacterToKill(this);
		delayerStart = true;
	}
	if (done || delayerStart)
	{
		for (int i = 0; i < targetCharacters.size(); i++)
			RemoveOnGroundAbilities(targetCharacters[i].target);
	}
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
				gameState.battle.ground->map[targPos.y][targPos.x].character = NULL;
			}
		}
	}
}

void ToolBox::SetToolBoxBack(Character *getter)
{
	inHand = true;
	RemoveFromMapPosition();
	stand->Deactivate();
	for (int i = 0; i < targetCharacters.size(); i++)
		RemoveOnGroundAbilities(targetCharacters[i].target);
	targetCharacters.clear();
	if (number != NULL)
		delete number;
	if (symbol != NULL)
		delete symbol;
	number = NULL;
	symbol = NULL;
	character = getter;
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
	arch = new ThrowArch(sprite, {sprite->dest.x, sprite->dest.y}, {dest.x + 1300, dest.y - 4000}, 10000.0f, 450.0f);
	targPos = target;
	gameState.battle.ground->map[target.y][target.x].blocked = true;
	gameState.battle.ground->map[target.y][target.x].additional = {AdditionalObjects::TOOLBOX, this};
	gameState.battle.ground->map[target.y][target.x].character = this;
	Character::position = target;
	PlaySound(gameState.audio.toolThrow, Channels::TOOL_THROW, 0);
}

void ToolBox::Destroy()
{
	if (sprite != NULL)
		delete sprite;
	if (stand != NULL)
		delete stand;
	if (symbol != NULL)
		delete symbol;
	if (number != NULL)
		delete number;
	if (arch != NULL)
		delete arch;
}
