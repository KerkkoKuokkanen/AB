
#ifndef STUN_UPDATES_H
# define STUN_UPDATES_H

# include "../ab.h"

typedef struct s_Stun
{
	Sprite *sprite;
	Character *target;
	int timer;
}				t_Stun;

class StunUpdates
{
	private:
		std::vector<t_Stun> questionMark = {};
		void UpdateStuns();
		void CreateStuns();
		void IterStuns();
		void UpdateFade(int index);
		bool StunExists(Character *character);
	public:
		~StunUpdates() {Destroy();};
		void Update();
		void Destroy();
};

#endif
