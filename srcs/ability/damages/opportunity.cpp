
#include "../../../hdr/global.h"

typedef struct s_RandChar
{
	t_Damager used;
	int value;
}				t_RandChar;

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

bool CheckIfOpportunityHits(Character *damager, Character *target)
{
	int hit = rand() % 100;
	if (hit >= 50)
		return (false);
	return (true);
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

Vector OpportunityAttack::GetDirection()
{
	SDL_Point cPos = GetDamagerPos(damager.damager, damager.type);
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

bool OpportunityAttack::CheckValid(SDL_Point pos)
{
	if (pos.x < 0 || pos.x >= gameState.battle.ground->map[0].size())
		return (false);
	if (pos.y < 0 || pos.y >= gameState.battle.ground->map.size())
		return (false);
	if (gameState.battle.ground->map[pos.y][pos.x].additional.type == AdditionalObjects::PHANTOM_KNIGHT &&
		gameState.battle.ground->map[pos.y][pos.x].additional.object != NULL)
		return (true);
	Character *ret = gameState.battle.ground->map[pos.y][pos.x].character;
	if (ret == NULL)
		return (false);
	if (ret->killed)
		return (false);
	if (ret->ally == target->ally)
		return (false);
	if (ret->statuses.stun != 0)
		return (false);
	if (CheckIfSmoked(pos))
		return (false);
	return (true);
}

static t_Damager GetTheAttacker(SDL_Point pos)
{
	t_GMU *used = &gameState.battle.ground->map[pos.y][pos.x];
	t_Damager ret;
	if (used->character != NULL)
	{
		ret = {used->character, 0};
		return (ret);
	}
	ret = {used->additional.object, 1};
	return (ret);
}

t_Damager OpportunityAttack::GetDamager()
{
	SDL_Point pos = gameState.battle.ground->movedCharacter.path[tried];
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

void OpportunityAttack::StartDamage()
{
	if (damager.damager == NULL || target == NULL)
		return ;
	mover = new SpriteMover(GetDamagerSprite(damager.damager, damager.type), GetDirection(), 20, 140.0f);
	if (hits)
		PlaySound(gameState.audio.opportunity, Channels::OPPORTUNIRY, 0);
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
	if (damager.damager == NULL)
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
		gameState.updateObjs.abilities->CreateOpportunityDamage(GetDamagerPos(damager.damager, damager.type), target);
		if (gameState.battle.ground->movedCharacter.character->cSing != LION)
			gameState.battle.ground->CancelMovement(gameState.battle.ground->movedCharacter.path[tried]);
		return ;
	}
	else
		PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
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
			damager.damager = NULL;
		}
	}
}

void OpportunityAttack::Destroy()
{
	if (mover != NULL)
		delete mover;
}
