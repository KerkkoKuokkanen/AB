
#include "../../../hdr/global.h"
#include "../../../hdr/render/camera.h"

#define BLACK_TIME 7
#define RED_TIME 9
#define TO_NORMAL 4

#define MOVE_OUT 6
#define MOVE_IN 10

#define DAMAGE_DONE 30

#define PARTICLE_DISTANCE 3200

void DamageCreator::CreateDamage(Character *character, Color startColor, int armorDamage, int healthDamage, Vector partDir, std::vector<t_Sound> &sounds, bool move)
{
	if (character == NULL)
		return ;
	character->damaged = true;
	SDL_Point pos = character->position;
	Vector place = gameState.battle.ground->GetCharacterCoord(pos, character);
	SDL_Rect dest = {rounding(place.x), rounding(place.y), character->sprite->dest.w, character->sprite->dest.h};
	t_Damage add = {character, armorDamage, healthDamage, partDir.Normalized(), 0, dest, startColor.r, startColor.g, startColor.b, false};
	add.move = move;
	for (int i = 0; i < sounds.size(); i++)
		PlaySound(sounds[i].sound, sounds[i].channel, sounds[i].loops);
	character->stats.health -= healthDamage;
	character->stats.armor -= armorDamage;
	if (character->stats.health < 0)
		character->stats.health = 0;
	if (character->stats.armor < 0)
		character->stats.armor = 0;
	damages.push_back(add);
	SetScreenShake(500, 4);
	if (partDir.y < 0.0f)
		return ;
	character->sprite->orderLayer = (pos.y + 1);
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
		float divider = (MOVE_OUT + 1.0f - (time - MOVE_OUT));
		if (divider == 0)
			divider = 1.0f;
		float amount = 250.0f / divider;
		character->sprite->Move(Vector(-dir.x * amount, -dir.y * amount));
		return ;
	}
	if (character->killed)
		return ;
	gameState.battle.ground->PlaceCharacter(character->position, character);
	SDL_Point pos = character->position;
	character->sprite->orderLayer = pos.y;
}

float DamageCreator::GetSpeed(Vector dir, Vector genDir)
{
	float angle = vectorAngle(dir, genDir);
	float speedUnit = (float)gameCamera.screen.width / 400.0f;
	float speed = (rand() % ((int)speedUnit * 60)) + speedUnit * 10.0f;
	if (angle > 0.78)
		return (speed);
	float unit = (speedUnit * 60.0f) / 0.78f;
	speed += (speedUnit * 60.0f) - (unit * angle);
	return (speed);
}

int DamageCreator::GetLifeTime()
{
	int life = 40;
	life += rand() % 30;
	return (life);
}

float DamageCreator::GetDrag()
{
	float drag = 1.015f;
	float add = float_rand() / 18.0f;
	return (drag + add);
}

float DamageCreator::GetYAdd()
{
	return (float_rand() / 100.0f);
}

void DamageCreator::CreateParticles(Character *character, Vector partDir, Color start)
{
	SDL_Surface *sur = getSurface(character);
	if (sur == NULL)
		return ;
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	int counterGoal = PARTICLE_DISTANCE;
	int counter = counterGoal;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	Color end(0, 0, 0);
	for (int y = 0; y < sur->h; y++)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			counter++;
			if (counter >= counterGoal)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir = getDirection(partDir);
				gameState.updateObjs.partManager->CreateModParticle(dir, Vector(xP, yP), GetSpeed(dir, partDir),
													start, end, GetLifeTime(), GetDrag(), false, GetYAdd());
				counter = 0;
			}
		}
	}
}

void DamageCreator::Update()
{
	bool visited = false;
	for (int i = 0; i < damages.size(); i++)
	{
		ColorManage(damages[i].character, damages[i].time);
		if (damages[i].move)
			MoveManage(damages[i].character, damages[i].time, damages[i].partDir, damages[i].ogPos);
		if (!damages[i].partDone && !visited)
		{
			visited = true;
			damages[i].partDone = true;
			CreateParticles(damages[i].character, damages[i].partDir, Color(damages[i].r, damages[i].g, damages[i].b));
		}
		if (damages[i].time >= DAMAGE_DONE)
		{
			damages[i].character->damaged = false;
			damages.erase(damages.begin() + i);
			i = (damages.size() == 0) ? 0 : i - 1;
			continue ;
		}
		damages[i].time++;
	}
}

void DamageCreator::RemoveCharacter(Character *character)
{
	for (int i = 0; i < damages.size(); i++)
	{
		if (damages[i].character == character)
		{
			damages[i].character->damaged = false;
			damages.erase(damages.begin() + i);
			continue ;
		}
	}
}
