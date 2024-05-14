
#ifndef BATTLE_UI_H
# define BATTLE_UI_H

# include "../ab.h"

# define BUTTON_RESERVE 30
# define ENERGYS 12

typedef struct t_Buttons
{
	Button *button;
	int buttonSign;
	bool used;
	int energyCost;
	int fatigueCost;
}				t_Buttons;

class CharacterUI
{
	private:
		std::vector<Character*> characters;
		Character *activeCharacter = NULL;
		t_Buttons buttons[BUTTON_RESERVE];
		Energy *energys[ENERGYS];
		Bar *health = NULL;
		Bar *armor = NULL;
		FatigueBar *fatigue = NULL;
		Statuses *statuses = NULL;
		StatusInfo *stausInfo = NULL;
		UiTextUpdater *abilityText = NULL;
		Sprite *text = NULL;
		SDL_Texture *texts = NULL;
		bool turnActive = true;
		void getActive();
		void GetAbilities();
		int GetButtonIndex();
		void CreateButton(SDL_Rect place, SDL_Texture *text, int sign, int cost, int fatigue);
		void HandleButtonAction(int value, int buttonIndex);
		void DeactivateUI();
		void CheckIfMouseOver();
		void CreateTexts();
		void ManageTurnText();
		bool AbilitiesMatch();
		void PollAbilities();
		bool CheckButtonCriteria(int index);
		t_Ability *GetCharacterAbility(int type);
		int textInfoSign = 0;
	public:
		bool overCharacterUI = false;
		bool active = false;
		bool NoOneKilled();
		void UseEnergy(int cost, bool moving = false);
		void ShowEnergy(int cost, bool moving = false);
		void ShowNoEnergy();
		CharacterUI();
		void SetCharacters(std::vector<Character> &characters);
		void Update();
		void Destroy();
		void RemoveCharacter(Character *character);
		void ClearEnergys();
		Character *GetActiveCharacter() {return (activeCharacter);};
};

#endif
