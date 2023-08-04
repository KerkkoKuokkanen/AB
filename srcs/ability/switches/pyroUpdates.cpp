
#include "../../../hdr/global.h"

void Abilities::PyroIncinerateDamage()
{
	bool visited = false;
	bool dmgVisited = false;
	for (int i = 0; i < targPoints.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targPoints[i].x][targPoints[i].y].character;
		if (targ == NULL)
		{
			if (RangeCheckWithoutBlockers(character, targ, ability))
			{
				dmgVisited = true;
				std::vector<SDL_Point> used = {targPoints[i]};
				damager.AddDamage(ability, character, used, false);
			}
			else
			{
				visited = true;
				misses.push_back(createBasicMISS(targ->position, targPoints[i], false));
			}
		}
	}
	if (visited)
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
	if (dmgVisited)
	{
		PlaySound(gameState.audio.daggerThrow[0], Channels::DAGGER_THROW0, 0);
		PlaySound(gameState.audio.daggerThrow[1], Channels::DAGGER_THROW1, 0);
	}
}

void Abilities::UpdatePyroAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case FLAME_PORT:
		{
			FlamePort *use = (FlamePort*)animation.animation;
			use->Update();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case FLAME_SLASH:
		{
			FlameSlash *use = (FlameSlash*)animation.animation;
			use->Update();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					misses.push_back(createBasicMISS(character->position, targetPoint, true));
			}
			break ;
		}
		case FLAME_BLAST:
		{
			FlameBlast *use = (FlameBlast*)animation.animation;
			use->Update();
			std::vector<t_HitReturn> ret = use->GetTargets();
			HandleDamageVector(ret);
			if (use->destroy)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case INCINERATE:
		{
			Incinerate *use = (Incinerate*)animation.animation;
			use->Update();
			if (use->createDamage)
				PyroIncinerateDamage();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
