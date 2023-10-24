
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
		BOMB_STRUCT
	};
};

namespace BuffTypes
{
	enum
	{
		ACCURACY,
		PROTECTION
	};
};

typedef struct s_ToxicBlade
{
	int hits;
	int stacks;
	int turns;
	int hitChance;
}				t_ToxicBlade;

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
}				t_BuffDebuff;

typedef struct s_ToxicStat
{
	int stacks;
	int turns;
}				t_ToxicStat;

typedef struct s_DamageBomb
{
	int critChance;
	int version;
	bool additionalBlocks;
	int stacks;
	int statusChance;
}				t_DamageBomb;

typedef struct s_StatusEffects
{
	std::vector<int> burns;
	std::vector<t_BuffDebuff> buffs;
	std::vector<t_BuffDebuff> deBuffs;
	std::vector<t_ToxicStat> toxicBlade;
	std::vector<int> poison;
	std::vector<int> bleed;
	void *hosting;
	bool hosted;
	int stun;
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
}				t_PhantomKnight;

#endif
