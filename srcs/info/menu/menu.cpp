
#include "../../../hdr/global.h"

static bool Pressed()
{
	static int tabtab = 0;
	if (gameState.keys.tab == 1 && tabtab == 0)
	{
		tabtab = 1;
		return (true);
	}
	if (gameState.keys.tab == 0)
		tabtab = 0;
	return (false);
}

void Menu::CheckOnScreen()
{
	if (Pressed())
	{
		onScreen = (onScreen == 0) ? 1 : 0;
		if (onScreen == 1)
			PutMenuOnScreen();
		else
			ClearMenu();
	}
}

void Menu::ClearMenu()
{

}

void Menu::PutMenuOnScreen()
{
	
}

void Menu::Update()
{
	CheckOnScreen();
	if (onScreen == 0)
		return ;
}

void Menu::Destroy()
{

}
