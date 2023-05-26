
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
}				t_Buttons;

class CharacterUI
{
	private:
		std::vector<Character*> characters;
		Character *activeCharacter = NULL;
		t_Buttons buttons[BUTTON_RESERVE];
		Energy *energys[ENERGYS];
		Bar *health;
		Bar *armor;
		bool turnActive = true;
		void getActive();
		void GetAbilities();
		int GetButtonIndex();
		void CreateButton(SDL_Rect place, SDL_Texture *text, int sign);
		void HandleButtonAction(int value, int buttonIndex);
		void DeactivateUI();
		void CheckIfMouseOver();
	public:
		bool overCharacterUI = false;
		bool active = false;
		CharacterUI();
		void SetCharacters(std::vector<Character> &characters);
		void Update();
		void Destroy();
		void RemoveCharacter(Character *character);
};

#endif
