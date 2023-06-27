
#include "../../hdr/global.h"

Vector Abilities::GetDirection()
{
	SDL_Rect cDest = character->sprite->dest;
	SDL_Rect eDest = target->sprite->dest;
	Vector toEnemy(cDest.x - eDest.x, cDest.y - eDest.y);
	float angle = vectorAngle(Vector(0.0f, 1.0f), toEnemy);
	float sign = (cDest.x <= eDest.x) ? 1.0f : -1.0f;
	if (angle < PI / 2)
		return(Vector(0.5 * sign, -0.5f));
	return (Vector(0.5f * sign, 0.5f));
}

void Abilities::SetSelector(t_Ability *ability, Character *character)
{
	SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(character);
	switch(ability->type)
	{
		case DAGGER_THROW:
			selector = new Selector(pos, 13, 2, false, &groundColoring);
			break ;
	}
}

void Abilities::SetAbility(t_Ability *ability, Character *character)
{
	Abilities::ability = ability;
	Abilities::character = character;
	SetSelector(ability, character);
	active = true;
}

void Abilities::ActivateAbility(t_Ability *ability, Character *character, Character *target)
{
	inMotion = true;
	switch (ability->type)
	{
		case DAGGER_THROW:
			animations.push_back({new DaggerThrowAnim(character, target), DAGGER_THROW});
			break ;
	}
}

void Abilities::Upadte()
{
	if (selector != NULL)
	{
		gameState.updateObjs.UI->ShowEnergy(ability->cost);
		Character *ret = selector->Update();
		if (ret != NULL && gameState.keys.click == RELEASE_CLICK)
		{
			gameState.updateObjs.UI->UseEnergy(ability->cost);
			target = ret;
			ActivateAbility(ability, character, ret);
			ClearMap();
		}
	}
	AnimationUpdater();
	ObjectUpdater();
	damageCreator.Update();
	groundColoring.Update();
	if (gameState.keys.rightClick == INITIAL_CLICK)
		ClearMap();
	AbilityStatus();
}

void Abilities::UpdateSpecificAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case DAGGER_THROW:
			DaggerThrowAnim *used = (DaggerThrowAnim*)animation.animation;
			used->Update();
			if (used->timeForAbility)
				objects.push_back({new Dagger(character, target, 80), DAGGER_OBJ});
			if (!used->active)
				animations.erase(animations.begin() + index);
			break ;
	}
}

void Abilities::AnimationUpdater()
{
	for (int i = 0; i < animations.size(); i++)
	{
		UpdateSpecificAnimation(animations[i], i);
	}
}

void Abilities::CreateDamage()
{
	t_Sound add2 = {gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0};
	t_Sound add3 = {gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0};
	std::vector<t_Sound> sounds = {add2, add3};
	damageCreator.CreateDamage(target, Color(255, 0, 0), 5, 5, GetDirection(), sounds);
}

void Abilities::UpdateSpecificObject(t_Object &object, int index)
{
	switch (object.type)
	{
		case DAGGER_OBJ:
			Dagger *used = (Dagger*)object.object;
			used->Update();
			if (used->remove)
			{
				if (used->createDamage)
					CreateDamage();
				used->Destroy();
				objects.erase(objects.begin() + index);
			}
	}
}

void Abilities::ObjectUpdater()
{
	for (int i = 0; i < objects.size(); i++)
	{
		UpdateSpecificObject(objects[i], i);
	}
}

void Abilities::AbilityStatus()
{
	if (!inMotion)
		return ;
	if (objects.size() == 0 && animations.size() == 0)
		Clear();
}

void Abilities::ClearMap()
{
	if (selector != NULL)
		delete selector;
	selector = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	if (!inMotion)
		active = false;
}

void Abilities::Clear()
{
	ability = NULL;
	character = NULL;
	if (selector != NULL)
		delete selector;
	selector = NULL;
	active = false;
	target = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	inMotion = false;
}
