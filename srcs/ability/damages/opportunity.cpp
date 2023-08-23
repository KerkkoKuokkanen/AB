
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

static bool CheckIfHits(Character *damager, Character *target)
{
	int hit = rand() % 100;
	if (hit >= 50)
		return (false);
	return (true);
}

Vector OpportunityAttack::GetDirection()
{
	SDL_Point cPos = damager->position;
	int index = gameState.battle.ground->movedCharacter.index;
	SDL_Point tPos = gameState.battle.ground->movedCharacter.path[index];
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(cPos);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(tPos);
	SDL_Point dir = {dest2.x - dest1.x, dest2.y - dest1.y};
	return (Vector((float)dir.x, (float)dir.y).Normalized());
}

Character *OpportunityAttack::AnyOneMoving()
{
	Character *ret = gameState.battle.ground->movedCharacter.character;
	return (ret);
}

Character *OpportunityAttack::CheckValid(SDL_Point pos)
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
	return (ret);
}

Character *OpportunityAttack::GetDamager()
{
	SDL_Point pos = gameState.battle.ground->movedCharacter.path[tried];
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
		if (CheckIfHits(chars[i].character, target))
		{
			hits = true;
			return (chars[i].character);
		}
	}
	return (chars[0].character);
}

void OpportunityAttack::StartDamage()
{
	if (damager == NULL || target == NULL)
		return ;
	mover = new CharacterMover(damager, GetDirection(), 10, 10, 220.0f);
	if (!hits)
	{
		SDL_Point pos = gameState.battle.ground->movedCharacter.path[gameState.battle.ground->movedCharacter.path.size() - 1];
	}
	else
	{
		PlaySound(gameState.audio.opportunity, Channels::OPPORTUNIRY, 0);
		SDL_Point pos = gameState.battle.ground->movedCharacter.path[1];
	}
}

void OpportunityAttack::CheckForTargets()
{
	if (mover != NULL)
		return ;
	Character *ret = AnyOneMoving();
	if (ret == NULL)
	{
		tried = (-1);
		return ;
	}
	if (tried == gameState.battle.ground->movedCharacter.index)
		return ;
	tried = gameState.battle.ground->movedCharacter.index;
	target = ret;
	damager = GetDamager();
	if (damager == NULL)
	{
		SDL_Point pos = gameState.battle.ground->movedCharacter.path[gameState.battle.ground->movedCharacter.path.size() - 1];
		target = NULL;
		return ;
	}
	StartDamage();
}

void OpportunityAttack::CreateDamageOrMiss()
{
	if (hits)
	{
		gameState.updateObjs.abilities->CreateOpportunityDamage(damager, target);
		gameState.battle.ground->CancelMovement(gameState.battle.ground->movedCharacter.path[tried]);
		return ;
	}
}

void OpportunityAttack::Update()
{
	CheckForTargets();
	if (mover != NULL)
	{
		int ret = mover->Update();
		if (ret == 9)
			CreateDamageOrMiss();
		if (ret == (-1))
		{
			delete mover;
			mover = NULL;
			target = NULL;
			damager = NULL;
		}
	}
}

void OpportunityAttack::Destroy()
{
	if (mover != NULL)
		delete mover;
}
