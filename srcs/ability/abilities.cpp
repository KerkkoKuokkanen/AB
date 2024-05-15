
#include "../../hdr/global.h"

static void SetSelectorForRotate(t_Ability *ability, Selector *selector)
{
	int *tier = (int*)ability->stats;
	selector->ClearStunned(true, false);
	if (*tier == 1)
		selector->SetSelectorFor(true, false);
	else
		selector->SetSelectorFor(true, true);
}

static void SetSelectorForHostEyes(t_Ability *ability, Selector *selector)
{
	t_HostEyes *used = (t_HostEyes*)ability->stats;
	if (used->enemyChance > 0)
		selector->SetSelectorFor(true, true);
	else
		selector->SetSelectorFor(true, false);
}

void Abilities::SetSelector(t_Ability *ability, Character *character)
{
	SDL_Point pos = character->position;
	switch(ability->type)
	{
		case DAGGER_THROW:
			selector = new Selector(pos, ability->range, 2, &groundColoring, false); // have to chance these hardCoded numbers later
			break ;
		case DAGGER_SLASH:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case SMOKE_BOMB:
			tileSelector = new TileSelector(pos, ability->range, 0, &groundColoring, false);
			tileSelector->IncludePoint(pos);
			break ;
		case FLAME_PORT:
			tileSelector = new TileSelector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case FLAME_SLASH:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case FLAME_BLAST:
			multiSelector = new MultiSelector(pos, ability->range, 0, &groundColoring, false, 4);
			break ;
		case INCINERATE:
			allSelector = new AllSelector(pos, ability->range, 0, &groundColoring, true, StatusSigns::BURN);
			break ;
		case LION_SMACK:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case PHANTOM_KNIGHT:
			tileSelector = new TileSelector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case ROTATE:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			SetSelectorForRotate(ability, selector);
			break ;
		case HAMMER_SMACK:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case THROW_TOOLBOX:
			tileSelector = new TileSelector(pos, ability->range, 0, &groundColoring, true);
			tileSelector->RemovePoint(character->position);
			break ;
		case SUPPLY_ALLY:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			selector->SetSelectorFor(true, false);
			break ;
		case PICK_UP_TOOLS:
			tileSelector = new TileSelector(pos, 1, 0, &groundColoring, false, true);
			tileSelector->RemovePoint(character->position);
			FindToolBox(tileSelector);
			break ;
		case SUPPLY:
			tileSelector = new TileSelector(pos, 1, 0, &groundColoring, false, true);
			tileSelector->RemovePoint(character->position);
			IncudeToolPoints(tileSelector);
			break ;
		case GENERIC_TOOL_THROW:
		{
			TileSelector *used = new TileSelector(pos, 1, 0, &groundColoring, false, true);
			IncudeToolPoints(used);
			selectorQueue = new SelectorQueue(&groundColoring, used);
			selectorQueue->AddNextSelector(false, {-1, -1}, (character->cSing == LION) ? ability->range + 1 : ability->range, 0, true, false);
			break ;
		}
		case SMITH_BUFF:
			selector = new Selector(pos, ability->range, 0, &groundColoring, false);
			selector->SetSelectorFor(true, true);
			break ;
		case LIGHTNING_BOLT:
			selector = new Selector(pos, ability->range, 4, &groundColoring, false);
			ExtendSelector(character, selector);
			break ;
		case ROCK_FALL:
			phantSelector = new PhantomSelector(character, ability->range, &groundColoring);
			phantSelector->SetDefaultAdditionals();
			ExtendPhantSelector(character, phantSelector);
			break ;
		case HOST_EYES:
			selector = new Selector(pos, ability->range, 2, &groundColoring, false);
			SetSelectorForHostEyes(ability, selector);
			ExtendSelector(character, selector);
			break ;
		case AXE_SLASH:
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		case AXE_JUMP:
			axeJumpSelector = new AxeJumpSelector(pos, ability->range, &groundColoring);
			break ;
		case TOXIC_BLADE:
			ActivateAbility(ability, character);
			break ;
		case RAIDER_BLOCK:
			ActivateAbility(ability, character);
			break ;
		case NAIL_BOMB:
		{
			phantSelector = new PhantomSelector(character, ability->range, &groundColoring, 0);
			phantSelector->RemovePoint(character->position);
			phantSelector->SetDefaultAdditionals();
			t_DamageBomb *used = (t_DamageBomb*)ability->stats;
			if (used->additionalBlocks)
				phantSelector->SetAdditionalHighlights({{0, -2}, {0, 2}, {-1, 0}, {1, 0}});
			break ;
		}
		case ACID_BOMB:
		{
			phantSelector = new PhantomSelector(character, ability->range, &groundColoring, 0);
			phantSelector->RemovePoint(character->position);
			phantSelector->SetDefaultAdditionals();
			t_DamageBomb *used = (t_DamageBomb*)ability->stats;
			if (used->additionalBlocks)
				phantSelector->SetAdditionalHighlights({{0, -2}, {0, 2}, {-1, 0}, {1, 0}});
			break ;
		}
		case SLOW_BOMB:
		{
			phantSelector = new PhantomSelector(character, ability->range, &groundColoring, 0);
			phantSelector->RemovePoint(character->position);
			phantSelector->SetDefaultAdditionals();
			t_SlowBomb *used = (t_SlowBomb*)ability->stats;
			if (used->additionalBlocks)
				phantSelector->SetAdditionalHighlights({{0, -2}, {0, 2}, {-1, 0}, {1, 0}});
			break ;
		}
		case GO_FOR_THE_HEAD:
		{
			selector = new Selector(pos, ability->range, 0, &groundColoring, true);
			break ;
		}
		case FLAIL_STRIKE:
			selector = new Selector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case SHILED_BASH:
			selector = new Selector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case CONTROL_ZONE:
			ActivateAbility(ability, character);
			break ;
		case ACID_RAIN:
			selector = new Selector(character->position, ability->range, 2, &groundColoring, false);
			break ;
		case TELEPORT:
		{
			Selector *used = new Selector(character->position, ability->range, 0, &groundColoring, false);
			used->SetSelectorFor(true, true);
			used->AddAdditionalCompareFunction(CheckForSize);
			selectorQueue = new SelectorQueue(&groundColoring);
			selectorQueue->AddStartingSelecotr(used);
			t_Teleport *tele = (t_Teleport*)ability->stats;
			selectorQueue->AddNextSelector(false, {-1, -1}, tele->secondRange, 0, true, false);
			break ;
		}
		case HEALTH_TRANSFER:
		{
			t_HealthTransfer *stats = (t_HealthTransfer*)ability->stats;
			selectorQueue = new SelectorQueue(&groundColoring);
			selectorQueue->AddNextSelectorWithTarget(true, character->position, ability->range, 0, false, false, true, stats->enemy);
			selectorQueue->AddNextSelectorWithTarget(true, {-1, -1}, stats->secondRange, 0, false, false, true, stats->enemy, CheckForMaxHealth);
			break ;
		}
		case SKELE_MELEE:
			selector = new Selector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case SKELE_LUNGE:
			axeJumpSelector = new AxeJumpSelector(pos, ability->range, &groundColoring);
			break ;
		case BIG_THUG_STRIKE:
			selector = new Selector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case THUG_STRIKE:
			selector = new Selector(character->position, ability->range, 0, &groundColoring, true);
			break ;
		case BIG_THUG_INSPIRE:
			ActivateAbility(ability, character);
			break ;
	}
}

