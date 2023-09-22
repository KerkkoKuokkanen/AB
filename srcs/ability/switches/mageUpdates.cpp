
#include "../../../hdr/global.h"

void Abilities::UpdateMageAnimation(t_Animation &anim, int index)
{
	switch (anim.type)
	{
		case LIGHTNING_BOLT:
		{
			MageAttack *used = (MageAttack*)anim.animation;
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
