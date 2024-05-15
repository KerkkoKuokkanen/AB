
#ifndef AI_OBJECT_HOLDER_H
# define AI_OBJECT_HOLDER_H

# include "../ab.h"

class AiObjHolder
{
	private:
		std::vector<t_AiMapUnit**> freeMaps;
		std::vector<t_AiCharacter*> freeCharacters;
		std::vector<AiIterator*> freeIterators;
	public:
		void Init();
		void Clear();
		void ReturnMap(t_AiMapUnit **map);
		void ReturnCharacter(t_AiCharacter *character);
		t_AiMapUnit **GetMap();
		t_AiCharacter *GetCharacter();
		AiIterator *GetIterator();
		void ReturnAiIterator(AiIterator *iterator);
};

#endif
