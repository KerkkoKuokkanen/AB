
#include "../../../hdr/global.h"

static Color getFlamePartColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit < 55)
		return (Color(255, 24, 0));
	return (Color(209, 110, 0));
}

FlamePort::FlamePort(Character *character, SDL_Point target)
{
	PlaySound(gameState.audio.flamePort[0], Channels::FLAME_PORT1, 0);
	ogPosition = character->position;
	FlamePort::character = character;
	FlamePort::target = target;
	character->setAnimationActive(true);
	SDL_Rect currDest = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect targetDest = gameState.battle.ground->getTileDest(target);
	distance = Vector((float)targetDest.x - (float)currDest.x, (float)targetDest.y - (float)currDest.y).Magnitude();
}

void FlamePort::ChangeColor()
{
	if (counter > FLAME_PORT_COLOR_CHANGE_TIME)
		return ;
	float unit = 255.0f / FLAME_PORT_COLOR_CHANGE_TIME;
	int col = (int)(unit * (float)counter);
	character->sprite->ColorMod(255, 255 - col, 255 - col);
}

void FlamePort::CreateParticles(int y, int yTarg)
{
	SDL_Surface *sur = getSurface(character);
	if (sur == NULL)
		return ;
	float wUnit = (float)character->sprite->dest.w / (float)sur->w;
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	int counter = FLAME_PORT_PART_DISTANCE;
	Uint32 *pixels = (Uint32*)sur->pixels;
	SDL_Rect dest = character->sprite->dest;
	Vector coord = gameState.battle.ground->GetCharacterCoord(target, character);
	while (y < yTarg)
	{
		for (int x = 0; x < sur->w; x++)
		{
			if (pixels[(y * sur->w) + x] == 0)
				continue ;
			counter++;
			if (counter >= FLAME_PORT_PART_DISTANCE)
			{
				float xP = (float)dest.x + (wUnit * (float)x);
				float yP = (float)dest.y + (hUnit * (float)y);
				float dx = coord.x + (wUnit * (float)x);
				float dy = coord.y + (hUnit * (float)y);
				Vector dir(0.0f, 1.0f);
				vectorRotate(dir, float_rand() * PI * 2.0f);
				dir = dir.Normalized();
				t_FlamePortPart add = {{dx - 100.0f, dy - 100.0f}, {dir.x, dir.y}, FLAME_PORT_PART_START_SPEED, 0.0f, false,
					new Sprite(gameState.textures.KillParticle[0], {0, 0, 220, 220}, NULL, NULL, 0, FLIP_NONE)};
				add.sprite->Position(Vector(xP, yP));
				Color used = getFlamePartColor();
				add.sprite->ColorMod(used.r, used.g, used.b);
				gameState.render->AddSprite(add.sprite, FLAME_PORT_LAYER);
				particles.push_back(add);
				add.sprite->Deactivate();
				counter = 0;
			}
		}
		y++;
	}
}

void FlamePort::JustMoveParticles(t_FlamePortPart &part)
{
	part.sprite->Move(Vector(part.direction.x * part.speed, part.direction.y * part.speed));
	part.speed /= 1.015f;
}

void FlamePort::MoveToTarget(t_FlamePortPart &part)
{
	if (part.atTarget)
		return ;
	SDL_Rect place = part.sprite->dest;
	Vector dir(part.target.x - (float)place.x, part.target.y - (float)place.y);
	dir = dir.Normalized();
	float currDist = Vector(part.target.x - (float)place.x, part.target.y - (float)place.y).Magnitude();
	float rotateMulti = 0.05f + (0.005f * (counter - FLAME_PORT_SECOND_PHASE_TIME));
	Vector newDir(part.direction.x + dir.x * rotateMulti, part.direction.y + dir.y * rotateMulti);
	newDir = newDir.Normalized();
	if (currDist < 250.0f)
	{
		part.sprite->Position(Vector(part.target.x, part.target.y));
		part.atTarget = true;
		return ;
	}
	if (currDist > part.phaseDist / 1.5f && part.phaseDist > 1000.0f)
		part.speed *= 1.03f;
	else
		part.speed /= 1.01f;
	part.sprite->Move(Vector(newDir.x * part.speed, newDir.y * part.speed));
	part.direction.x = newDir.x;
	part.direction.y = newDir.y;
}

void FlamePort::UpdateParticles()
{
	if (!partSecondPhase)
	{
		for (int i = 0; i < particles.size(); i++)
			JustMoveParticles(particles[i]);
		return ;
	}
	int count = 0;
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i].atTarget)
			count++;
		MoveToTarget(particles[i]);
	}
	if (count > 1000)
		lastPhase = true;
}

void FlamePort::CreateSecondPhase()
{
	partSecondPhase = true;
	for (int i = 0; i < particles.size(); i++)
	{
		SDL_Rect place = particles[i].sprite->dest;
		float x = (float)place.x;
		float y = (float)place.y;
		particles[i].phaseDist = Vector(particles[i].target.x - x, particles[i].target.y - y).Magnitude();
	}
}

void FlamePort::StartLastPhase()
{
	if (lastPhaseStarted)
		return ;
	PlaySound(gameState.audio.flamePort[2], Channels::FLAME_PORT3, 0);
	lastPhaseStarted = true;
	character->sprite->ClearColorMod();
	SDL_Point pos = ogPosition;
	gameState.battle.ground->PlaceCharacter(target, character);
	gameState.battle.ground->map[pos.y][pos.x].character = NULL;
	gameState.battle.ground->map[pos.y][pos.x].blocked = false;
}

void FlamePort::UpdateLastPhase()
{
	for (int i = 0; i < particles.size(); i++)
		particles[i].sprite->AlphaMod(255 - alpha);
	if (alpha >= 255)
	{
		character->stand->ClearAlphaMod();
		character->sprite->ClearAlphaMod();
		gameState.render->ClearLayer(FLAME_PORT_LAYER);
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].sprite->SetRemoved();
			delete particles[i].sprite;
		}
		particles.clear();
		character->setAnimationActive(false);
		done = true;
		return ;
	}
	character->sprite->AlphaMod(alpha);
	alpha += 6;
	if (alpha > 255)
		alpha = 255;
}

void FlamePort::Update()
{
	createSelfDamage = false;
	if (done)
		return ;
	ChangeColor();
	if (counter > FLAME_PORT_COLOR_CHANGE_TIME)
	{
		character->sprite->AlphaMod(0);
		character->stand->AlphaMod(0);
		UpdateParticles();
	}
	if (lastPhase)
	{
		StartLastPhase();
		UpdateLastPhase();
	}
	if (counter == FLAME_PORT_COLOR_CHANGE_TIME)
	{
		createSelfDamage = true;
		SetScreenShake(500, 4);
		for (int i = 0; i < particles.size(); i++)
			particles[i].sprite->Activate();
	}
	if (counter == 35)
		PlaySound(gameState.audio.flamePort[1], Channels::FLAME_PORT2, 0);
	if (counter >= FLAME_PORT_COLOR_CHANGE_TIME - 4 && counter < FLAME_PORT_COLOR_CHANGE_TIME)
	{
		SDL_Surface *sur = getSurface(character);
		int y = sur->h / 4;
		int multi = counter - (FLAME_PORT_COLOR_CHANGE_TIME - 4);
		CreateParticles(y * multi, y * (multi + 1));
	}
	if (counter > FLAME_PORT_SECOND_PHASE_TIME && !partSecondPhase)
		CreateSecondPhase();
	counter++;
}

void FlamePort::Destroy()
{
	for (int i = 0; i < particles.size(); i++)
		delete particles[i].sprite;
}
