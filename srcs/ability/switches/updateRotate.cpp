
#include "../../../hdr/global.h"

void Abilities::UpdateRotate(int index)
{
	Rotate *rotate = (Rotate*)animations[index].animation;
	rotate->Update();
	if (rotate->done)
	{
		delete rotate;
		animations.erase(animations.begin() + index);
	}
}
