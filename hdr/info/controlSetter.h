
#ifndef CONTROL_SETTER_H
# define CONTROL_SETTER_H

# include "../ab.h"

class ControlSetter
{
	private:
		Character *character = NULL;
		std::vector<Control*> controls = {};
		bool CheckIfCanDo();
		Character *CheckActiveCharacter();
		void CreatePhantomControls();
		void CreateControls();
		void CreateControlsFromPostion(SDL_Point pos);
		void CreateSingle(SDL_Point pos);
		bool CheckValid(SDL_Point pos);
		void AddAdditionalControls();
	public:
		void ClearControlled();
		void Update();
		void Destroy();
};

#endif
