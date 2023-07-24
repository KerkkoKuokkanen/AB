
#ifndef NUMBER_H
# define NUMBER_H

# include "../ab.h"

namespace NumberType
{
	enum
	{
		WHITE,
		NORMAL,
		SMOOTH
	};
};

class Number
{
	public:
		std::vector<Sprite*> nums;
		Number(int number, int size, int layer, int orderingLayer, bool staticSprite, int numberType);
		~Number() {Destroy();};
		void Deactivate();
		void Activate();
		int getFullWidth();
		void ColorMod(Uint8 r, Uint8 g, Uint8 b);
		void AlphaMod(Uint8 alpha);
		void Resize(int size);
		void Position(Vector place);
		void Move(Vector amount);
		void Destroy();
};

#endif
