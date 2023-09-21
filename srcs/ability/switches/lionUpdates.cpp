
#include "../../../hdr/global.h"

bool Abilities::CheckForPhantomKnight()
{
	if (phantSelector != NULL)
	{
		phantSelector->ChangeOrientation();
		return (true);
	}
	return (false);
}

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
					CreateMiss(character->position, target->position, target, true);
			}
			if (use->done)
			{
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
		case PHANTOM_KNIGHT:
		{
			PhantomAnim *use = (PhantomAnim*)animation.animation;
			use->Update();
			if (use->done)
			{
				effectUpdater.SetEffect(character, targetPoint, ability);
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
