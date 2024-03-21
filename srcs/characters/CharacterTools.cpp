
#include "../../hdr/global.h"

static void AssingDefaultPyroStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_FlamePortStats));
	t_FlamePortStats *stat0 = (t_FlamePortStats*)stats[0].stats;
	stat0->selfDamagePrecent = 10;
	stat0->range = 15;
	stats[1].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	t_AttackWithDebuff *stat1 = (t_AttackWithDebuff*)stats[1].stats;
	stat1->critChance = 4;
	stat1->damage = 100;
	stat1->debuffChance = 80;
	stats[2].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	stat1 = (t_AttackWithDebuff*)stats[2].stats;
	stat1->critChance = 2;
	stat1->damage = 60;
	stat1->debuffChance = 75;
	stats[3].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat2 = (t_AttackStruct*)stats[3].stats;
	stat2->critChance = 4;
	stat2->damage = 130;
}

static void AssingDefaultThiefStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackWithStatus));
	t_AttackWithStatus *stat0 = (t_AttackWithStatus*)stats[0].stats;
	stat0->critChance = 5;
	stat0->damage = 90;
	stat0->statusChance = 80;
	stat0->stacks = 2;
	stat0->statusActive = true;
	stats[1].stats = (void*)malloc(sizeof(t_LastingEffect));
	t_LastingEffect *stat1 = (t_LastingEffect*)stats[1].stats;
	stat1->turns = 2;
	stats[2].stats = (void*)malloc(sizeof(t_AttackWithStatus));
	stat0 = (t_AttackWithStatus*)stats[2].stats;
	stat0->critChance = 5;
	stat0->damage = 100;
	stat0->statusChance = 80;
	stat0->stacks = 4;
	stat0->statusActive = true;
}

static void AssignDefaultLionStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	t_AttackWithDebuff *stat0 = (t_AttackWithDebuff*)stats[0].stats;
	stat0->critChance = 4;
	stat0->damage = 70;
	stat0->debuffChance = 30;
	stats[1].stats = (void*)malloc(sizeof(t_PhantomKnight));
	t_PhantomKnight *stat1 = (t_PhantomKnight*)stats[1].stats;
	stat1->hits = 20;
	stat1->armor = 10;
	stat1->opportunity = true;
	stat1->turns = 1;
	stats[2].stats = (void*)malloc(sizeof(int));
	int *stat2 = (int*)stats[2].stats;
	*stat2 = 2;
}

static void AssignDefaultSmithStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 3;
	stat0->damage = 100;
	stats[1].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	t_AttackWithDebuff *stat2 = (t_AttackWithDebuff*)stats[1].stats;
	stat2->critChance = 2;
	stat2->damage = 100;
	stat2->debuffChance = 85;
	stats[2].stats = (void*)malloc(sizeof(t_BuffAndDebuff));
	t_BuffAndDebuff *stat1 = (t_BuffAndDebuff*)stats[2].stats;
	stat1->buffChance = 200;
	stat1->debuffChance = 150;
	stat1->turns = 2;
	stat1->amount = 10;
}

static void AssignDefaultMageAbilities(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 4;
	stat0->damage = 100;
	stats[1].stats = (void*)malloc(sizeof(t_AttackStruct));
	stat0 = (t_AttackStruct*)stats[1].stats;
	stat0->critChance = 2;
	stat0->damage = 75;
	stats[2].stats = (void*)malloc(sizeof(t_HostEyes));
	t_HostEyes *stat1 = (t_HostEyes*)stats[2].stats;
	stat1->enemyChance = 80;
	stat1->hostRange = 6;
}

static void AssignDefaultRaiderAbilities(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 4;
	stat0->damage = 100;
	stats[1].stats = (void*)malloc(sizeof(t_AttackStruct));
	stat0 = (t_AttackStruct*)stats[1].stats;
	stat0->critChance = 4;
	stat0->damage = 100;
	stats[2].stats = (void*)malloc(sizeof(t_ToxicBlade));
	t_ToxicBlade *stat1 = (t_ToxicBlade*)stats[2].stats;
	stat1->hits = 2;
	stat1->stacks = 6;
	stat1->turns = 0;
	stat1->hitChance = 80;
	stats[3].stats = (void*)malloc(sizeof(t_RaiderBlock));
	t_RaiderBlock *stat2 = (t_RaiderBlock*)stats[3].stats;
	stat2->precentage = 15;
}

