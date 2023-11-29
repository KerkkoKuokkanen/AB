
#include "../../../hdr/global.h"

TeleStart::TeleStart(Character *character, SDL_Point target)
{
	Character *targ = gameState.battle.ground->map[target.y][target.x].character;
	TeleStart::target = targ;
	TeleStart::character = character;
	character->setAnimationActive(true);
	TeleStart::target->setAnimationActive(true);
	animation = new WitchAnimation(character, WitchAnimationType::BLUE, 1);
}

void TeleStart::UpdateTargetAlpha()
{
	if (counter < 5 || colDone)
		return ;
	if (counter <= 15)
	{
		int count = counter - 5;
		float unit = 255.0f / 10.0f;
		float minus = unit * (float)count;
		int col = rounding(255.0f - minus);
		col = (col <= 1) ? 1 : col;
		target->sprite->ColorMod(col, col, 255);
		return ;
	}
	int count = counter - 15;
	float unit = 255.0f / 10.0f;
	float add = unit * (float)count;
	int col = rounding(add);
	col = (col <= 0) ? 1 : col;
	if (col >= 255)
	{
		colDone = true;
		target->sprite->ClearColorMod();
		return ;
	}
	target->sprite->ColorMod(col, col, 255);
}

void TeleStart::Update()
{
	createEffect = false;
	if (done)
		return ;
	UpdateTargetAlpha();
	if (animation != NULL)
	{
		animation->Update();
		if (animation->done)
		{
			delete animation;
			animation = NULL;
		}
	}
	if (counter == 13)
		createEffect = true;
	counter++;
	if (counter >= 42)
		done = true;
}

void TeleStart::Destroy()
{
	target->setAnimationActive(false);
	character->setAnimationActive(false);
	if (animation != NULL)
		delete animation;
}
