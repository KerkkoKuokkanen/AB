
#include "../../hdr/global.h"

void ObjectManager::AddObject(void *obj, int type)
{
	switch (type)
	{
		case DAGGER_OBJ:
			daggers.push_back((Dagger*)obj);
			break ;
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < daggers.size(); i++)
	{
		daggers[i]->Update();
		if (daggers[i]->remove)
		{
			daggers[i]->Destroy();
			delete daggers[i];
			daggers.erase(daggers.begin() + i);
		}
	}
}

void ObjectManager::Clear()
{
	for (int i = 0; i < daggers.size(); i++)
		daggers[i]->Destroy();
	daggers.clear();
}