static void AssignDefaultAlchemistAbilities(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_DamageBomb));
	t_DamageBomb *stat0 = (t_DamageBomb*)stats[0].stats;
	stat0->additionalBlocks = false;
	stat0->damage = 100;
	stat0->critChance = 1;
	stat0->stacks = 3;
	stat0->statusChance = 75;
	stat0->version = 7;
	stats[1].stats = (void*)malloc(sizeof(t_DamageBomb));
	stat0 = (t_DamageBomb*)stats[1].stats;
	stat0->additionalBlocks = false;
	stat0->damage = 70;
	stat0->critChance = 1;
	stat0->stacks = 10;
	stat0->statusChance = 85;
	stat0->version = 8;
	stats[2].stats = (void*)malloc(sizeof(t_SlowBomb));
	t_SlowBomb *stat1 = (t_SlowBomb*)stats[2].stats;
	stat1->additionalBlocks = false;
	stat1->chance = 95;
	stat1->slowDownVersion = 0;
	stat1->version = 8;
}

static void AssingDefaultKnightAbilities(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackWithStatus));
	t_AttackWithStatus *stat0 = (t_AttackWithStatus*)stats[0].stats;
	stat0->critChance = 3;
	stat0->damage = 100;
	stat0->stacks = 2;
	stat0->statusActive = true;
	stat0->statusChance = 80;
	stats[1].stats = (void*)malloc(sizeof(t_ShieldBash));
	t_ShieldBash *stat1 = (t_ShieldBash*)stats[1].stats;
	stat1->critChance = 1;
	stat1->damage = 33;
	stat1->stunChance = 100;
	stat1->moveChance = 80;
	stats[2].stats = (void*)malloc(sizeof(t_ControlZone));
	t_ControlZone *stat2 = (t_ControlZone*)stats[2].stats;
	stat2->controlArea = false;
	stat2->endTurn = true;
}

static void AssingDefaultWitchAbilities(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AcidRainDamage));
	t_AcidRainDamage *stat0 = (t_AcidRainDamage*)stats[0].stats;
	stat0->chance = 100;
	stat0->stacks = 10;
	stats[1].stats = (void*)malloc(sizeof(t_Teleport));
	t_Teleport *stat1 = (t_Teleport*)stats[1].stats;
	stat1->maxSize = 5;
	stat1->secondRange = 13;
	stats[2].stats = (void*)malloc(sizeof(t_HealthTransfer));
	t_HealthTransfer *stat2 = (t_HealthTransfer*)stats[2].stats;
	stat2->amount = 20;
	stat2->secondRange = 10;
	stat2->minNumber = 18;
	stat2->enemy = false;
}

static void AssignDefaultSkeleStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 2;
	stat0->damage = 100;
	stats[1].stats = (void*)malloc(sizeof(t_AttackStruct));
	stat0 = (t_AttackStruct*)stats[1].stats;
	stat0->critChance = 2;
	stat0->damage = 100;
}

static void AssignDefaultBigThugStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 1;
	stat0->damage = 140;
}

static void AssignDefaultThugStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 4;
	stat0->damage = 100;
}