void Abilities::SetAbility(t_Ability *ability, Character *character)
{
	gameState.updateObjs.turnOrder->ResetClicks();
	if (inMotion)
		return ;
	Clear();
	Abilities::ability = ability;
	Abilities::character = character;
	active = true;
	SetSelector(ability, character);
}

void Abilities::SetAiAbilityToAction(t_Ability *ability, Character *character, SDL_Point target, std::vector<SDL_Point> &adds)
{
	gameState.updateObjs.turnOrder->ResetClicks();
	Clear();
	active = true;
	character->moves -= ability->cost;
	Abilities::target = gameState.battle.ground->map[target.y][target.x].character;
	targetPoint = target;
	Abilities::character = character;
	Abilities::ability = ability;
	for (int i = 0; i < adds.size(); i++)
		targPoints.push_back(adds[i]);
	ActivateAbility(ability, character);
}

void Abilities::ActivateAbility(t_Ability *ability, Character *character)
{
	inMotion = true;
	if (character->ally)
		gameState.updateObjs.UI->UseEnergy(ability->cost);
	character->stats.fatigue += ability->fatigue;
	switch (ability->type)
	{
		case DAGGER_THROW:
			animations.push_back({new DaggerThrowAnim(character, target), DAGGER_THROW});
			break ;
		case SMOKE_BOMB:
			animations.push_back({new SmokeBombAnim(character, targetPoint), SMOKE_BOMB});
			break ;
		case DAGGER_SLASH:
			animations.push_back({new DaggerSlashAnim(character, targetPoint), DAGGER_SLASH});
			break ;
		case FLAME_PORT:
			animations.push_back({new FlamePort(character, targetPoint), FLAME_PORT});
			break ;
		case FLAME_SLASH:
			animations.push_back({new FlameSlash(character, targetPoint), FLAME_SLASH});
			break ;
		case FLAME_BLAST:
			animations.push_back({new FlameBlast(character, targPoints, ability), FLAME_BLAST});
			break ;
		case INCINERATE:
			if (targPoints.size() != 0)
				animations.push_back({new Incinerate(character, targPoints), INCINERATE});
			break ;
		case LION_SMACK:
			animations.push_back({new LionSmack(character, targetPoint), LION_SMACK});
			break ;
		case PHANTOM_KNIGHT:
			SetScreenShake(300, 8);
			animations.push_back({new PhantomAnim({targetPoint}), PHANTOM_KNIGHT});
			break ;
		case ROTATE:
			animations.push_back({new Rotate(character, target), ROTATE});
			break ;
		case HAMMER_SMACK:
			animations.push_back({new HammerSmack(character, target), HAMMER_SMACK});
			break ;
		case THROW_TOOLBOX:
			animations.push_back({new ToolThrowAnim(character, targetPoint), THROW_TOOLBOX});
			break ;
		case SUPPLY_ALLY:
			animations.push_back({new SupplyAlly(character, target), SUPPLY_ALLY});
			break ;
		case PICK_UP_TOOLS:
			animations.push_back({new PickUpTools(character, targetPoint), PICK_UP_TOOLS});
			break ;
		case SUPPLY:
			animations.push_back({new Supply(character, targetPoint), SUPPLY});
			break ;
		case GENERIC_TOOL_THROW:
			animations.push_back({new GenericToolThrow(character, targPoints[0], targPoints[1]), GENERIC_TOOL_THROW});
			break ;
		case SMITH_BUFF:
			animations.push_back({new SmithBuff(character, target), SMITH_BUFF});
			break ;
		case LIGHTNING_BOLT:
			animations.push_back({new MageAttack(character), LIGHTNING_BOLT});
			break ;
		case ROCK_FALL:
			animations.push_back({new MageAttack(character), ROCK_FALL});
			break ;
		case HOST_EYES:
			animations.push_back({new HostEyesAnim(character, target), HOST_EYES});
			break ;
		case AXE_SLASH:
			animations.push_back({new AxeSlash(character, target), AXE_SLASH});
			break ;
		case AXE_JUMP:
			animations.push_back({new AxeJumpAnim(character, target, targetPoint), AXE_JUMP});
			break ;
		case TOXIC_BLADE:
			animations.push_back({new ToxinBuff(character), TOXIC_BLADE});
			break ;
		case RAIDER_BLOCK:
			animations.push_back({new RaiderBlock(character), RAIDER_BLOCK});
			break ;
		case NAIL_BOMB:
			animations.push_back({new NailBomb(character, targPoints[0], ability), NAIL_BOMB});
			break ;
		case ACID_BOMB:
			animations.push_back({new AcidBombAnim(character, targPoints[0], ability), ACID_BOMB});
			break ;
		case SLOW_BOMB:
			animations.push_back({new SlowBomb(character, targPoints[0], ability), SLOW_BOMB});
			break ;
		case GO_FOR_THE_HEAD:
			animations.push_back({new GoForTheHead(character, target), GO_FOR_THE_HEAD});
			break ;
		case FLAIL_STRIKE:
			animations.push_back({new KnightAttack(character, target), FLAIL_STRIKE});
			break ;
		case SHILED_BASH:
			animations.push_back({new ShieldBash(character, target), SHILED_BASH});
			break ;
		case CONTROL_ZONE:
			animations.push_back({new ControlZone(character), CONTROL_ZONE});
			break ;
		case ACID_RAIN:
			animations.push_back({new AcidRain(character, target->position, 1), ACID_RAIN});
			break ;
		case TELEPORT:
			animations.push_back({new TeleStart(character, targPoints[0]), TELEPORT});
			break ;
		case HEALTH_TRANSFER:
		{
			Character *used = gameState.battle.ground->map[targPoints[0].y][targPoints[0].x].character;
			animations.push_back({new HeartBeat(character, used), HEALTH_TRANSFER});
			break ;
		}
		case SKELE_MELEE:
			animations.push_back({new SkeleMeleeAnim(character, target), SKELE_MELEE});
			break ;
		case SKELE_LUNGE:
			animations.push_back({new SkeleLunge(character, target, targPoints[0]), SKELE_LUNGE});
			break ;
		case BIG_THUG_STRIKE:
			animations.push_back({new BigThugStrike(character, target), BIG_THUG_STRIKE});
			break ;
		case THUG_STRIKE:
			animations.push_back({new ThugStrike(character, target), THUG_STRIKE});
			break ;
		case BIG_THUG_INSPIRE:
			animations.push_back({new BigThugInspire(character), BIG_THUG_INSPIRE});
			break ;
	}
}

