
#include "../../hdr/global.h"

static void AssingDefaultPyroStats(std::vector<t_Ability> &stats)
{
	stats[0].stats = (void*)malloc(sizeof(t_FlamePortStats));
	t_FlamePortStats *stat0 = (t_FlamePortStats*)stats[0].stats;
	stat0->selfDamagePrecent = 10;
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
	stat1->turns = 3;
	stats[2].stats = (void*)malloc(sizeof(t_AttackStruct));
	stat0 = (t_AttackStruct*)stats[2].stats;
	stat0->critChance = 5;
	stat0->damage = 100;
}

void Character::AssignAbilities()
{
	switch (cSing)
	{
		case THIEF:
			abilities = {{DAGGER_THROW, 0, 80, StatStructs::ATTACK_STRUCT, NULL},
						{SMOKE_BOMB, 0, 200, StatStructs::LASTING_EFFECT, NULL},
						{DAGGER_SLASH, 0, 80, StatStructs::ATTACK_STRUCT, NULL}};
			AssingDefaultThiefStats(abilities);
			break ;
		case SKELE:
			break ;
		case PYRO:
			abilities = {{FLAME_PORT, 0, 200, StatStructs::FLAME_PORT, NULL},
						{FLAME_SLASH, 0, 80, StatStructs::ATTACK_AND_DEBUFF, NULL},
						{FLAME_BLAST, 0, 80, StatStructs::ATTACK_AND_DEBUFF, NULL},
						{INCINERATE, 0, 90, StatStructs::ATTACK_STRUCT, NULL}};
			AssingDefaultPyroStats(abilities);
			break ;
	}
}

void Character::CreateCharacterType(int skin)
{
	cSing = skin;
	switch (skin)
	{
		case THIEF:
		{
			SDL_Rect dest = {-3000, -450, 5800, 7500};
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
	}
}
