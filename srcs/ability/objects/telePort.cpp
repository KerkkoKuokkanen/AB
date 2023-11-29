
#include "../../../hdr/global.h"
#define TIME_OUT 500
#define PART_DISTANCE 1500

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 85)
		return (Color(14, 47, 99));
	if (hit > 60)
		return (Color(51, 78, 196));
	if (hit > 45)
		return (Color(3, 7, 28));
	if (hit > 20)
		return (Color(48, 43, 122));
	return (Color(61, 152, 209));
}

TelePort::TelePort(Character *moved, SDL_Point goal)
{
	startPosition = moved->position;
	targetPosition = goal;
	character = moved;
	sur = getSurface(moved);
	moved->setAnimationActive(true);
	partCounter = rand() & PART_DISTANCE;
	Vector place = gameState.battle.ground->GetCharacterCoord(goal, moved);
	targetDest.x = rounding(place.x);
	targetDest.y = rounding(place.y);
}

void TelePort::CreateParticles(int start, int end)
{
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	int y = start;
	while (y < end)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			partCounter++;
			if (partCounter >= FLAME_PORT_PART_DISTANCE)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				Vector dir(0.0f, -1.0f);
				float angle = float_rand() * (PI);
				angle = (rand() % 2 == 0) ? -angle : angle;
				vectorRotate(dir, angle);
				float speed = rand() % 300 + 300;
				float drag = 1.1f;
				float yAdd = float_rand() * 0.2f;
				yAdd = (rand() % 2 == 0) ? -yAdd : yAdd;
				int life = rand() % 5 + 22;
				Sprite *used = new Sprite(gameState.textures.KillParticle[0], {rounding(xP), rounding(yP), 220, 200}, NULL, NULL, 0, FLIP_NONE);
				Color ret = GetColor();
				used->ColorMod(ret.r, ret.g, ret.b);
				t_TeleParticle add = {used, {dir.x, dir.y}, speed, life, drag, yAdd, {}};
				SDL_Point place = {rounding(xP - dest.x), rounding(yP - dest.y)};
				add.saves.push_back({place, 255});
				used->Deactivate();
				gameState.render->AddSprite(used, TELEPORT_LAYER);
				particles.push_back(add);
				partCounter = 0;
			}
		}
		y++;
	}
}

void TelePort::ActivateParticles()
{
	for (int i = 0; i < particles.size(); i++)
		particles[i].particle->Activate();
	character->sprite->Deactivate();
	character->stand->Deactivate();
}

void TelePort::ManageCreatingParticles()
{
	if (counter < 4)
	{
		int unit = sur->h / 4;
		CreateParticles(unit * counter, unit * (counter + 1));
	}
	if (counter == 4)
	{
		ActivateParticles();
	}
}

int TelePort::ManageParticleLifeAndAlpha(int index)
{
	int i = index;
	if (particles[i].life <= 0)
		return (0);
	particles[i].life -= 1;
	if (particles[i].life <= 13)
	{
		float unit = 255.0f / 13.0f;
		float alpha = unit * particles[i].life;
		int used = rounding(alpha);
		if (used < 0)
			used = 0;
		particles[i].particle->AlphaMod(alpha);
		return (used);
	}
	return(255);
}

SDL_Point TelePort::GetCurrentPlace(int index)
{
	int i = index;
	SDL_Rect pDest = particles[i].particle->dest;
	SDL_Rect cDest = character->sprite->dest;
	SDL_Point used = {pDest.x - cDest.x, pDest.y - cDest.y};
	return (used);
}

void TelePort::ManageParticleMoving()
{
	if (counter < 4)
		return ;
	for (int i = 0; i < particles.size(); i++)
	{
		float xAdd = particles[i].direction.x * particles[i].speed;
		float yAdd = particles[i].direction.y * particles[i].speed;
		particles[i].particle->Move(Vector(xAdd, yAdd));
		particles[i].speed /= particles[i].drag;
		particles[i].direction.y += particles[i].yAdd;
		Vector dir(particles[i].direction.x, particles[i].direction.y);
		dir = dir.Normalized();
		particles[i].direction = {dir.x, dir.y};
		int alpha = ManageParticleLifeAndAlpha(i);
		SDL_Point place = GetCurrentPlace(i);
		particles[i].saves.push_back({place, alpha});
	}
}

void TelePort::ManageFirstPhaseParts()
{
	if (firstPhaseDone)
		return ;
	ManageParticleMoving();
	if (counter > 4)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			if (particles[i].life > 0)
				return ;
		}
		countSave = counter;
		firstPhaseDone = true;
	}
}

void TelePort::MoveSecondPhaseParts()
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i].saves.size() == 0)
		{
			secondPhaseDone = true;
			return ;
		}
		t_PartSavePostion save = particles[i].saves[particles[i].saves.size() - 1];
		particles[i].saves.erase(particles[i].saves.begin() + particles[i].saves.size() - 1);
		SDL_Point place = {save.place.x + targetDest.x, save.place.y + targetDest.y};
		particles[i].particle->Position(Vector((float)place.x, (float)place.y));
		particles[i].particle->AlphaMod(save.alpha);
	}
}

void TelePort::ManageSecondPhase()
{
	if (!firstPhaseDone)
		return ;
	if (counter - countSave == 13)
		PlaySound(gameState.audio.teleport[1], Channels::VOLUME_26, 0);
	MoveSecondPhaseParts();
	if (secondPhaseDone)
	{
		gameState.battle.ground->PlaceCharacter(targetPosition, character);
		gameState.battle.ground->map[startPosition.y][startPosition.x].character = NULL;
		gameState.battle.ground->map[startPosition.y][startPosition.x].blocked = false;
		gameState.battle.ground->map[targetPosition.y][targetPosition.x].character = character;
		gameState.battle.ground->map[targetPosition.y][targetPosition.x].blocked = true;
		character->sprite->Activate();
		character->stand->Activate();
	}
}

void TelePort::Update()
{
	createMove = false;
	if (done)
		return ;
	character->setAnimationActive(true);
	ManageCreatingParticles();
	ManageFirstPhaseParts();
	ManageSecondPhase();
	if (counter == 6)
		PlaySound(gameState.audio.teleport[0], Channels::VOLUME_26, 0);
	counter++;
	if (secondPhaseDone)
		done = true;
	if (counter >= TIME_OUT)
		done = true;
}

void TelePort::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->Activate();
	character->stand->Activate();
	gameState.render->ClearLayer(TELEPORT_LAYER);
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].particle->SetRemoved();
		delete particles[i].particle;
	}
	particles.clear();
}
