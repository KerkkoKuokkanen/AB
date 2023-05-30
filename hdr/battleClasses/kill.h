
#ifndef KILL_H
# define KILL_H

# include "../ab.h"

# define KILL_TIME 60

typedef struct s_kill
{
	Character *character;
	int timer;
}				t_kill;

class Kill
{
	private:
		std::vector<t_kill> kills;
		SDL_Texture *killPart1;
		SDL_Texture *killPart2;
		void RemoveCharacter(Character *character);
		void KillColorFade(t_kill *killed);
		void CreateParticles(Character *character);
		float getSpeed(Vector dir, Vector genDir);
	public:
		Kill();
		void AddCharacterToKill(Character *character);
		void Update();
		bool killing = false;
};

#endif
