
#include "../../hdr/global.h"

void AnimationManager::SetAnimation(void *animation, int type)
{
	t_Animation add = {animation, type};
	animations.push_back(add);
	animationActive = true;
}

void AnimationManager::Update()
{
	if (animations.size() == 0)
	{
		animationActive = false;
		return ;
	}
	animationActive = true;
	for (int i = 0; i < animations.size(); i++)
		AnimationUpdate(animations[i], i);
}

void AnimationManager::AnimationUpdate(t_Animation &unit, int index)
{
	switch (unit.type)
	{
		case DAGGER_THROW_ANIMATION:
			DaggerThrowAnim* anim = (DaggerThrowAnim*)unit.animation;
			if (anim->active == false)
			{
				delete anim;
				animations.erase(animations.begin() + index);
			}
			else
				anim->Update();
			break ;
	}
}
