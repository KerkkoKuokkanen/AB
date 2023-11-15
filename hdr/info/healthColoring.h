
#ifndef HEALTH_COLORING_H
# define HEALTH_COLORING_H

# include "../ab.h"

class HealthColoring
{
	private:
		int counter = 0;
	public:
		~HealthColoring() {Destroy();};
		void Update();
		void Destroy();
};

#endif
