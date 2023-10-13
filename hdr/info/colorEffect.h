
#ifndef COLOR_EFFECT_H
# define COLOR_EFFECT_H

# include "../ab.h"

typedef struct s_ColorEffect
{
	Sprite *sprite;
	Color color;
	int time;
	int delay;
}				t_ColorEffect;

class ColorEffects
{
	private:
		std::vector<t_ColorEffect> effects;
		void UpdateEffect(t_ColorEffect &unit);
	public:
		void AddEffect(Sprite *sprite, int time, Color color, int delay);
		~ColorEffects() {Destroy();};
		void Update();
		void Destroy();
};

#endif
