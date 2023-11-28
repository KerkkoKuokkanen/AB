
#include "../../../hdr/global.h"

static void ApplyRainPoison(Character *target, Character *character, t_Ability *ability)
{
	PlaySound(gameState.audio.rainAttack[1], Channels::VOLUME_10, 0);
	gameState.updateObjs.info->AddColorEffect(target->sprite, 6, Color(28, 138, 0), 0);
	t_AcidRainDamage *stack = (t_AcidRainDamage*)ability->stats;
	int stacks = stack->stacks;
	std::string used;
	used += std::to_string(stacks);
	used += " poison";
	const char *ret = used.c_str();
	CreateTextSnippet(character, target, ret, 1000, Color(28, 138, 0));
	for (int i = 0; i < stacks; i++)
		target->statuses.poison.push_back(3);
}

void Abilities::UpdateWitchAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case ACID_RAIN:
		{
			AcidRain *used = (AcidRain*)animation.animation;
			used->Update();
			if (used->createDamage)
			{
				if (!StatusApply(ability, character, target, true))
					CreateMiss(character->position, target->position, target, true);
				else
					ApplyRainPoison(target, character, ability);
			}
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
