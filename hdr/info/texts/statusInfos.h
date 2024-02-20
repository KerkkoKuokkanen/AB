
#ifndef STATUS_INFOS_H
# define STATUS_INFOS_H

# include "../../ab.h"

class StatusInfo
{
	private:
	public:
		~StatusInfo() {Destroy();};
		void Update();
		void Destroy();
};

#endif
