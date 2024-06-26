
#ifndef STAT_STRUCTS_H
# define STAT_STRUCTS_H

namespace StatStructs
{
	enum
	{
		ATTACK_AND_DEBUFF,
		ATTACK_STRUCT,
		LASTING_EFFECT,
		FLAME_PORT,
		PHANTOM_KNIGHT,
		TIERS,
		THROWABLE,
		SUPPLY,
		BUFF_AND_DEBUFF,
		HOST_EYES,
		TOXIC_BLADE,
		RAIDER_BLOCK,
		BOMB_STRUCT,
		SLOW_BOMB_STRUCT,
		ATTACK_WITH_STATUS,
		SHIELD_BASH_STRUCT,
		CONTROL_ZONE_STRUCT,
		ACID_RAIN_STRUCT,
		TELEPORT,
		HEALTH_TRANSFER,
		BUFF_STRUCT
	};
};

namespace BuffTypes
{
	enum
	{
		ACCURACY,
		PROTECTION,
		OPPORTUNITY_ACCURACY
	};
};

typedef struct s_ToxicBlade
{
	int hits;
	int stacks;
	int turns;
	int hitChance;
}				t_ToxicBlade;

typedef struct s_PointDist
{
	SDL_Point pos;
	int distance;
	int closest;
}				t_PointDist;

typedef struct s_Teleport
{
	int secondRange;
	int maxSize;
}				t_Teleport;

typedef struct s_HealthTransfer
{
	int secondRange;
	int amount;
	int minNumber;
	bool enemy;
}				t_HealthTransfer;

typedef struct s_AcidRainDamage
{
	int stacks;
	int chance;
}				t_AcidRainDamage;

typedef struct s_ControlZone
{
	bool endTurn;
	bool controlArea;
}				t_ControlZone;

typedef struct s_ShieldBash
{
	int damage;
	int critChance;
	int stunChance;
	int moveChance;
}				t_ShieldBash;

typedef struct s_RaiderBlock
{
	int precentage;
}				t_RaiderBlock;

typedef struct s_HostEyes
{
	int enemyChance;
	int hostRange;
}				t_HostEyes;

typedef struct s_Supply
{
	int amount;
}				t_Supply;

typedef struct s_BuffAndDebuff
{
	int buffChance;
	int debuffChance;
	int turns;
	int amount;
}				t_BuffAndDebuff;

typedef struct s_Throwable
{
	int range;
}				t_Throwable;

typedef struct s_BuffDebuff
{
	int type;
	int turns;
	int amount;
	bool atEnd;
	int id;
}				t_BuffDebuff;

typedef struct s_ToxicStat
{
	int stacks;
	int turns;
}				t_ToxicStat;

typedef struct s_DamageBomb
{
	int damage;
	int critChance;
	int version;
	bool additionalBlocks;
	int stacks;
	int statusChance;
}				t_DamageBomb;

typedef struct s_SlowBomb
{
	int version;
	bool additionalBlocks;
	int chance;
	int slowDownVersion;
}				t_SlowBomb;

typedef struct s_StatusEffects
{
	std::vector<int> burns;
	std::vector<t_BuffDebuff> buffs;
	std::vector<t_BuffDebuff> deBuffs;
	std::vector<t_ToxicStat> toxicBlade;
	std::vector<SDL_Point> poison;
	std::vector<SDL_Point> bleed;
	void *hosting;
	bool hosted;
	int controlZone;
	int stun;
	int slowed;
	int frenzy;
}				t_StatusEffects;

typedef struct s_AttackStruct
{
	int damage;
	int critChance;
}				t_AttackStruct;

typedef struct s_AttackWithDebuff
{
	int damage;
	int critChance;
	int debuffChance;
}				t_AttackWithDebuff;

typedef struct s_AttackWithStatus
{
	int damage;
	int critChance;
	int statusChance;
	int stacks;
	bool statusActive;
}				t_AttackWithStatus;

typedef struct s_LastingEffect
{
	int turns;
}				t_LastingEffect;

typedef struct s_FlamePortStats
{
	int selfDamagePrecent;
	int range;
}				t_FlamePortStats;

typedef struct s_PhantomKnight
{
	int turns;
	bool opportunity;
	int hits;
	int armor;
}				t_PhantomKnight;

typedef struct s_Damager
{
	void *damager;
	int type;
}				t_Damager;

namespace SelectorTypesForAi
{
	enum
	{
		SELECTOR,
		TILE_SELECTOR,
		ALWAYS_USABLE
	};
};

typedef struct s_TargetingType
{
	int range;
	int targetType;
	bool characters;
	bool staticSearch;
	bool melee;
}				t_TargetingType;

#endif
