
#include "../../../hdr/global.h"

void Abilities::UpdatePyroAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case FLAME_PORT:
		{
			FlamePort *use = (FlamePort*)animation.animation;
			use->Update();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case FLAME_SLASH:
		{
			FlameSlash *use = (FlameSlash*)animation.animation;
			use->Update();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			if (use->createDamage)
			{
				if (MeleeCheck(character, target, ability))
					CreateDamage();
				else
					misses.push_back(createBasicMISS(character->position, targetPoint, true));
			}
			break ;
		}
	}
}
