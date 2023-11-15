
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
	if (killed->timer > 15)
		return ;
	float unit = 255.0f / 15.0f;
	int time = abs(killed->timer - 15);
	int value = rounding(unit * (float)time);
	if (time <= 0)
		value = 2;
	killed->character->sprite->ColorMod(value, value, value);
}

void Kill::Update()
{
	for (int i = 0; i < killEffects.size(); i++)
	{
		killEffects[i]->Update();
		if (killEffects[i]->done)
		{
			delete killEffects[i];
			killEffects.erase(killEffects.begin() + i);
			i = (killEffects.size() == 0) ? 0 : i - 1;
		}
	}
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
			SetScreenShake(700, 5);
			killEffects.push_back(new KillEffect(getSurface(kills[i].character), kills[i].character->sprite, kills[i].character->stand));
			RemoveCharacter(kills[i].character);
			kills.erase(kills.begin() + i);
			i = (i == 0) ? 0 : i - 1;
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
	t_kill kill = {character, 15};
	PlaySound(gameState.audio.kills[1], Channels::VOLUME_25, 0);
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