void Abilities::SelectorWithCharacters()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	Character *ret = selector->Update();
	if (ret != NULL)
	{
		if (gameState.keys.click == RELEASE_CLICK)
		{
			target = ret;
			targetPoint = ret->position;
			ActivateAbility(ability, character);
			ClearMap();
		}
	}
}

void Abilities::SelectorWithSquares()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	SDL_Point ret = tileSelector->Update();
	if (ret.x != (-1) && ret.y != (-1))
	{
		Character *blockChar = gameState.battle.ground->map[ret.y][ret.x].character;
		if (gameState.keys.click == RELEASE_CLICK)
		{
			target = blockChar;
			targetPoint = ret;
			ActivateAbility(ability, character);
			ClearMap();
		}
	}
}

void Abilities::SelectorForAxeJump()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	axeJumpSelector->Update();
	if (axeJumpSelector->done)
	{
		target = axeJumpSelector->GetTargetEnemy();
		targetPoint = axeJumpSelector->GetTargetLandingPos();
		ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::UpdatePhantomSelector()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	phantSelector->Update();
	if (phantSelector->done)
	{
		targPoints.clear();
		targPoints = phantSelector->GetTargets();
		if (targPoints.size() != 0)
			ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::MultiSelectorWithCharacter()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	multiSelector->Update();
	if (!multiSelector->done)
		return ;
	targPoints.clear();
	targPoints = multiSelector->GetPositions();
	ActivateAbility(ability, character);
	ClearMap();
}

void Abilities::SelectorQueueUpdate()
{
	selectorQueue->Update();
	if (selectorQueue->done)
	{
		targPoints.clear();
		targPoints = selectorQueue->GetTargets();
		if (targPoints.size() != 0)
			ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::AllSelectorUpdate()
{
	gameState.updateObjs.UI->ShowEnergy(ability->cost);
	allSelector->Update();
	if (allSelector->done)
	{
		targPoints.clear();
		targPoints = allSelector->getTargets();
		if (targPoints.size() != 0)
			ActivateAbility(ability, character);
		ClearMap();
	}
}

void Abilities::UpdateSelector()
{
	if (selector != NULL)
		SelectorWithCharacters();
	else if (tileSelector != NULL)
		SelectorWithSquares();
	else if (multiSelector != NULL)
		MultiSelectorWithCharacter();
	else if (allSelector != NULL)
		AllSelectorUpdate();
	else if (phantSelector != NULL)
		UpdatePhantomSelector();
	else if (axeJumpSelector != NULL)
		SelectorForAxeJump();
	else if (selectorQueue != NULL)
		SelectorQueueUpdate();
}

void Abilities::UpdateMisses()
{
	for (int i = 0; i < misses.size(); i++)
	{
		int ret = misses[i]->Update();
		if (ret == (-1))
		{
			delete misses[i];
			misses.erase(misses.begin() + i);
			i = (i == 0) ? 0 : i - 1;
		}
	}
}

void Abilities::Upadte()
{
	oAttack.Update();
	aoAttack.Update();
	UpdateSelector();
	AnimationUpdater();
	ObjectUpdater();
	UpdateMisses();
	effectUpdater.Update();
	damager.Update();
	groundColoring.Update();
	if (gameState.keys.rightClick == INITIAL_CLICK)
		ClearMap();
	AbilityStatus();
}

void Abilities::HandleDamageVector(std::vector<t_HitReturn> &ret)
{
	for (int i = 0; i < ret.size(); i++)
	{
		if (!ret[i].missing)
		{
			std::vector<SDL_Point> add = {ret[i].target};
			damager.AddDamage(ability, character, add);
		}
		else
		{
			Character *target = gameState.battle.ground->map[ret[i].target.y][ret[i].target.x].character;
			CreateTextSnippet(character, target, "MISS", 1000, Color(32, 153, 186));
			PlaySound(gameState.audio.whiff, Channels::WHIFF, 0);
		}
	}
}

void Abilities::AnimationUpdater()
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (CheckGenericAnimations(animations[i], i))
			continue ;
		switch (character->cSing)
		{
			case THIEF:
				UpdateThiefAnimation(animations[i], i);
				break ;
			case PYRO:
				UpdatePyroAnimation(animations[i], i);
				break ;
			case LION:
				UpdateLionAnimation(animations[i], i);
				break ;
			case SMITH:
				UpdateSmithAnimation(animations[i], i);
				break ;
			case MAGE:
				UpdateMageAnimation(animations[i], i);
				break ;
			case RAIDER:
				UpdateRaiderAnimation(animations[i], i);
				break ;
			case ALCHEMIST:
				UpdateAlchemistAnimation(animations[i], i);
				break ;
			case KNIGHT:
				UpdateKnightAnimation(animations[i], i);
				break ;
			case WITCH:
				UpdateWitchAnimation(animations[i], i);
				break ;
			case SKELE:
				UpdateEnemyAnimationOne(animations[i], i);
				break ;
			case BIG_THUG:
				UpdateEnemyAnimationOne(animations[i], i);
				break ;
			case THUG:
				UpdateEnemyAnimationOne(animations[i], i);
				break ;
		}
	}
}

void Abilities::CreateDamage(bool sound)
{
	std::vector<SDL_Point> used = {targetPoint};
	damager.AddDamage(ability, character, used, sound);
}

void Abilities::ObjectUpdater()
{
	for (int i = 0; i < objects.size(); i++)
	{
		switch (character->cSing)
		{
			case THIEF:
				UpdateThiefObject(objects[i], i);
				break ;
			case MAGE:
				UpdateMageObject(objects[i], i);
				break ;
			case KNIGHT:
				UpdateKnightObjects(objects[i], i);
				break ;
			case WITCH:
				UpdateWitchObjects(objects[i], i);
				break ;
		}
	}
}

void Abilities::AbilityStatus()
{
	if (!inMotion)
		return ;
	if (objects.size() == 0 && animations.size() == 0)
		Clear();
}

void Abilities::CreateOpportunityDamage(SDL_Point damager, Character *target)
{
	Abilities::damager.AddOpportunityDamage(damager, target);
}

void Abilities::CreateBleedDamage(Character *target, int amount)
{
	damager.AddBleedDamage(target, amount);
}

void Abilities::CreatePoisonDamage(Character *target, int amount)
{
	damager.AddPoisonDamage(target, amount);
}

t_Animation *Abilities::GetAnimation(int type)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i].type == type)
			return (&animations[i]);
	}
	return (NULL);
}

