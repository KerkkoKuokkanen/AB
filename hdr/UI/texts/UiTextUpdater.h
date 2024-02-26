
#ifndef UI_TEXT_UPDATER_H
# define UI_TEXT_UPDATER_H

# include "../../ab.h"

class UiTextUpdater
{
	private:
		int currentAbility = 0;
		int counter = 0;
		TextBubble *bubble = NULL;
		void UpdateBubble();
		void CreateBubble();
	public:
		void Update(int ability);
};

#endif
