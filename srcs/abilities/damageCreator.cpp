
#include "../../hdr/global.h"

#define BLACK_TIME 7
#define RED_TIME 9
#define TO_NORMAL 4

#define MOVE_OUT 6
#define MOVE_IN 10

#define DAMAGE_DONE 30

//255, 80, 60

void DamageCreator::CreateDamage(Character *character, int armorDamage, int healthDamage, Vector partDir)
{
	if (character == NULL)
		return ;
	t_Damage add = {character, armorDamage, healthDamage, partDir, 0, character->sprite->dest};
	character->stats.health -= healthDamage;
	character->stats.armor -= armorDamage;
	damages.push_back(add);
}

void DamageCreator::ColorManage(Character *character, int time)
{
	float colorChange = 255.0f - ((255.0f / BLACK_TIME) * (float)time);
	float r = 255.0f / RED_TIME * (float)(time - BLACK_TIME);
	float g = 80.0f / RED_TIME * (float)(time - BLACK_TIME);
	float b = 60.0f / RED_TIME * (float)(time - BLACK_TIME);
	float gn = 175.0f / TO_NORMAL * (float)(time - (RED_TIME + BLACK_TIME));
	float bn = 195.0f / TO_NORMAL * (float)(time - (RED_TIME + BLACK_TIME));
	if (time <= BLACK_TIME)
	{
		character->sprite->ColorMod((Uint8)colorChange, (Uint8)colorChange, (Uint8)colorChange);
		return ;
	}
	if (time <= (RED_TIME + BLACK_TIME))
	{
		character->sprite->ColorMod((Uint8)r, (Uint8)g, (Uint8)b);
		return ;
	}
	if (time <= (RED_TIME + BLACK_TIME + TO_NORMAL))
	{
		character->sprite->ColorMod(255, (Uint8)gn, (Uint8)bn);
		return;
	}
	character->sprite->ClearColorMod();
}

void DamageCreator::MoveManage(Character *character, int time, Vector direction, SDL_Rect dest)
{
	Vector dir = direction.Normalized();
	if (time <= MOVE_OUT)
	{
		float amount = 250.0f / ((float)time + 1.0f);
		character->sprite->Move(Vector(dir.x * amount, dir.y * amount));
		return ;
	}
	if (time <= (MOVE_OUT + MOVE_IN))
	{
		float amount = 250.0f / (MOVE_OUT + 1.0f - (time - MOVE_OUT));
		character->sprite->Move(Vector(-dir.x * amount, -dir.y * amount));
		return ;
	}
	character->sprite->Position(Vector(dest.x, dest.y));
}

void DamageCreator::Update()
{
	for (int i = 0; i < damages.size(); i++)
	{
		ColorManage(damages[i].character, damages[i].time);
		MoveManage(damages[i].character, damages[i].time, damages[i].partDir, damages[i].ogPos);
		if (damages[i].time >= DAMAGE_DONE)
		{
			damages.erase(damages.begin() + i);
			continue ;
		}
		damages[i].time++;
	}
}
