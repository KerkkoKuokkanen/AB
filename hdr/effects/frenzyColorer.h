
#ifndef FRENZY_COLORER_H
# define FRENZY_COLORER_H

# include "../ab.h"

typedef struct s_Frenzys
{
	Character *target;
	float fadeMulti;
	int counter;
}				t_Frenzys;

class FrenzyColorer
{
	private:
		std::vector<t_Frenzys> frenzys = {};
		void UpdateUnits();
	public:
		~FrenzyColorer() {Destroy();};
		void AddCharacter(Character *target);
		void Update();
		void Destroy();
};

#endif
