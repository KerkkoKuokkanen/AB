
#include "../../../hdr/global.h"

static std::vector<Character*> GetInspireTargets(Character *character, t_Ability *ability)
{
	SDL_Point pos = character->position;
	int range = ability->range;
	std::vector<Character*> tagets = {};
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *targ = gameState.battle.ground->characters[i].character;
		if (character->ally != targ->ally)
			continue ;
		if (targ->cSing != THUG)
			continue ;
		SDL_Point tPos = targ->position;
		int dist = DistanceBetweenPoints(pos, tPos);
		if (dist <= range)
			tagets.push_back(targ);
	}
	return (tagets);
}

void Abilities::UpdateEnemyAnimationOne(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case SKELE_MELEE:
		{
			SkeleMeleeAnim *used = (SkeleMeleeAnim*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case SKELE_LUNGE:
		{
			SkeleLunge *used = (SkeleLunge*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
				{
					std::vector<SDL_Point> point = {target->position};
					damager.AddDamage(ability, character, point);
				}
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				PlaySound(gameState.audio.BuffEffect, Channels::VOLUME_11, 0);
				AddBuffToCharacter(character, {BuffTypes::OPPORTUNITY_ACCURACY, 2, 50, false, BuffDebuffId::SKELE_OPP});
				new BuffEffect(character, true);
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case BIG_THUG_STRIKE:
		{
			BigThugStrike *used = (BigThugStrike*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case THUG_STRIKE:
		{
			ThugStrike *used = (ThugStrike*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					CreateMiss(character->position, target->position, target, true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case BIG_THUG_INSPIRE:
		{
			BigThugInspire *used = (BigThugInspire*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}