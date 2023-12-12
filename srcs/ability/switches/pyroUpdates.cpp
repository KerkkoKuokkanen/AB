
#include "../../../hdr/global.h"

void Abilities::PyroIncinerateDamage()
{
	for (int i = 0; i < targPoints.size(); i++)
	{
		Character *targ = gameState.battle.ground->map[targPoints[i].y][targPoints[i].x].character;
		if (targ != NULL)
		{
			if (MeleeCheck(character, targ, ability))
			{
				std::vector<SDL_Point> used = {targPoints[i]};
				targ->statuses.burns.clear();
				damager.AddDamage(ability, character, used);
			}
			else
				CreateMiss(character->position, targ->position, targ, true);
		}
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
			if (use->createSelfDamage)
			{
				t_FlamePortStats *stats = (t_FlamePortStats*)ability->stats;
				int amount = stats->selfDamagePrecent;
				float multi = ((float)amount / 100.0f);
				int healthMinus = rounding((float)character->stats.maxHealth * multi);
				int health = (character->stats.health - healthMinus <= 0) ? 1 : character->stats.health - healthMinus;
				character->stats.health = health;
				PlaySound(gameState.audio.heartBeat, Channels::VOLUME_35, 0);
				gameState.updateObjs.info->SetCritFilter();
			}
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
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
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
