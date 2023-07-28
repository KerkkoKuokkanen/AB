
#ifndef COUNTER_H
# define COUNTER_H

# include "../ab.h"

class Counter
{
	private:
		Sprite *sprite;
		Number *turn;
		Number *allies;
		Number *enemies;
		int currentTurn = 0;
		int allied = 0;
		int enemy = 0;
		int GetEnemies();
		int GetAllies();
		void ManageEnemies();
		void ManageTurn();
		void ManageAllies();
	public:
		Counter();
		~Counter() {Destroy();};
		void Update();
		void Destroy();
};

#endif
