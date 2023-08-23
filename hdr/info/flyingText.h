
#ifndef FLYING_TEXT_H
# define FLYING_TEXT_H

# include "../ab.h"

class FlyingSnippet
{
	public:
		Snippet *snippet;
		int time = 0;
		int third = 0;
		float yAdd = 0.0f;
		float xAdd = 0.0f;
		float speed = 300.0f;
		float drag = 1.0f;
		SDL_FPoint dir;
		void ManageAlpha();
		void ManageMovement();
	public:
		bool done = false;
		FlyingSnippet(const char *text, Vector postion, Vector direction, int size, int time);
		~FlyingSnippet() {Destroy();};
		void SetAdds(float xAdd, float yAdd) {FlyingSnippet::xAdd = xAdd; FlyingSnippet::yAdd = yAdd;};
		void SetSpeed(float speed) {FlyingSnippet::speed = speed;};
		void SetDrag(float drag) {
			if (drag < 0.0001f && drag > 0.0001f)
				return ;
			FlyingSnippet::drag = drag;
		};
		void Update();
		void Destroy();
};

#endif
