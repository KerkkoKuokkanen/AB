
#ifndef TOOL_BOX_H
# define TOOL_BOX_H

# include "../ab.h"

typedef struct s_CharacterAndFound
{
	Character *target;
	bool found;
}				t_CharacherAndFound;

class ToolBox
{
	private:
		bool inHand = true;
		void CheckCharacterTexture();
		void UpdateToolBoxInHand();
		std::vector<t_CharacherAndFound> targetCharacters = {};
		Snippet *number = NULL;
		Sprite *symbol = NULL;
		bool ToolExists(Character *target, int toolSign);
		void RemoveInHandAbilities();
		void InHandAbilities();
		void ManageSmithAbilities();
		void ManageOnGroundAbilities();
		void ManageToolBoxNotInHand();
		void UpdateThrowArch();
		void CheckIfInTargetCharacters(Character *target);
		void AssignDefaultOnGroundAbilities(Character *target);
		void RemoveOnGroundAbilities(Character *target);
		void RemoveFromMapPosition();
		void CreateSymbol();
		void CreateNumber();
		void ManageDisplayNumbers();
		void DisplayToolBoxNumber();
		int iter = 0;
		int supplyAmount = 0;
		SDL_Point targPos = {0, 0};
		ThrowArch *arch = NULL;
	public:
		Character *character = NULL;
		Sprite *sprite = NULL;
		ToolBox(Character *character);
		~ToolBox() {Destroy();};
		int GetSupplyAmount() {return(supplyAmount);};
		void SetToolThrow(SDL_Point target);
		void SetInHand(bool set) {inHand = set;};
		void SetToolBoxBack();
		void SupplyTarget(Character *target);
		SDL_Point getPosition() {return(targPos);};
		void Update();
		void Destroy();
};

#endif
