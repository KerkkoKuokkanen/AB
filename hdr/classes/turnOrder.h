
#ifndef TURN_ORDER_H
# define TURN_ORDER_H

# include "../ab.h"

# define TARGET_SIGN -99889988

typedef struct s_Indicator
{
	Sprite *indicator;
	Character *character;
	SDL_Rect *srect;
	float x;
	bool active;
	int killMove;
}				t_Indicator;

class TurnOrder
{
	private:
		std::vector<Character*> characters;
		std::vector<t_Indicator> indicators;
		Sprite *banner;
		Sprite *backGround;
		void CreateIndicators();
		void CreateSRect(SDL_Rect *srect, int cSing);
		SDL_Rect CreateDest(int cSing);
		void StartTurn();
		bool turnStartActive = false;
		bool turnChange = false;
		bool killActive = false;
		int rightEdge, leftEdge;
		void ChangeTurn();
		void UpdateStartTurn();
		bool RightEdgeManage(t_Indicator &indicator);
		bool LeftEdgeManage(t_Indicator &indicator);
		void SideManage(t_Indicator &indicator);
		void ResetClicks();
		int target = TARGET_SIGN;
		SDL_Rect clickBoxArea = {0, 0, 0, 0};
		void MouseScroll();
		int findTheFirstActive();
		void KillMoveUpdate();
		bool NoOneMoving();
		int wait = 0;
	public:
		bool insideBox = false;
		TurnOrder(std::vector<Character> &characters);
		void Update();
		void Destroy();
		void ActivateTurnChange();
		void CheckClickBox();
		void RemoveCharacter(Character *character);
};

#endif
