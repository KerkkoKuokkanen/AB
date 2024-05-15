
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
		Sprite *banner = NULL;
		Sprite *backGround = NULL;
		Sprite *hoverIndicator = NULL;
		void CreateIndicators();
		void CreateSRect(SDL_Rect *srect, int cSing);
		SDL_Rect CreateDest(int cSing);
		void StartTurn();
		bool killActive = false;
		int rightEdge, leftEdge;
		void ChangeTurn();
		void UpdateStartTurn();
		bool RightEdgeManage(t_Indicator &indicator);
		bool LeftEdgeManage(t_Indicator &indicator);
		void SideManage(t_Indicator &indicator);
		int target = TARGET_SIGN;
		SDL_Rect clickBoxArea = {0, 0, 0, 0};
		void MouseScroll();
		int findTheFirstActive();
		void KillMoveUpdate();
		void SetStuffHappening();
		void SetStuffWithoudMove();
		int InActiveList(Character *hover);
		void UpdateHoverIndicator();
		int wait = 0;
		int hoverCounter = 0;
	public:
		std::vector<t_Indicator> indicators;
		int turnCount = 0;
		bool turnStartActive = false;
		bool turnChange = false;
		bool stuffHappening = true;
		bool stuffWithOutMove = true;
		bool insideBox = false;
		TurnOrder(std::vector<Character*> &characters);
		~TurnOrder() {Destroy();};
		void ResetClicks();
		bool NoOneMoving();
		void Update();
		void Destroy();
		void ActivateTurnChange(bool force = false);
		void CheckClickBox();
		void RemoveCharacter(Character *character);
};

#endif
