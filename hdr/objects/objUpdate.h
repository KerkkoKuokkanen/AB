
#ifndef OBJ_UPDATE_H
# define OBJ_UPDATE_H

# include "../ab.h"

class OBJ_Update
{
	private:
		std::vector<Object*> objects;
		std::vector<ToolBox*> toolBoxes;
		void CreateToolBoxes();
		void UpdateObjects();
		void UpdateToolBoxes();
	public:
		OBJ_Update();
		ToolBox *GetToolBox(Character *character);
		void AddObject(Object *obj) {objects.push_back(obj);};
		void Update();
};

#endif
