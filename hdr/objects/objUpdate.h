
#ifndef OBJ_UPDATE_H
# define OBJ_UPDATE_H

# include "../ab.h"

class OBJ_Update
{
	private:
		std::vector<Object*> objects;
	public:
		void AddObject(Object *obj) {objects.push_back(obj);};
		void Update() {
			for (int i = 0; i < objects.size(); i++)
				objects[i]->Update();
		};
};

#endif
