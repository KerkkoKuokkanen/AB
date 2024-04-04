
#include "../../hdr/global.h"
#define MAX_ALPHA 100.0f

static bool ParticlesAllowed(Character *character)
{
	if (character->moving)
		return (false);
	if (gameState.updateObjs.abilities->inMotion && character->turn)
		return (false);
	if (character->killed)
		return (false);
	return (true);
}

static float GetIntensity(int intensity)
{
	int used = intensity;
	float unit = 1.0f / MAX_ALPHA;
	float amount = 1.0f - (unit * (float)used);
	return (amount);
}

static int HowManyParticles(int counter, int intensity)
{
	if (counter % 15 != 0)
		return (0);
	float it = GetIntensity(intensity);
	float amount = (float)(rand() % 5 + 10) * it;
	return (rounding(amount));
}

void FrenzyColorer::UpdateUnits()
{
	for (int i = 0; i < frenzys.size(); i++)
	{
		frenzys[i].counter++;
		float unit = (float)frenzys[i].counter / 140.0f;
		frenzys[i].fadeMulti = ((0.5f * cos(unit)) / 2.0f + 0.25f) + 1.0f;
		float fadeMulti = cos(gameState.updateObjs.fadeIter * frenzys[i].fadeMulti) / 2.0f + 0.5f;
		float alphaAmount = (MAX_ALPHA * fadeMulti);
		int alpha = rounding(alphaAmount);
		int amount = HowManyParticles(frenzys[i].counter, alpha);
		if (amount != 0 && ParticlesAllowed(frenzys[i].target))
			CreateParticlesForThugIntensity0To100(frenzys[i].target, amount);
		frenzys[i].target->sprite->ColorMod(255, 130 + alpha, 130 + alpha);
		if (frenzys[i].counter > 2147482647)
			frenzys[i].counter = 0;
		if (frenzys[i].target->killed || frenzys[i].target->statuses.frenzy <= 0)
		{
			frenzys[i].target->sprite->ClearColorMod();
			frenzys.erase(frenzys.begin() + i);
			i = (frenzys.size() == 0) ? 0 : i - 1;
		}
	}
}

void FrenzyColorer::Update()
{
	UpdateUnits();
}

void FrenzyColorer::AddCharacter(Character *target)
{
	for (int i = 0; i < frenzys.size(); i++)
	{
		if (frenzys[i].target == target)
			return ;
	}
	t_Frenzys add;
	add.counter = rand() % 10000;
	add.target = target;
	add.fadeMulti = 1.0f;
	frenzys.push_back(add);
}

void FrenzyColorer::Destroy()
{
	frenzys.clear();
}
