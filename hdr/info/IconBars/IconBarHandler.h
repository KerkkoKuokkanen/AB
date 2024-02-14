
#ifndef ICON_BAR_HANDLER_H
# define ICON_BAR_HANDLER_H

# include "../../ab.h"

typedef struct s_CharTracker
{
	Character *character;
	int currHealth;
	int currArmor;
}				t_CharTracker;

class IconBarHandler
{
	private:
		std::vector<t_CharTracker> characters = {};
		std::vector<IconBar*> iconBars = {};
		bool CheckForNotExisting(Character *check);
		void UpdateBars();
		void PollMap();
		bool AlreadyInPool(Character *character);
		void CheckCharacterInPool(Character *character);
		void CreateNewBar(Character *character, int aStart, int a, int hStart, int h);
		void RePositionBars(int removedSlot);
	public:
		~IconBarHandler() {Destroy();};
		void Update();
		void Destroy();
};

#endif
