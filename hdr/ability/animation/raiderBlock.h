
#ifndef RAIDER_BLOCK_H
# define RAIDER_BLOCK_H

# include "../../ab.h"

class RaiderBlock : public AbBase
{
	private:
		Character *character;
		int counter = 0;
	public:
		bool done = false;
		bool createBuff = false;
		RaiderBlock(Character *character);
		~RaiderBlock() {Destroy();};
		void Update();
		void Destroy();
};

#endif
