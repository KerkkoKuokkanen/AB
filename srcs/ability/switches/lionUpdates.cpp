
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
					misses.push_back(createBasicMISS(character->position, targetPoint, true));
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
				for (int i = 0; i < targPoints.size(); i++)
					effectUpdater.SetEffect(character, targPoints[i], ability);
				delete use;
				animations.erase(animations.begin() + index);
			}
			break ;
		}
	}
}
