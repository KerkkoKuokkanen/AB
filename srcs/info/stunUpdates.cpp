
#include "../../hdr/global.h"
#define STUN_TIME 30

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
		questionMark.push_back({add, character, 0});
		PlaySound(gameState.audio.stun, Channels::STUN, 0);
	}
}

void StunUpdates::UpdateFade(int index)
{
	Character *targ = questionMark[index].target;
	if (questionMark[index].timer < STUN_TIME)
		questionMark[index].timer++;
	if (targ == NULL || targ->killed || targ->damaged)
		return ;
	if (questionMark[index].timer >= STUN_TIME)
	{
		questionMark[index].target->sprite->ColorMod(255, 219, 56);
		if (questionMark[index].target->active == false)
			questionMark[index].sprite->AlphaMod(35);
		else
			questionMark[index].sprite->ClearAlphaMod();
		return ;
	}
	float aUnit = 255.0f / 30.0f;
	int alpha = rounding(aUnit * (float)questionMark[index].timer);
	questionMark[index].sprite->AlphaMod(alpha);
	float gUnit = 36.0f / 30.0f;
	float bUnit = 199.0f / 30.0f;
	int g = rounding(gUnit * (float)questionMark[index].timer);
	int b = rounding(bUnit * (float)questionMark[index].timer);
	questionMark[index].target->sprite->ColorMod(255, 255 - g, 255 - b);
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
		UpdateFade(i);
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
