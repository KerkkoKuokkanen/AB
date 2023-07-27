
#ifndef ADD_STATUS_H
# define ADD_STATUS_H

# include "../../ab.h"

namespace StatusSigns
{
	enum
	{
		BURN
	};
};

class AddStatus
{
	private:
		Sprite *status = NULL;
		Number *number = NULL;
		SDL_Point goal = {0, 0};
		Character *target = NULL;
		Character *character = NULL;
		int counter = 0;
		int statusSign = 0;
		int amount = 0;
		float dist = 0.0f;
		SDL_FPoint direction = {0.0f, 0.0f};
		void CreateSprite();
		void CreateNumber();
		void PositionStatus(Character *character, Character *target);
		void PositionNumber();
		void GetGoal(Character *target);
		void MoveEffect();
		void ScaleSprite();
		bool atTarget();
	public:
		bool done = false;
		AddStatus(Character *character, Character *target, int statusSign, int amount = 1);
		~AddStatus() {Destroy();};
		void Update();
		void Destroy();
};

#endif
