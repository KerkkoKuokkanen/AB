
#include "../../hdr/global.h"
#define TIMETIME 30

ThugInspire::ThugInspire(Character *target)
{
	ThugInspire::target = target;
	target->setAnimationActive(true);
	counter = 0;
	done = false;
}

void ThugInspire::ManageAlpha()
{
	if (counter > 23)
		return ;
	float unit = 255.0f / 15.0f;
	if (counter <= 15)
	{
		float amount = 255.0f - unit * (float)counter;
		int used = rounding(amount);
		used = (used <= 0) ? 1 : used;
		target->sprite->ColorMod(255, used, used);
		return ;
	}
	int count = counter - 15;
	float amount = unit * (float)count;
	int used = rounding(amount);
	used = (used > 255) ? 255 : used;
	target->sprite->ColorMod(255, used, used);
}

void ThugInspire::Update()
{
	if (done)
		return ;
	counter++;
	ManageAlpha();
	if (counter == 15)
		CreateParticlesForThugIntensity0To100(target, 99);
	if (counter == 23)
		gameState.updateObjs.info->AddToFrenzyColorer(target);
	if (counter > TIMETIME)
		done = true;
}

void ThugInspire::Destroy()
{
	if (target == NULL)
		return ;
	target->setAnimationActive(false);
	target->sprite->ClearColorMod();
}
