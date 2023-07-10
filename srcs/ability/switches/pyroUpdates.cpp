
#include "../../../hdr/global.h"

void Abilities::UpdatePyroAnimation(t_Animation &animation, int index)
{
	switch (animation.type)
	{
		case FLAME_PORT:
			FlamePort *use = (FlamePort*)animation.animation;
			use->Update();
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
	}
}
