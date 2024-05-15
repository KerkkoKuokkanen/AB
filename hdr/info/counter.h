
#ifndef COUNTER_H
# define COUNTER_H

# include "../ab.h"

class Counter
{
	private:
		Sprite *sprite = NULL;
		Number *turn = NULL;
		Number *allies = NULL;
		Number *enemies = NULL;
		int currentTurn = 0;
		int allied = 0;
		int enemy = 0;
		int GetEnemies();
		int GetAllies();
		void ManageEnemies();
		void ManageTurn();
		void ManageAllies();
		void CheckClickBox();
	public:
		bool insideBox = false;
		Counter();
		~Counter() {Destroy();};
		void Update();
		void Destroy();
};

#endif
