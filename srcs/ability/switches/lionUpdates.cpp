
#include "../../../hdr/global.h"

void Abilities::UpdateLionAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case LION_SMACK:
		{
			LionSmack *use = (LionSmack*)animation.animation;
			use->Update();
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					misses.push_back(createBasicMISS(character->position, targetPoint, true));
			}
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
