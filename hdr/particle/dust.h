
#ifndef DUST_H
# define DUST_H

# include "../ab.h"

typedef struct s_Dust
{
	Sprite *dust;
	SDL_FPoint direction;
	float velocity;
	int lifeTime;
}				t_Dust;

class Dust
{
	private:
		std::vector<t_Dust> dusts;
		int lifeTime;
		void Destroy();
	public:
		Dust(SDL_Point position, Vector direction);
		void SimpleClear() {
			for (int i = 0; i < dusts.size(); i++)
				delete dusts[i].dust;
		};
		void Update();
		void ClearDusts();
};

#endif
