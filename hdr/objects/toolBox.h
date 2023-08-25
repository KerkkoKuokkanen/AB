
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
	public:
		ToolBox(Character *character);
		~ToolBox() {Destroy();};
		void Update();
		void Destroy();
};

#endif
