
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
	sprite->setAngle(angle);
	sprite->dest = dest;
	sprite->orderLayer = character->sprite->orderLayer;
	sprite->z = character->sprite->z + 0.05f;
	sprite->AlphaMod(character->sprite->getAlpha());
}

bool ToolBox::ToolExists(int toolSign)
{
	for (int i = 0; i < character->abilities.size(); i++)
	{
		if (character->abilities[i].type == toolSign)
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
	if (!ToolExists(THROW_TOOLBOX))
	{
		character->abilities.push_back({THROW_TOOLBOX, 0, 8, 200, StatStructs::THROWABLE, (-1), NULL});
		int index = character->abilities.size() - 1;
		character->abilities[index].stats = (void*)malloc(sizeof(t_Throwable));
		t_Throwable *used = (t_Throwable*)character->abilities[index].stats;
		used->range = 9;
	}
	if (!ToolExists(SUPPLY_ALLY))
	{
		character->abilities.push_back({SUPPLY_ALLY, 0, 16, 200, StatStructs::SUPPLY, (-1), NULL});
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

void ToolBox::Update()
{
	UpdateToolBoxInHand();
	ManageSmithAbilities();
}
