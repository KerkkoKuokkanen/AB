
#ifndef STATUSES_H
# define STATUSES_H

# include "../ab.h"

typedef struct s_NumberAndSprite
{
	Sprite *sprite;
	Number *number;
}				t_NumberAndSprite;

typedef struct t_StatSpriteStruct
{
	t_NumberAndSprite images;
	int statusType;
}				t_StatSpriteStruct;

typedef struct s_Pulser
{
	Sprite *sprite;
	int timer;
	int statusSign;
}				t_Pulser;

class Statuses
{
	private:
		Character *character = NULL;
		SDL_FPoint position = {0.0f, 0.0f};
		std::vector<t_StatSpriteStruct> statuses;
		std::vector<t_Pulser> pulsers = {};
		bool vertical;
		bool staticSprite;
		int size;
		int numberSize;
		void CreateStatuses();
		void OrderStatuses();
		void CheckIfNewStatuses();
		void CheckIfNeedToCreateStatuses();
		bool AlreadyExists(int statusSign);
		void ChangeAmount(int &index, int amount, int num);
		void CreateFrestStatus(int statusSign);
		void RePosition();
		void ManageNumbers();
		void ManagePulsers();
		void CreatePulser(int statusSign);
		void PositionPulsers();
		SDL_Rect GetRightRect(int statusSign);
	public:
		Statuses(Character *character, int size, int numberSize, bool staticSprite, bool vertical = false);
		~Statuses() {Destroy();};
		void Postion(Vector place);
		void Update();
		void Destroy();
};

#endif
