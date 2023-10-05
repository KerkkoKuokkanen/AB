
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
		RAIDER_BLOCK
	};
};

namespace BuffTypes
{
	enum
	{
		ACCURACY
	};
};

typedef struct s_ToxicBlade
{
	int hits;
	int stacks;
}				t_ToxicBlade;

typedef struct s_RaiderBlock
{
	int precentage;
	int hits;
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
}				t_BuffDebuff;

typedef struct s_StatusEffects
{
	std::vector<int> burns;
	std::vector<t_BuffDebuff> buffs;
	std::vector<t_BuffDebuff> deBuffs;
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
