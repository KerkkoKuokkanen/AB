
#include "../../hdr/global.h"

#define PART_DIST 180
#define X_OFFSET 0
#define Y_OFFSET 0

Kill::Kill()
{
	killPart1 = gameState.textures.KillParticle[0];
	killPart2 = gameState.textures.KillParticle[1];
}

void Kill::KillColorFade(t_kill *killed)
{
	float unit = 255.0f / 40.0f;
	int time = killed->timer - 20;
	int value = rounding(unit * (float)time);
	if (time <= 0)
		value = 2;
	killed->character->sprite->ColorMod(value, value, value);
}

float Kill::getSpeed(Vector dir, Vector genDir)
{
	float angle = vectorAngle(dir, genDir);
	float speedUnit = (float)gameState.screen.width / 400.0f;
	float speed = (rand() % ((int)speedUnit * 20)) + speedUnit * 5.0f;
	if (angle > 0.78)
		return (speed);
	float unit = (speedUnit * 60.0f) / 0.78f;
	speed += (speedUnit * 60.0f) - (unit * angle);
	return (speed);
}

void Kill::CreateParticles(Character *character)
{
	SDL_Surface *sur = getSurface(character);
	if (sur == NULL)
		return ;
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	int counter = PART_DIST;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	Vector generalDir(1.0f, 0.0f);
	if (character->ally)
		generalDir.x = (-1.0f);
	for (int y = 0; y < sur->h; y++)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			counter++;
			if (counter >= PART_DIST)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir = getDirection(generalDir);
				gameState.updateObjs.partManager->CreateParticle(dir, Vector(xP, yP), getSpeed(dir, generalDir));
				counter = 0;
			}
		}
	}
}

void Kill::Update()
{
	if (kills.size() == 0)
	{
		killing = false;
		return ;
	}
	killing = true;
	bool visited = false;
	for (int i = 0; i < kills.size(); i++)
	{
		KillColorFade(&kills[i]);
		kills[i].timer--;
		if (kills[i].timer <= 0 && !visited)
		{
			visited = true;
			CreateParticles(kills[i].character);
			RemoveCharacter(kills[i].character);
			kills.erase(kills.begin() + i);
		}
	}
}

void Kill::AddCharacterToKill(Character *character)
{
	for (int i = 0; i < kills.size(); i++)
	{
		if (character == kills[i].character)
			return ;
	}
	t_kill kill = {character, KILL_TIME};
	character->killed = true;
	kills.push_back(kill);
}

void Kill::RemoveCharacter(Character *character)
{
	gameState.battle.ground->RemoveCharacter(character);
	Character *chosen = gameState.updateObjs.indicator->getChosen();
	if (chosen != NULL)
	{
		if (chosen == character)
			gameState.updateObjs.indicator->Deactivate();
	}
	gameState.updateObjs.turnOrder->RemoveCharacter(character);
	gameState.updateObjs.UI->RemoveCharacter(character);
	character->Destroy();
	//delete character; may need to be used later
}
