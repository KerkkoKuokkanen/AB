
#include "../../../hdr/global.h"

typedef struct s_RandChar
{
	Character *character;
	int value;
}				t_RandChar;

static bool CompFunc(t_RandChar &one, t_RandChar &two)
{
	if (one.value < two.value)
		return (true);
	return (false);
}

static bool CheckIfSmoked(SDL_Point pos)
{
	for (int i = 0; i < gameState.updateObjs.abilities->effectUpdater.effects.size(); i++)
	{
		t_AbilityEffect &effect = gameState.updateObjs.abilities->effectUpdater.effects[i];
		if (effect.ability->type == SMOKE_BOMB && effect.pos.x == pos.x && effect.pos.y == pos.y)
			return (true);
	}
	return (false);
}

static Vector GetDirection(Character *damager, Character *target)
{
	SDL_Point cPos = damager->position;
	SDL_Point tPos = target->position;
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(tPos);
	SDL_Point dir = {dest2.x - dest1.x, dest2.y - dest1.y};
	return (Vector((float)dir.x, (float)dir.y).Normalized());
}

Character *AbilityOpportunity::GetTarget()
{
	if (gameState.updateObjs.abilities->active == false)
		return (NULL);
	return (gameState.updateObjs.abilities->GetCharacter());
}

Character *AbilityOpportunity::CheckValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (NULL);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (NULL);
	Character *ret = gameState.battle.ground->map[pos.y][pos.x].character;
	if (ret == NULL)
		return (NULL);
	if (ret->killed)
		return (NULL);
	if (ret->ally == target->ally)
		return (NULL);
	if (ret->statuses.stun != 0)
		return (NULL);
	if (CheckIfSmoked(pos))
		return (NULL);
	return (ret);
}

Character *AbilityOpportunity::GetDamager(Character *target)
{
	SDL_Point pos = target->position;
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
	std::vector<t_RandChar> chars;
	Character *ret1 = CheckValid({left, pos.y + 1});
	if (ret1 != NULL)
		chars.push_back({ret1, rand() % 1000});
	Character *ret2 = CheckValid({left, pos.y - 1});
	if (ret2 != NULL)
		chars.push_back({ret2, rand() % 1000});
	Character *ret3 = CheckValid({right, pos.y + 1});
	if (ret3 != NULL)
		chars.push_back({ret3, rand() % 1000});
	Character *ret4 = CheckValid({right, pos.y - 1});
	if (ret4 != NULL)
		chars.push_back({ret4, rand() % 1000});
	hits = false;
	if (chars.size() == 0)
		return (NULL);
	std::sort(chars.begin(), chars.end(), CompFunc);
	for (int i = 0; i < chars.size(); i++)
	{
		if (CheckIfOpportunityHits(chars[i].character, target))
		{
			hits = true;
			return (chars[i].character);
		}
	}
	return (chars[0].character);
}

void AbilityOpportunity::StartDamage(Character *damager)
{
	mover = new CharacterMover(damager, GetDirection(damager, target), 10, 10, 220.0f);
	if (hits)
		PlaySound(gameState.audio.opportunity, Channels::OPPORTUNIRY, 0);
}

void AbilityOpportunity::AxeSlashUpdate()
{
	if (mover != NULL)
		return ;
	if (gameState.updateObjs.abilities->inMotion == false ||
		gameState.updateObjs.abilities->ability->type != AXE_JUMP)
	{
		target = NULL;
		triedForAxe = false;
		return ;
	}
	if (triedForAxe)
		return ;
	triedForAxe = true;
	Character *ret = GetTarget();
	if (ret == NULL)
		return ;
	target = ret;
	Character *damager = GetDamager(ret);
	if (damager == NULL)
	{
		target = NULL;
		return ;
	}
	StartDamage(damager);
}

void AbilityOpportunity::ManageAbilityType()
{
	t_Ability *ability = gameState.updateObjs.abilities->ability;
	t_Animation *anim = gameState.updateObjs.abilities->GetAnimation(ability->type);
	if (anim == NULL)
		return ;
	switch (anim->type)
	{
		case AXE_JUMP:
		{
			AxeJumpAnim *used = (AxeJumpAnim*)anim->animation;
			if (used->arch != NULL)
				delete used->arch;
			used->arch = NULL;
			used->done = true;
			gameState.battle.ground->PlaceCharacter(target->position, target);
			target->sprite->setTexture(gameState.textures.chars.raiderIdle[0]);
			break ;
		}
	}
}

void AbilityOpportunity::CreateDamageOrMiss()
{
	if (hits)
	{
		Character *damager = mover->GetCharacter();
		ManageAbilityType();
		gameState.updateObjs.abilities->CreateOpportunityDamage(damager, target);
		return ;
	}
	else
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
}

void AbilityOpportunity::Update()
{
	AxeSlashUpdate();
	if (mover != NULL)
	{
		int ret = mover->Update();
		if (ret == 8)
			CreateDamageOrMiss();
		if (ret == (-1))
		{
			delete mover;
			mover = NULL;
			target = NULL;
		}
	}
}

void AbilityOpportunity::Destroy()
{
	if (mover != NULL)
		delete mover;
}
