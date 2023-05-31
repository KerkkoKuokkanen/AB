
#ifndef ANIMATION_MANAGER_H
# define ANIMATION_MANAGER_H

# include "../ab.h"

enum {
	DAGGER_THROW_ANIMATION
};

typedef struct s_Animation
{
	void *animation;
	int type;
}				t_Animation;

class AnimationManager
{
	private:
		std::vector<t_Animation> animations;
		void AnimationUpdate(t_Animation &unit, int index);
	public:
		bool animationActive = false;
		void SetAnimation(void *animation, int type);
		void Update();
};

#endif
