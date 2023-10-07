
#ifndef HEALTH_COLORING_H
# define HEALTH_COLORING_H

# include "../ab.h"

typedef struct s_HealhtColoringClass
{
	int cSing;
	int top1;
	int bottom1;
	int top2;
	int bottom2;
}				t_HealthColoringClass;

typedef struct s_HealthColoring
{
	Character *character;
	Sprite *sprite;
	SDL_Rect *sRect;
}				t_HealthColoring;

class HealthColoring
{
	private:
		std::vector<t_HealthColoringClass> classes;
		std::vector<t_HealthColoring> characters;
		bool ShouldDeactivate(int index);
		bool ShouldDestroy(int index);
		void DestroyUnit(int index);
		void UpdateUnit(int index);
		t_HealthColoringClass *GetCharacterDimentions(int cSing);
		void PollForNewCharacters();
		void CreateNewCharacter(Character *character);
		void CreateNewCharacterClass(Character *character);
	public:
		HealthColoring() {Init();};
		~HealthColoring() {Destroy();};
		void Init();
		void Update();
		void Destroy();
};

#endif
