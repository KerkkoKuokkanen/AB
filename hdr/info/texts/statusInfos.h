
#ifndef STATUS_INFOS_H
# define STATUS_INFOS_H

# include "../../ab.h"

class StatusInfo
{
	private:
		TextBubble *bubble = NULL;
		void SetUpBubble(int hoverIcon);
		void CreateBubbles(int hoverIcon);
	public:
		~StatusInfo() {Destroy();};
		void Update(int hoverIcon);
		void Destroy();
};

#endif
