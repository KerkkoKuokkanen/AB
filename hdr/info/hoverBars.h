
#ifndef HOVER_BARS_H
# define HOVER_BARS_H

# include "../ab.h"

class HoverBars
{
	private:
		Bar *health = NULL;
		Bar *armor = NULL;
		Statuses *statuses = NULL;
		Character *target = NULL;
		SDL_Point GetHealthPosition();
		void PlaceBars(SDL_Point place);
		void ManageStatuses();
		void CreateStatuses(SDL_Point place);
	public:
		HoverBars();
		~HoverBars() {Destroy();};
		void Update(Character *hovered);
		void Destroy();
};

#endif
