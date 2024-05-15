
#ifndef HOST_EYES_ANIM_H
# define HOST_EYES_ANIM_H

# include "../../ab.h"

class HostEyesAnim : public AbBase
{
	private:
		Character *character;
		Character *target;
		int counter = 0;
		std::vector<HostEyesEffect*> effects = {};
		void CreateEffects();
		void UpdateEffects();
	public:
		bool done = false;
		bool createEffect = false;
		HostEyesAnim(Character *character, Character *target);
		~HostEyesAnim() {Destroy();};
		void Update();
		void Destroy();
};

#endif
