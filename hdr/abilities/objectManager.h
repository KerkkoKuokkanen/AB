
#ifndef OBJECT_MANAGER_H
# define OBJECT_MANAGER_H

# include "../ab.h"

enum {
	DAGGER_OBJ
};

class ObjectManager
{
	private:
		std::vector<Dagger*> daggers;
	public:
		void AddObject(void *obj, int type);
		void RemoveObject(void *obj, int type);
		void Update();
		void Clear();
};

#endif
