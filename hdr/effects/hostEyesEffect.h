
#ifndef HOST_EYES_EFFECT_H
# define HOST_EYES_EFFECT_H

# include "../ab.h"

class HostEyesEffect
{
	private:
		Character *character;
		Character *target;
		float totalDist = 0.0f;
		float topAmount = 10.0f;
		bool top = false;
		SDL_FPoint genDir = {0.0f, 0.0f};
		SDL_FPoint dir = {1.0f, 0.0f};
		SDL_FPoint genPos = {0.0f, 0.0f};
		SDL_FPoint pos = {0.0f, 0.0f};
		SDL_FPoint tPos = {0.0f, 0.0f};
		std::vector<Sprite*> sprites;
		std::vector<float> counters;
		void PlaceParts();
		void CreateSprites();
		void MoveSprites();
		void ManageColors();
		void MovePos();
		bool CheckIfDone();
	public:
		bool done = false;
		HostEyesEffect(Character *character, Character *target, float topAmount, bool top = false);
		~HostEyesEffect() {Destroy();};
		void CreateParticles();
		void Update();
		void Destroy();
};

#endif
