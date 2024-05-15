
#include "../../hdr/global.h"
#define TIME 35

static Color getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(2, 66, 112));
	if (hit > 70)
		return (Color(52, 158, 235));
	if (hit > 50)
		return (Color(21, 76, 99));
	return (Color(31, 126, 163));
}

HealEffect::HealEffect(Character *character, Character *source, int amount)
{
	PlaySound(gameState.audio.BuffEffect, Channels::VOLUME_10, 0);
	HealEffect::source = source;
	HealEffect::character = character;
	HealEffect::amount = amount;
	character->setAnimationActive(true);
	gameState.updateObjs.info->AddHealEffect(this);
}

void HealEffect::UpdateColor()
{
	float r = 255.0f - 0.0f;
	float g = 255.0f - 163.0f;
	float b = 255.0f - 227.0f;
	float ru = r / 17.0f;
	float gu = g / 17.0f;
	float bu = b / 17.0f;
	if (counter < 18)
	{
		int rs = rounding(255.0f - (ru * (float)counter));
		int gs = rounding(255.0f - (gu * (float)counter));
		int bs = rounding(255.0f - (bu * (float)counter));
		character->sprite->ColorMod(rs, gs, bs);
		return ;
	}
	float count = (float)counter - 18.0f;
	int rs = rounding(0.0f + (ru * (float)count));
	int gs = rounding(163.0f + (gu * (float)count));
	int bs = rounding(227.0f + (bu * (float)count));
	if (rs > 255 || gs > 255 || bs > 255)
	{
		character->sprite->ClearColorMod();
		return ;
	}
	character->sprite->ColorMod(rs, gs, bs);
}

void HealEffect::CreateTextSnippet()
{
	CreateDamageSnippetWithColor(source->position, character, amount, Color(0, 163, 227));
}

void HealEffect::Update()
{
	if (done)
		return ;
	UpdateColor();
	if (counter == 12)
		CreateTextSnippet();
	counter++;
	if (counter >= TIME)
		done = true;
}

void HealEffect::Destroy()
{
	if (character == NULL)
		return ;
	character->setAnimationActive(false);
	character->sprite->ClearColorMod();
}