void Character::AssignAbilities()
{
	switch (cSing)
	{
		case THIEF:
			stats = {18, 24, 9, 70, 70, 35, 35, 90, 0, 3, 1};
			abilities = {{DAGGER_THROW, 3, 15, 11, 80, StatStructs::ATTACK_WITH_STATUS, StatusSigns::BLEED, 90, 5, false, true, NULL},
						{SMOKE_BOMB, 4, 20, 7, 200, StatStructs::LASTING_EFFECT, -1, 0, 0, true, true, NULL},
						{DAGGER_SLASH, 2, 10, 2, 80, StatStructs::ATTACK_WITH_STATUS, StatusSigns::BLEED, 100, 5, true, true, NULL}};
			AssingDefaultThiefStats(abilities);
			break ;
		case SKELE:
			stats = {22, 29, 3, 50, 50, 25, 25, 130, 0, 3, 1};
			abilities = {{SKELE_MELEE, 3, 15, 2, 80, StatStructs::ATTACK_STRUCT, -1, 100, 2, true, true, NULL},
						{SKELE_LUNGE, 4, 20, 8, 80, StatStructs::ATTACK_STRUCT, -1, 100, 2, false, true, NULL}};
			AssignDefaultSkeleStats(abilities);
			break ;
		case PYRO:
			stats = {29, 34, 5, 55, 55, 35, 35, 90, 0, 2, 1};
			abilities = {{FLAME_PORT, 3, 10, 14, 200, StatStructs::FLAME_PORT, -1, 0, 0, true, false, NULL},
						{FLAME_SLASH, 3, 15, 2, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::BURN, 100, 4, true, true, NULL},
						{FLAME_BLAST, 4, 20, 5, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::BURN, 60, 2, true, true, NULL},
						{INCINERATE, 5, 30, 6, 90, StatStructs::ATTACK_STRUCT, -1, 175, 4, true, true, NULL}};
			AssingDefaultPyroStats(abilities);
			break ;
		case LION:
			stats = {16, 20, 2, 100, 100, 160, 160, 80, 0, 8, 1};
			abilities = {{LION_SMACK, 3, 12, 2, 95, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::STUN, 65, 1, true, true, NULL},
						{PHANTOM_KNIGHT, 5, 20, 8, 200, StatStructs::PHANTOM_KNIGHT, -1, 0, 0, true, false, NULL},
						{ROTATE, 2, 10, 2, 200, StatStructs::TIERS, -1, 0, 0, true, true, NULL}};
			AssignDefaultLionStats(abilities);
			break ;
		case SMITH:
			stats = {20, 25, 2, 70, 70, 35, 35, 70, 0, 4, 1};
			abilities = {{HAMMER_SMACK, 3, 15, 2, 80, StatStructs::ATTACK_STRUCT, -1, 100, 1, true, true, NULL},
						{GO_FOR_THE_HEAD, 5, 30, 2, 100, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::STUN, 120, 2, true, true, NULL},
						{SMITH_BUFF, 2, 10, 9, 200, StatStructs::BUFF_AND_DEBUFF, StatusSigns::BUFF, 0, 0, true, false, NULL}};
			AssignDefaultSmithStats(abilities);
			break ;
		case MAGE:
			stats = {24, 30, 3, 40, 40, 20, 20, 95, 0, 1, 1};
			abilities = {{LIGHTNING_BOLT, 3, 15, 12, 80, StatStructs::ATTACK_STRUCT, (-1), 100, 3, false, true, NULL},
						{ROCK_FALL, 5, 20, 10, 80, StatStructs::ATTACK_STRUCT, (-1), 55, 2, false, true, NULL},
						{HOST_EYES, 2, 10, 11, 200, StatStructs::HOST_EYES, StatusSigns::HOST, 0, 0, false, false, NULL}};
			AssignDefaultMageAbilities(abilities);
			break ;
		case RAIDER:
			stats = {30, 36, 4, 110, 110, 50, 50, 100, 0, 4, 1};
			abilities = {{AXE_SLASH, 3, 15, 2, 80, StatStructs::ATTACK_STRUCT, (-1), 100, 4, true, true, NULL},
						{AXE_JUMP, 3, 15, 10, 80, StatStructs::ATTACK_STRUCT, (-1), 100, 4, true, true, NULL},
						{TOXIC_BLADE, 2, 10, 0, 200, StatStructs::TOXIC_BLADE, (-1), 0, 0, true, false, NULL},
						{RAIDER_BLOCK, 2, 15, 0, 200, StatStructs::RAIDER_BLOCK, (-1), 0, 0, true, false, NULL}};
			AssignDefaultRaiderAbilities(abilities);
			break ;
		case ALCHEMIST:
			stats = {21, 25, 6, 60, 60, 30, 30, 80, 0, 3, 1};
			abilities = {{NAIL_BOMB, 4, 15, 9, 90, StatStructs::BOMB_STRUCT, (-1), 100, 2, true, true, NULL},
						{ACID_BOMB, 3, 20, 10, 90, StatStructs::BOMB_STRUCT, (-1), 70, 3, false, true, NULL},
						{SLOW_BOMB, 3, 13, 11, 200, StatStructs::SLOW_BOMB_STRUCT, (-1), 0, 0, true, true, NULL}};
			AssignDefaultAlchemistAbilities(abilities);
			break ;
		case KNIGHT:
			stats = {20, 27, 3, 80, 80, 80, 80, 90, 0, 6, 1};
			abilities = {{FLAIL_STRIKE, 3, 15, 4, 80, StatStructs::ATTACK_WITH_STATUS, StatusSigns::BLEED, 100, 3, true, true, NULL},
						{SHILED_BASH, 3, 25, 2, 80, StatStructs::SHIELD_BASH_STRUCT, (-1), 33, 2, true, true, NULL},
						{CONTROL_ZONE, 3, 25, 0, 200, StatStructs::CONTROL_ZONE_STRUCT, (-1), 0, 0, true, false, NULL}};
			AssingDefaultKnightAbilities(abilities);
			break ;
		case WITCH:
			stats = {10, 14, 8, 45, 45, 25, 25, 90, 0, 2, 1};
			abilities = {{ACID_RAIN, 3, 12, 10, 90, StatStructs::ACID_RAIN_STRUCT, (-1), 0, 0, false, true, NULL},
						{TELEPORT, 4, 16, 10, 90, StatStructs::TELEPORT, (-1), 0, 0, false, true, NULL},
						{HEALTH_TRANSFER, 2, 10, 10, 80, StatStructs::HEALTH_TRANSFER, (-1), 0, 0, true, true, NULL}};
			AssingDefaultWitchAbilities(abilities);
			break ;
		case BIG_THUG:
			stats = {26, 48, 3, 210, 210, 40, 40, 130, 0, 6, 1};
			abilities = {{BIG_THUG_STRIKE, 4, 23, 2, 70, StatStructs::ATTACK_STRUCT, (-1), 140, 1, true, true, NULL}};
			AssignDefaultBigThugStats(abilities);
			break ;
		case THUG:
			stats = {18, 27, 4, 55, 55, 40, 40, 100, 0, 2, 1};
			abilities = {{THUG_STRIKE, 3, 16, 2, 80, StatStructs::ATTACK_STRUCT, (-1), 100, 4, true, true, NULL}};
			AssignDefaultThugStats(abilities);
			break ;
		default:
			return ;
	}
}

