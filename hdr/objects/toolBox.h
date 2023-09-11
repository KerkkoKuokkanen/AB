
#ifndef TOOL_BOX_H
# define TOOL_BOX_H

# include "../ab.h"

class ToolBox
{
	private:
		bool inHand = true;
		void CheckCharacterTexture();
		void UpdateToolBoxInHand();
		bool ToolExists(int toolSign);
		void RemoveInHandAbilities();
		void InHandAbilities();
		void ManageSmithAbilities();
		void ManageToolBoxNotInHand();
		void UpdateThrowArch();
		int iter = 0;
		SDL_Point targPos = {0, 0};
		ThrowArch *arch = NULL;
	public:
		Character *character = NULL;
		Sprite *sprite = NULL;
		ToolBox(Character *character);
		~ToolBox() {Destroy();};
		void SetToolThrow(SDL_Point target);
		void SetInHand(bool set) {inHand = set;};
		void Update();
		void Destroy();
};

#endif