void Abilities::ClearMap()
{
	if (selector != NULL)
		delete selector;
	selector = NULL;
	if (tileSelector != NULL)
		delete tileSelector;
	tileSelector = NULL;
	if (multiSelector != NULL)
		delete multiSelector;
	multiSelector = NULL;
	if (allSelector != NULL)
		delete allSelector;
	allSelector = NULL;
	if (phantSelector != NULL)
		delete phantSelector;
	phantSelector = NULL;
	if (axeJumpSelector != NULL)
		delete axeJumpSelector;
	axeJumpSelector = NULL;
	if (selectorQueue != NULL)
		delete selectorQueue;
	selectorQueue = NULL;
	groundColoring.ClearMap();
	groundColoring.active = false;
	if (!inMotion)
		active = false;
	marking = false;
}

void Abilities::Clear()
{
	ability = NULL;
	character = NULL;
	if (selector != NULL)
		delete selector;
	selector = NULL;
	if (tileSelector != NULL)
		delete tileSelector;
	tileSelector = NULL;
	if (multiSelector != NULL)
		delete multiSelector;
	multiSelector = NULL;
	if (allSelector != NULL)
		delete allSelector;
	allSelector = NULL;
	if (phantSelector != NULL)
		delete phantSelector;
	phantSelector = NULL;
	if (axeJumpSelector != NULL)
		delete axeJumpSelector;
	axeJumpSelector = NULL;
	if (selectorQueue != NULL)
		delete selectorQueue;
	selectorQueue = NULL;
	active = false;
	target = NULL;
	targetPoint = {-1, -1};
	targPoints.clear();
	groundColoring.ClearMap();
	groundColoring.active = false;
	inMotion = false;
	marking = false;
}

void Abilities::Destroy()
{
	Clear();
	oAttack.Destroy();
	aoAttack.Destroy();
	damager.Destroy();
	effectUpdater.Clear();
	for (int i = 0; i < misses.size(); i++)
		delete misses[i];
	for (int i = 0; i < animations.size(); i++)
	{
		AbBase *used = (AbBase*)animations[i].animation;
		delete used;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		AbBase *used = (AbBase*)objects[i].object;
		delete used;
	}
}
