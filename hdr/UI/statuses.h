
#ifndef STATUSES_H
# define STATUSES_H

# include "../ab.h"

typedef struct s_NumberAndSprite
{
	Sprite *sprite;
	Number *number;
}				t_NumberAndSprite;

typedef struct s_SnippetAndSprite
{
	Sprite *sprite;
	Snippet *snippet;
}				t_SnippetAndSprite;

typedef struct t_StatSpriteStruct
{
	t_SnippetAndSprite images;
	int statusType;
	int amount;
}				t_StatSpriteStruct;

class Statuses
{
	private:
		Character *character = NULL;
		SDL_FPoint position = {0.0f, 0.0f};
		std::vector<t_StatSpriteStruct> statuses;
		bool vertical;
		bool staticSprite;
		int size;
		int numberSize;
		int numberOffset;
		void CreateBurns();
		void CreateStatuses();
		void OrderStatuses();
		void CheckIfNewStatuses();
		void CheckIfNeedToCreateStatuses();
		bool AlreadyExists(int statusSign);
		void ChangeAmount(int &index, int amount, int num);
		void CreateFrestStatus(int statusSign);
		void RePosition();
		SDL_Rect GetRightRect(int statusSign);
		bool positioned = false;
	public:
		Statuses(Character *character, int size, int numberSize, int numOffset, bool staticSprite, bool vertical = false);
		~Statuses() {Destroy();};
		void Postion(Vector place);
		bool GetMouseOverStatuses();
		void Update();
		void Destroy();
};

#endif
