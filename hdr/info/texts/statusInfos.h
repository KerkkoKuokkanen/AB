
#ifndef STATUS_INFOS_H
# define STATUS_INFOS_H

# include "../../ab.h"

class StatusInfo
{
	private:
		TextBubble *bubble = NULL;
		void SetUpBubble(int hoverIcon);
		void CreateBubbles(int hoverIcon);
		int followCorner = 0;
		int xAdd = 0;
		int yAdd = 0;
	public:
		~StatusInfo() {Destroy();};
		void SetXAndYAdd(int x, int y) {xAdd = x; yAdd = y;};
		void GiveFollowCorner(int corner) {followCorner = corner;};
		void Update(int hoverIcon);
		void Destroy();
};

#endif