void Character::CreateCharacterType(int skin)
{
	cSing = skin;
	switch (skin)
	{
		case THIEF:
		{
			SDL_Rect dest = {-3000, -450, 6800, 7360};
			textures.push_back(gameState.textures.thiefIdle1);
			textures.push_back(gameState.textures.thiefIdle2);
			stands.push_back(gameState.textures.stands.thiefIdle1Stand);
			stands.push_back(gameState.textures.stands.thiefIdle2Stand);
			sprite = new Sprite(gameState.textures.thiefIdle1, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.thiefIdle1Stand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case SKELE:
		{
			SDL_Rect skele = {-3000, -450, 6500, 6500};
			textures.push_back(gameState.textures.skeleIdle1);
			textures.push_back(gameState.textures.skeleIdle2);
			stands.push_back(gameState.textures.stands.skeleIdle1Stand);
			stands.push_back(gameState.textures.stands.skeleIdle2Stand);
			sprite = new Sprite(gameState.textures.skeleIdle1, skele, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.skeleIdle1Stand, skele, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case PYRO:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.pyroIdle1);
			textures.push_back(gameState.textures.chars.pyroIdle2);
			stands.push_back(gameState.textures.stands.pyroStand);
			stands.push_back(gameState.textures.stands.pyroStand);
			sprite = new Sprite(gameState.textures.chars.pyroIdle1, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.pyroStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case LION:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.lionIdle[0]);
			textures.push_back(gameState.textures.chars.lionIdle[1]);
			stands.push_back(gameState.textures.stands.lionStand);
			stands.push_back(gameState.textures.stands.lionStand);
			sprite = new Sprite(gameState.textures.chars.lionIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.lionStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case PHANTOM_LION:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.lionIdle[0]);
			textures.push_back(gameState.textures.chars.lionIdle[1]);
			stands.push_back(gameState.textures.stands.lionStand);
			stands.push_back(gameState.textures.stands.lionStand);
			sprite = new Sprite(NULL, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(NULL, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case TOOLS:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.lionIdle[0]);
			textures.push_back(gameState.textures.chars.lionIdle[1]);
			stands.push_back(gameState.textures.stands.lionStand);
			stands.push_back(gameState.textures.stands.lionStand);
			sprite = new Sprite(NULL, dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(NULL, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case SMITH:
		{
			SDL_Rect dest = {-3000, -450, 6000, 7360};
			textures.push_back(gameState.textures.chars.smithIdle[0]);
			textures.push_back(gameState.textures.chars.smithIdle[1]);
			stands.push_back(gameState.textures.stands.smithStand);
			stands.push_back(gameState.textures.stands.smithStand);
			sprite = new Sprite(gameState.textures.chars.smithIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.smithStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case MAGE:
		{
			SDL_Rect dest = {-3000, -450, 6700, 8040};
			textures.push_back(gameState.textures.chars.mageIdle[0]);
			textures.push_back(gameState.textures.chars.mageIdle[1]);
			stands.push_back(gameState.textures.stands.mageStand);
			stands.push_back(gameState.textures.stands.mageStand);
			sprite = new Sprite(gameState.textures.chars.mageIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.mageStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case RAIDER:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.raiderIdle[0]);
			textures.push_back(gameState.textures.chars.raiderIdle[1]);
			stands.push_back(gameState.textures.stands.raiderStand);
			stands.push_back(gameState.textures.stands.raiderStand);
			sprite = new Sprite(gameState.textures.chars.raiderIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.raiderStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case ALCHEMIST:
		{
			SDL_Rect dest = {-3000, -450, 6800, 7960};
			textures.push_back(gameState.textures.chars.AlchemistIdle[0]);
			textures.push_back(gameState.textures.chars.AlchemistIdle[1]);
			stands.push_back(gameState.textures.stands.pyroStand);
			stands.push_back(gameState.textures.stands.pyroStand);
			sprite = new Sprite(gameState.textures.chars.AlchemistIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.pyroStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case KNIGHT:
		{
			SDL_Rect dest = {-3000, -450, 6500, 7360};
			textures.push_back(gameState.textures.chars.knightIdle[0]);
			textures.push_back(gameState.textures.chars.knightIdle[1]);
			stands.push_back(gameState.textures.stands.knightStand);
			stands.push_back(gameState.textures.stands.knightStand);
			sprite = new Sprite(gameState.textures.chars.knightIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.knightStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case WITCH:
		{
			SDL_Rect dest = {-3000, -450, 6500, 7360};
			textures.push_back(gameState.textures.chars.witchIdle[0]);
			textures.push_back(gameState.textures.chars.witchIdle[1]);
			stands.push_back(gameState.textures.stands.witchStand);
			stands.push_back(gameState.textures.stands.witchStand);
			sprite = new Sprite(gameState.textures.chars.witchIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.witchStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
		case BIG_THUG:
		{
			SDL_Rect dest = {-3000, -450, 6800, 8160};
			textures.push_back(gameState.textures.chars.bigThugIdle[0]);
			textures.push_back(gameState.textures.chars.bigThugIdle[1]);
			stands.push_back(gameState.textures.stands.bigThugStand);
			stands.push_back(gameState.textures.stands.bigThugStand);
			sprite = new Sprite(gameState.textures.chars.bigThugIdle[0], dest, NULL, NULL, 0, FLIP_HORIZONTAL);
			stand = new Sprite(gameState.textures.stands.bigThugStand, dest, NULL, NULL, 0, FLIP_HORIZONTAL);
			break ;
		}
		case THUG:
		{
			SDL_Rect dest = {-3000, -450, 6500, 7560};
			textures.push_back(gameState.textures.chars.thugIdle[0]);
			textures.push_back(gameState.textures.chars.thugIdle[1]);
			stands.push_back(gameState.textures.stands.thugStand);
			stands.push_back(gameState.textures.stands.thugStand);
			sprite = new Sprite(gameState.textures.chars.thugIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
			stand = new Sprite(gameState.textures.stands.thugStand, dest, NULL, NULL, 0, FLIP_NONE);
			break ;
		}
	}
}
