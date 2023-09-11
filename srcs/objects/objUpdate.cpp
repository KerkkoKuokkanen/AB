
#include "../../hdr/global.h"

OBJ_Update::OBJ_Update()
{
	CreateToolBoxes();
}

void OBJ_Update::UpdateObjects()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Update();
}

void OBJ_Update::CreateToolBoxes()
{
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		Character *used = gameState.battle.ground->characters[i].character;
		if (used->cSing == SMITH)
		{
			ToolBox *box = new ToolBox(used);
			toolBoxes.push_back(box);
		}
	}
}

void OBJ_Update::UpdateToolBoxes()
{
	for (int i = 0; i < toolBoxes.size(); i++)
	{
		toolBoxes[i]->Update();
	}
}

void OBJ_Update::Update()
{
	UpdateObjects();
	UpdateToolBoxes();
};

ToolBox *OBJ_Update::GetToolBox(Character *character)
{
	for (int i = 0; i < toolBoxes.size(); i++)
	{
		if (toolBoxes[i]->character == character)
			return (toolBoxes[i]);
	}
	return (NULL);
}
