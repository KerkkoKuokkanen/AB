
#ifndef STAT_STRUCTS_H
# define STAT_STRUCTS_H

namespace StatStructs
{
	enum
	{
		ATTACK_AND_DEBUFF,
		ATTACK_STRUCT,
		LASTING_EFFECT,
		FLAME_PORT
	};
};

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
}				t_FlamePortStats;

#endif
