
#include "../../../hdr/global.h"

static bool CheckIfValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	return (true);
}

static SDL_Point GetAttackerPos(Character *attacker, Character *target)
{
	int left = getXToLeft(target->position);
	int right = getXToRight(target->position);
	SDL_Point pos = target->position;
	SDL_Point ret = target->position;
	SDL_Point check = GetPositionFromCoordinates(pos, {1, -1});
	t_GMU *tester = NULL;
	if (CheckIfValid(check))
	{
		tester = &gameState.battle.ground->map[check.y][check.x];
		if (tester->character != NULL && tester->character == attacker)
		{
			ret = {1, -1};
			return (ret);
		}
	}
	if (CheckIfValid(check))
	{
		check = GetPositionFromCoordinates(pos, {1, 1});
		tester = &gameState.battle.ground->map[check.y][check.x];
		if (tester->character != NULL && tester->character == attacker)
		{
			ret = {1, 1};
			return (ret);
		}
	}
	if (CheckIfValid(check))
	{
		check = GetPositionFromCoordinates(pos, {-1, -1});
		tester = &gameState.battle.ground->map[check.y][check.x];
		if (tester->character != NULL && tester->character == attacker)
		{
			ret = {-1, -1};
			return (ret);
		}
	}
	if (CheckIfValid(check))
	{
		check = GetPositionFromCoordinates(pos, {-1, 1});
		tester = &gameState.battle.ground->map[check.y][check.x];
		if (tester->character != NULL && tester->character == attacker)
		{
			ret = {-1, 1};
			return (ret);
		}
	}
	return (ret);
}

static SDL_Point GetLandingPos(Character *attacker, Character *target)
{
	SDL_Point atk = GetAttackerPos(attacker, target);
	if (atk.x == target->position.x && atk.y == target->position.y)
		return (target->position);
	SDL_Point ret = {-atk.x, -atk.y};
	SDL_Point check = GetPositionFromCoordinates(target->position, ret);
	ret = check;
	if (ret.y < 0 || ret.y >= gameState.battle.ground->map.size())
		return (target->position);
	if (ret.x < 0 || ret.x >= gameState.battle.ground->map[0].size())
		return (target->position);
	if (gameState.battle.ground->map[ret.y][ret.x].blocked)
		return (target->position);
	return (ret);
}

void Abilities::CreateShieldBashDamage()
{
	SDL_Point land = GetLandingPos(character, target);
	bool moveChance = MoveChanceCheck(ability, character, target);
	if ((land.x == target->position.x && land.y == target->position.y) || moveChance == false)
	{
		bool check = StatusApply(ability, character, target, true);
		if (!check && target->statuses.stun == 0)
			CreateTextSnippet(character, target, "MISS", 900, Color(186, 168, 0));
		else
		{
			if (target->statuses.stun == 0)
				CreateTextSnippet(character, target, "stunned", 1200, Color(186, 168, 0));
			target->statuses.stun = 1;
		}
		CreateDamage();
	}
	else
	{
		PlaySound(gameState.audio.shieldBash[1], Channels::VOLUME_70, 0);
		SetScreenShake(150, 4);
		objects.push_back({new BashMover(character, target, land), SHILED_BASH});
	}
}

void Abilities::UpdateKnightAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case FLAIL_STRIKE:
		{
			KnightAttack *used = (KnightAttack*)anim.animation;
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
		case SHILED_BASH:
		{
			ShieldBash *used = (ShieldBash*)anim.animation;
			used->Update();
			if (used->createDamage)
			{
				if (!MeleeCheck(character, target, ability))
					CreateMiss(character->position, target->position, target, true);
				else
				{
					new ShieldBashEffect(character, target);
					CreateShieldBashDamage();
				}
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case CONTROL_ZONE:
		{
			ControlZone *used = (ControlZone*)anim.animation;
			used->Update();
			if (used->createBuff)
			{
				character->statuses.controlZone = 1;
				t_ControlZone *ret = (t_ControlZone*)ability->stats;
				if (ret->endTurn)
					gameState.updateObjs.turnOrder->ActivateTurnChange(true);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}

void Abilities::UpdateKnightObjects(t_Object &object, int index)
{
	switch (object.type)
	{
		case SHILED_BASH:
		{
			BashMover *used = (BashMover*)object.object;
			used->Update();
			if (used->done)
			{
				bool check = StatusApply(ability, character, target, true);
				if (!check && target->statuses.stun == 0)
					CreateTextSnippet(character, target, "MISS", 900, Color(186, 168, 0));
				else
				{
					if (target->statuses.stun == 0)
						CreateTextSnippet(character, target, "stunned", 1200, Color(186, 168, 0));
					target->statuses.stun = 1;
				}
				CreateDamage();
				delete used;
				objects.erase(objects.begin() + index);
			}
			break ;
		}
	}
}
