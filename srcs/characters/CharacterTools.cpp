
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
	stats[0].stats = (void*)malloc(sizeof(t_AttackStruct));
	t_AttackStruct *stat0 = (t_AttackStruct*)stats[0].stats;
	stat0->critChance = 5;
	stat0->damage = 90;
	stats[1].stats = (void*)malloc(sizeof(t_LastingEffect));
	t_LastingEffect *stat1 = (t_LastingEffect*)stats[1].stats;
	stat1->turns = 2;
	stats[2].stats = (void*)malloc(sizeof(t_AttackStruct));
	stat0 = (t_AttackStruct*)stats[2].stats;
	stat0->critChance = 5;
	stat0->damage = 100;
}

static void AssignDefaultLionStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	t_AttackWithDebuff *stat0 = (t_AttackWithDebuff*)stats[0].stats;
	stat0->critChance = 4;
	stat0->damage = 80;
	stat0->debuffChance = 35;
	stats[1].stats = (void*)malloc(sizeof(t_PhantomKnight));
	t_PhantomKnight *stat1 = (t_PhantomKnight*)stats[1].stats;
	stat1->hits = 1;
	stat1->opportunity = false;
	stat1->turns = 1;
	stats[2].stats = (void*)malloc(sizeof(int));
	int *stat2 = (int*)stats[2].stats;
	*stat2 = 1;
}

static void AssignDefaultSmithStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_AttackWithDebuff));
	t_AttackWithDebuff *stat0 = (t_AttackWithDebuff*)stats[0].stats;
	stat0->critChance = 1;
	stat0->damage = 90;
	stat0->debuffChance = 40;
	stats[1].stats = (void*)malloc(sizeof(t_BuffAndDebuff));
	t_BuffAndDebuff *stat1 = (t_BuffAndDebuff*)stats[1].stats;
	stat1->buffChance = 200;
	stat1->debuffChance = 200;
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
	stat1->hostRange = 5;
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
	stat1->stacks = 10;
	stat1->turns = 0;
	stat1->hitChance = 80;
	stats[3].stats = (void*)malloc(sizeof(t_RaiderBlock));
	t_RaiderBlock *stat2 = (t_RaiderBlock*)stats[3].stats;
	stat2->precentage = 15;
}

void Character::AssignAbilities()
{
	switch (cSing)
	{
		case THIEF:
			abilities = {{DAGGER_THROW, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, -1, NULL},
						{SMOKE_BOMB, 0, 10, 0, 200, StatStructs::LASTING_EFFECT, -1, NULL},
						{DAGGER_SLASH, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, -1, NULL}};
			AssingDefaultThiefStats(abilities);
			break ;
		case SKELE:
			break ;
		case PYRO:
			abilities = {{FLAME_PORT, 0, 10, 0, 200, StatStructs::FLAME_PORT, -1, NULL},
						{FLAME_SLASH, 0, 10, 0, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::BURN, NULL},
						{FLAME_BLAST, 0, 10, 0, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::BURN, NULL},
						{INCINERATE, 0, 10, 0, 90, StatStructs::ATTACK_STRUCT, -1, NULL}};
			AssingDefaultPyroStats(abilities);
			break ;
		case LION:
			abilities = {{LION_SMACK, 0, 10, 0, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::STUN, NULL},
						{PHANTOM_KNIGHT, 0, 10, 0, 200, StatStructs::PHANTOM_KNIGHT, -1, NULL},
						{ROTATE, 0, 10, 0, 200, StatStructs::TIERS, -1, NULL}};
			AssignDefaultLionStats(abilities);
			break ;
		case SMITH:
			abilities = {{HAMMER_SMACK, 0, 10, 0, 80, StatStructs::ATTACK_AND_DEBUFF, StatusSigns::STUN, NULL},
						{SMITH_BUFF, 0, 10, 0, 200, StatStructs::BUFF_AND_DEBUFF, StatusSigns::BUFF, NULL}};
			AssignDefaultSmithStats(abilities);
			break ;
		case MAGE:
			abilities = {{LIGHTNING_BOLT, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, (-1), NULL},
						{ROCK_FALL, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, (-1), NULL},
						{HOST_EYES, 0, 10, 0, 200, StatStructs::HOST_EYES, StatusSigns::HOST, NULL}};
			AssignDefaultMageAbilities(abilities);
			break ;
		case RAIDER:
			abilities = {{AXE_SLASH, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, (-1), NULL},
						{AXE_JUMP, 0, 10, 0, 80, StatStructs::ATTACK_STRUCT, (-1), NULL},
						{TOXIC_BLADE, 0, 10, 0, 200, StatStructs::TOXIC_BLADE, (-1), NULL},
						{RAIDER_BLOCK, 0, 10, 0, 200, StatStructs::RAIDER_BLOCK, (-1), NULL}};
			AssignDefaultRaiderAbilities(abilities);
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
			SDL_Rect dest = {-3000, -450, 5450, 7150};
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
	}
}
