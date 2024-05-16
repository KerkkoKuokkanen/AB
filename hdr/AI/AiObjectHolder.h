
#ifndef AI_OBJECT_HOLDER_H
# define AI_OBJECT_HOLDER_H

# include "../ab.h"
# include <unordered_map>

class AiObjHolder
{
	private:
		std::vector<t_AiMapUnit**> freeMaps;
		std::vector<t_AiCharacter*> freeCharacters;
		std::vector<AiIterator*> freeIterators;
		std::unordered_map<t_AiMapUnit**, t_AiMapUnit**> mapsInUse = {};
		std::unordered_map<t_AiCharacter*, t_AiCharacter*> charsInUse = {};
		std::unordered_map<AiIterator*, AiIterator*> iteratorsInUse = {};
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
