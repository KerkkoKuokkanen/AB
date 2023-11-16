
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
		questionMark.push_back({character, 0});
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
		return ;
	}
	float aUnit = 255.0f / 30.0f;
	int alpha = rounding(aUnit * (float)questionMark[index].timer);
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
		UpdateFade(i);
		if (questionMark[i].target->killed || questionMark[i].target->statuses.stun <= 0)
		{
			questionMark[i].target->sprite->ClearColorMod();
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
	questionMark.clear();
}
