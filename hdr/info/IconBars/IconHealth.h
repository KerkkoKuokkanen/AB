
#ifndef ICON_HEALTH_H
# define ICON_HEALTH_H

# include "../../ab.h"

class IconHealth
{
	private:
		bool red = false;
		Sprite *bar[3] = {NULL, NULL, NULL};
		Sprite *reducer = NULL;
		int reducerGoalValue = 0;
		int counter = 0;
		void CreateBar(int curr, int max, bool red, int slot);
		void CreateReducer(int start, int curr, int max, bool red, int slot);
		bool atGoal = false;
		float scaleAmount = 0.0f;
	public:
		IconHealth(int start, int curr, int max, bool red, int slot);
		~IconHealth() {Destroy();};
		void Reposition(int slot);
		void Update();
		void Destroy();
};

#endif
