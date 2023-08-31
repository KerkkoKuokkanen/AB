
#include "../../hdr/global.h"

Character::Character(int skin, bool allied)
{
	CreateCharacterType(skin);
	AssignAbilities();
	Vector top = GetCharacterTopMid(this);
	top.x = top.x - (float)sprite->dest.x;
	top.y = top.y - (float)sprite->dest.y;
	topMid = {rounding(top.x), rounding(top.y)};
	statuses.stun = 0;
	statuses.burns = {};
	width = 5800;
	height = 7500;
	if (!allied)
		ally = false;
}

void Character::DeleteCharacter()
{
	delete sprite;
	delete stand;
	delete this;
}

void Character::AddToRender()
{
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	gameState.render->AddSprite(stand, BATTLEGROUND_LAYER);
}

void Character::FindPosition()
{
	if (!moving)
		position = gameState.updateObjs.indicator->FindCharacter(this);
}

void Character::ShiftChecker()
{
	if (!moving)
	{
		FindPosition();
		SDL_Point pos = position;
		if (gameState.battle.ground->map[pos.y][pos.x].active)
		{
			if (gameState.modes.filterMode == 1 || gameState.keys.control != 0)
			{
				active = false;
					sprite->AlphaMod(35);
				stand->AlphaMod(35);
			}
			else
			{
				active = true;
				sprite->ClearAlphaMod();
				stand->ClearAlphaMod();
			}
		}
	}
}

void Character::ManageFatigue()
{
	if (!wasTurn && turn)
	{
		wasTurn = true;
		stats.fatigue -= 23;
	}
	if (wasTurn && !turn)
		wasTurn = false;
	if (stats.fatigue > stats.maxFatigue)
		stats.fatigue = stats.maxFatigue;
	if (stats.fatigue < 0)
		stats.fatigue = 0;
}

void Character::Update()
{
	if (killed)
	{
		clicked = false;
		return ;
	}
	if (stats.health <= 0)
		gameState.updateObjs.killer->AddCharacterToKill(this);
	if (gameState.keys.rightClick == 1 && gameState.keys.click != 1)
		clicked = false;
	if (gameState.keys.click == RELEASE_CLICK && cSing == LION)
		new SupplyEffect(this);
	ShiftChecker();
	ManageFatigue();
	if (animationActive)
		return ;
	if (gameState.updateObjs.characterAnimIter == 50)
	{
		currentTexture = (currentTexture == 0) ? 1 : 0;
		if (statuses.stun > 0)
			return ;
		sprite->setTexture(textures[gameState.updateObjs.characterAnimIndex]);
		stand->setTexture(stands[gameState.updateObjs.characterAnimIndex]);
	}
}

void Character::setCoord(SDL_Point &coord)
{
	Character::coord = coord;
}

SDL_Point &Character::getCoord()
{
	return (coord);
}

void Character::Position(Vector to)
{
	sprite->Position(to);
	stand->Position(to);
};

void Character::Move(Vector amount)
{
	sprite->Move(amount);
	stand->Move(amount);
};

void Character::Destroy()
{
	delete sprite;
	delete stand;
	for (int i = 0; i < abilities.size(); i++)
	{
		if (abilities[i].stats != NULL)
			free(abilities[i].stats);
	}
	textures.clear();
	stands.clear();
}
