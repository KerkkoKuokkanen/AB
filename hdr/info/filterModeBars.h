
#ifndef FILTER_MODE_BARS_H
# define FILTER_MODE_BARS_H

# include "../ab.h"

typedef struct s_FilterBars
{
	Bar *health;
	Bar *armor;
	Character *target;
	Statuses *status;
}				t_FilterBars;

class FilterModeBars
{
	private:
		std::vector<t_FilterBars> bars;
		void PostionBars(Character *target, t_FilterBars &bars);
	public:
		FilterModeBars();
		~FilterModeBars() {Destroy();};
		void Update();
		void Destroy();
};

#endif
