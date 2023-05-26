
#include "../../hdr/global.h"

SDL_Surface *getSurface(Character *character)
{
	int text = character->currentTexture;
	switch (character->cSing)
	{
		case 0:
			if (text == 0)
				return (gameState.surfaces.thiefIdle1);
			else
				return (gameState.surfaces.thiefIdle2);
		case 1:
			if (text == 0)
				return (gameState.surfaces.skeleIdle1);
			else
				return (gameState.surfaces.skeleIdle2);
	}
	return (NULL);
}

bool MenuHoverCheck(SDL_Surface *sur, SDL_Rect dest, int xMouse, int yMouse)
{
	if (sur == NULL)
		return (false);
	float wUnit = (float)sur->w / (float)dest.w;
	float hUnit = (float)sur->h / (float)dest.h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	int mouseX = xMouse - dest.x;
	int mouseY = yMouse - dest.y;
	if (mouseX < 0 || mouseX > dest.w)
		return (false);
	if (mouseY < 0 || mouseY > dest.h)
		return (false);
	int x = rounding(wUnit * (float)mouseX);
	int y = rounding(hUnit * (float)mouseY);
	if (x < 0 || x >= sur->w)
		return (false);
	if (y < 0 || y > sur->h)
		return (false);
	if (pixels[(y * sur->w) + x] != 0)
		return (true);
	return (false);
}

bool CheckIfHoveringOver(Character *character)
{
	SDL_Rect dest = character->sprite->dest;
	SDL_Surface *sur = getSurface(character);
	if (sur == NULL)
		return (false);
	float wUnit = (float)sur->w / (float)character->sprite->dest.w;
	float hUnit = (float)sur->h / (float)character->sprite->dest.h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	int mouseX = gameState.keys.mouseX - dest.x;
	int mouseY = gameState.keys.mouseY - dest.y;
	if (mouseX < 0 || mouseX > dest.w)
		return (false);
	if (mouseY < 0 || mouseY > dest.h)
		return (false);
	int x = rounding(wUnit * (float)mouseX);
	int y = rounding(hUnit * (float)mouseY);
	if (x < 0 || x >= sur->w)
		return (false);
	if (y < 0 || y > sur->h)
		return (false);
	if (pixels[(y * sur->w) + x] != 0)
		return (true);
	return (false);
}

Character *HoveringOver()
{
	int max = (-1);
	Character *character = NULL;
	for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
	{
		gameState.battle.ground->characters[i].character->hover = false;
		if (CheckIfHoveringOver(gameState.battle.ground->characters[i].character))
		{
			SDL_Point pos = gameState.updateObjs.indicator->FindCharacter(gameState.battle.ground->characters[i].character);
			if (pos.y > max && gameState.battle.ground->map[pos.y][pos.x].active)
			{
				max = pos.y;
				character = gameState.battle.ground->characters[i].character;
			}
		}
	}
	return (character);
}

void UpdateHoveredCharacter()
{
	Character *chosen = gameState.updateObjs.chosen;
	if (chosen == NULL)
		return ;
	SDL_Point position = gameState.updateObjs.indicator->FindCharacter(chosen);
	if (!gameState.battle.ground->map[position.y][position.x].highlited)
	{
		if (chosen->ally)
			gameState.battle.ground->HighLightBlock(position, 120, 255, 100);
		else
			gameState.battle.ground->HighLightBlock(position, 255, 69, 56);
		}
	if (gameState.keys.click == RELEASE_CLICK && !gameState.updateObjs.abilityManager->abilityActive)
	{
		for (int i = 0; i < gameState.battle.ground->characters.size(); i++)
			gameState.battle.ground->characters[i].character->clicked = false;
		gameState.updateObjs.abilityManager->ClearAbilities();
		chosen->clicked = true;
	}
}

void ManageTextureHovering()
{
	gameState.updateObjs.hover.overCharacter = false;
	gameState.updateObjs.chosen = NULL;
	if (gameState.updateObjs.hover.overCharacterUI ||
		gameState.updateObjs.hover.overMenu ||
		gameState.updateObjs.hover.overTurnOrder ||
		gameState.keys.middleMouse != 0)
		return ;
	Character *chosen = HoveringOver();
	gameState.updateObjs.chosen = chosen;
	if (chosen == NULL)
		return ;
	if (chosen->killed)
		return ;
	gameState.updateObjs.hover.overCharacter = true;
	chosen->hover = true;
}
