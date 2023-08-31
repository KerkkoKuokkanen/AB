
#ifndef TOOL_BOX_H
# define TOOL_BOX_H

# include "../ab.h"

class ToolBox
{
	private:
		Character *character = NULL;
		Sprite *sprite = NULL;;
		bool inHand = true;
		void CheckCharacterTexture();
		void UpdateToolBoxInHand();
		bool ToolExists(int toolSign);
		void RemoveInHandAbilities();
		void InHandAbilities();
		void ManageSmithAbilities();
		int iter = 0;
	public:
		ToolBox(Character *character);
		~ToolBox() {Destroy();};
		void Update();
		void Destroy();
};

#endif
