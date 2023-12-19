
#include "../../../hdr/global.h"

static bool CompFunc(t_RandChar &one, t_RandChar &two)
{
	if (one.value < two.value)
		return (true);
	return (false);
}

static SDL_Point GetDamagerPos(void *damager, int type)
{
	if (type == 0)
	{
		Character *ret = (Character*)damager;
		return (ret->position);
	}
	PhantomKnight *used = (PhantomKnight*)damager;
	return (used->position);
}

static Vector GetDirection(void *damager, int type, Character *target)
{
	SDL_Point cPos = GetDamagerPos(damager, type);
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

static bool CheckForAdditionalValid(Character *target, SDL_Point pos)
{
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	if (used->additional.object == NULL)
		return (false);
	if (used->additional.type != AdditionalObjects::PHANTOM_KNIGHT)
		return (false);
	PhantomKnight *ret = (PhantomKnight*)used->additional.object;
	Character *PC = ret->character;
	if (PC->ally == target->ally)
		return (false);
	return (true);
}

bool AbilityOpportunity::CheckValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	if (CheckIfSmoked(pos))
		return (false);
	if (CheckForAdditionalValid(target, pos))
		return (true);
	Character *ret = gameState.battle.ground->map[pos.y][pos.x].character;
	if (ret == NULL)
		return (false);
	if (ret->cSing == TOOLS)
		return (false);
	if (ret->killed)
		return (false);
	if (ret->ally == target->ally)
		return (false);
	if (ret->statuses.stun != 0)
		return (false);
	return (true);
}

static t_Damager GetTheAttacker(SDL_Point pos)
{
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	t_Damager ret;
	if (used->additional.object != NULL && used->additional.type == AdditionalObjects::PHANTOM_KNIGHT)
	{
		ret = {used->additional.object, 1};
		return (ret);
	}
	ret = {used->character, 0};
	return (ret);
}

static Character *GetTheCharacterForAttack(t_Damager &damager)
{
	if (damager.type == 0)
	{
		Character *character = (Character*)damager.damager;
		return (character);
	}
	PhantomKnight *used = (PhantomKnight*)damager.damager;
	return (used->character);
}

bool AbilityOpportunity::CheckValidForAdditional(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	if (CheckIfSmoked(pos))
		return (false);
	Character *ret = gameState.battle.ground->map[pos.y][pos.x].character;
	if (ret == NULL)
		return (false);
	if (ret->killed)
		return (false);
	if (ret->cSing == TOOLS)
		return (false);
	if (ret->ally == target->ally)
		return (false);
	if (ret->statuses.stun != 0)
		return (false);
	if (ret->cSing != KNIGHT)
		return (false);
	if (ret->statuses.controlZone <= 0)
		return (false);
	return (true);
}

void AbilityOpportunity::AddAdditionalDamagers(SDL_Point pos, std::vector<t_RandChar> &adds)
{
	SDL_Point checks[8] = {
		GetPositionFromCoordinates(pos, {-2, -2}),
		GetPositionFromCoordinates(pos, {0, -2}),
		GetPositionFromCoordinates(pos, {2, -2}),
		GetPositionFromCoordinates(pos, {1, 0}),
		GetPositionFromCoordinates(pos, {2, 2}),
		GetPositionFromCoordinates(pos, {0, 2}),
		GetPositionFromCoordinates(pos, {-2, 2}),
		GetPositionFromCoordinates(pos, {-1, 0})
	};
	for (int i = 0; i < 8; i++)
	{
		if (CheckValidForAdditional(checks[i]))
			adds.push_back({GetTheAttacker(checks[i]), rand() % 1000});
	}
}

t_Damager AbilityOpportunity::GetDamager(Character *target)
{
	SDL_Point pos = target->position;
	int left = getXToLeft(pos);
	int right = getXToRight(pos);
	std::vector<t_RandChar> chars;
	if (CheckValid({left, pos.y + 1}))
		chars.push_back({GetTheAttacker({left, pos.y + 1}), rand() % 1000});
	if (CheckValid({left, pos.y - 1}))
		chars.push_back({GetTheAttacker({left, pos.y - 1}), rand() % 1000});
	if (CheckValid({right, pos.y + 1}))
		chars.push_back({GetTheAttacker({right, pos.y + 1}), rand() % 1000});
	if (CheckValid({right, pos.y - 1}))
		chars.push_back({GetTheAttacker({right, pos.y - 1}), rand() % 1000});
	AddAdditionalDamagers(pos, chars);
	hits = false;
	damager.damager = NULL;
	if (chars.size() == 0)
		return (damager);
	std::sort(chars.begin(), chars.end(), CompFunc);
	for (int i = 0; i < chars.size(); i++)
	{
		if (CheckIfOpportunityHits(GetTheCharacterForAttack(chars[i].used), target))
		{
			hits = true;
			damager.damager = chars[i].used.damager;
			damager.type = chars[i].used.type;
			return (damager);
		}
	}
	damager.damager = chars[0].used.damager;
	damager.type = chars[0].used.type;
	return (damager);
}

static Sprite *GetDamagerSprite(void *damager, int type)
{
	if (type == 0)
	{
		Character *ret = (Character*)damager;
		return (ret->sprite);
	}
	PhantomKnight *used = (PhantomKnight*)damager;
	return (used->GetSprite());
}

void AbilityOpportunity::StartDamage()
{

	mover = new SpriteMover(GetDamagerSprite(damager.damager, damager.type), GetDirection(damager.damager, damager.type, target), 20, 140.0f);
	if (hits)
		PlaySound(gameState.audio.opportunity, Channels::OPPORTUNIRY, 0);
}

void AbilityOpportunity::AxeSlashUpdate()
{
	if (mover != NULL)
		return ;
	if (gameState.updateObjs.abilities->ability == NULL ||
		gameState.updateObjs.abilities->inMotion == false ||
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
	damager = GetDamager(ret);
	if (damager.damager == NULL)
	{
		target = NULL;
		return ;
	}
	StartDamage();
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
		ManageAbilityType();
		gameState.updateObjs.abilities->CreateOpportunityDamage(GetDamagerPos(damager.damager, damager.type), target);
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
			damager.damager = NULL;
		}
	}
}

void AbilityOpportunity::Destroy()
{
	if (mover != NULL)
		delete mover;
}
