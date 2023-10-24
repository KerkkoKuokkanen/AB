
#ifndef NAIL_BOMB_BLAST_H
# define NAIL_BOMB_BLAST_H

# include "../ab.h"

typedef struct s_Nail
{
	int life;
	SDL_FPoint direction;
	float speed;
	Sprite *sprite;
}				t_Nail;

class NailBombBlast
{
	private:
		std::vector<t_Nail> nails;
		SDL_Point position;
		void CreateNails();
		void CreateParticles();
		void UpdateNailAlpha(t_Nail &nail);
		void UpdateNailPosition(t_Nail &nail);
		unsigned int type = 0;
		float speedMulti = 1.0f;
		float amountMulti = 1.0f;
	public:
		bool done = false;
		NailBombBlast(SDL_Point position, unsigned int type = 0);
		~NailBombBlast() {Destroy();};
		void Update();
		void Destroy();
};

#endif
