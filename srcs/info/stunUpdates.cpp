
#include "../../hdr/global.h"

bool StunUpdates::StunExists(Character *character)
{
	if (character == NULL)
		return (true);
	for (int i = 0; i < questionMark.size(); i++)
	{
		if (questionMark[i].target == character)
			return (true);
	}
	return (false);
}

void StunUpdates::CreateStuns()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *character = gameState.battle.ground->characters[i].character;
		if (character->statuses.stun <= 0)
			continue ;
		if (character->damaged || character->killed || character->moving)
			continue ;
		if (StunExists(character))
			continue ;
		SDL_Point pos = character->topMid;
		SDL_Rect dest = {character->sprite->dest.x + pos.x - 500, character->sprite->dest.y + pos.y - 1000, 1000, 1000};
		Sprite *add = new Sprite(gameState.textures.questionMark, dest, NULL, NULL, 0, FLIP_NONE);
		add->z = character->sprite->z + 0.1f;
		add->orderLayer = character->sprite->orderLayer;
		gameState.render->AddSprite(add, BATTLEGROUND_LAYER);
		questionMark.push_back({add, character});
	}
}

void StunUpdates::IterStuns()
{
	bool disable = (gameState.screen.unit < 0.000015f) ? true : false;
	for (int i = 0; i < questionMark.size(); i++)
	{
		if (disable)
			questionMark[i].sprite->Deactivate();
		else
			questionMark[i].sprite->Activate();
		if (questionMark[i].target->active == false)
			questionMark[i].sprite->AlphaMod(35);
		else
			questionMark[i].sprite->ClearAlphaMod();
		questionMark[i].target->sprite->ColorMod(255, 219, 56);
		if (questionMark[i].target->killed || questionMark[i].target->statuses.stun <= 0)
		{
			questionMark[i].target->sprite->ClearColorMod();
			delete questionMark[i].sprite;
			questionMark.erase(questionMark.begin() + i);
			if (i != 0)
				i -= 1;
		}
	}
}

void StunUpdates::UpdateStuns()
{
	CreateStuns();
	IterStuns();
}

void StunUpdates::Update()
{
	UpdateStuns();
}

void StunUpdates::Destroy()
{
	for (int i = 0; i < questionMark.size(); i++)
		delete questionMark[i].sprite;
	questionMark.clear();
}
