
#ifndef MARKER_H
# define MARKER_H

# include "../ab.h"

typedef struct s_MarkerPlace
{
	SDL_Point pos;
	std::vector<Sprite*> sprites;
	int colorSign;
}				t_MarkerPlace;

class Markers
{
	private:
		std::vector<t_MarkerPlace> marked = {};
		Vector GetMarkerStartPlace(SDL_Point position);
		int GetMarkerPosition(SDL_Point position);
		void MultipleMarkers(t_MarkerPlace *mark);
		void SetColor(t_MarkerPlace *mark);
		std::vector<Color> colors = {{171, 82, 19}, {110, 4, 4}, {120, 120, 120}, {140, 0, 47}};
		int colorCounter = 0;
		bool first = true;
	public:
		void PlaceMarker(SDL_Point position);
		~Markers() {Destroy();};
		void Destroy();
};

#endif
