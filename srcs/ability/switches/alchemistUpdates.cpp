
#include "../../../hdr/global.h"

void Abilities::UpdateAlchemistAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case NAIL_BOMB:
		{
			NailBomb *used = (NailBomb*)anim.animation;
			used->Update();
			if (used->done)
			{
				delete used;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
