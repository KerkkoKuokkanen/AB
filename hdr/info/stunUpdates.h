
#ifndef STUN_UPDATES_H
# define STUN_UPDATES_H

# include "../ab.h"

typedef struct s_Stun
{
	Sprite *sprite;
	Character *target;
}				t_Stun;

class StunUpdates
{
	private:
		std::vector<t_Stun> questionMark = {};
		void UpdateStuns();
		void CreateStuns();
		void IterStuns();
		bool StunExists(Character *character);
	public:
		~StunUpdates() {Destroy();};
		void Update();
		void Destroy();
};

#endif
