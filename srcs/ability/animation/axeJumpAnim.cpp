
#include "../../../hdr/global.h"
#define TIME_OUT 600
#define SPEED_SPRTE_START 190000
#define SPEED_SPRITE_TIME 22
#define SECOND_PHASE_TIME 33

static SDL_Point GetDest(SDL_Point pos)
{
	SDL_Point ret = {0, 0};
	SDL_Rect dest = gameState.battle.ground->getTileDest(pos);
	ret = {dest.x - 800, dest.y - 4700};
	return (ret);
}

AxeJumpAnim::AxeJumpAnim(Character *character, Character *target, SDL_Point pos)
{
	AxeJumpAnim::character = character;
	AxeJumpAnim::target = target;
	AxeJumpAnim::pos = pos;
	speedSpriteCounter = SPEED_SPRTE_START;
	ogPos = character->position;
}

void AxeJumpAnim::StartJump()
{
	SetScreenShake(200, 3);
	SDL_Point start = {character->sprite->dest.x, character->sprite->dest.y};
	arch = new ThrowArch(character->sprite, start, GetDest(pos), 14000.0f, 460.0f);
	character->setAnimationActive(true);
	Vector dir((float)(character->sprite->dest.x - target->sprite->dest.x), (float)(character->sprite->dest.y - target->sprite->dest.y));
	dir = dir.Normalized();
	SDL_Rect dest = character->sprite->dest;
	SDL_Point place = {dest.x + 3000, dest.y + 6600};
	CreateDust(place, dir);
	character->sprite->setTexture(gameState.textures.attacks.axeJump);
}

void AxeJumpAnim::CreateSpeedSprite()
{
	Sprite *add = new Sprite(gameState.textures.attacks.axeJump, character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	add->ColorMod(179, 24, 0);
	add->orderLayer = speedSpriteCounter;
	speedSpriteCounter += 1;
	gameState.render->AddSprite(add, BATTLEGROUND_LAYER);
	speedSprites.push_back({add, SPEED_SPRITE_TIME});
}

void AxeJumpAnim::UpdateSpeedSprite()
{
	if (speedSprites.size() == 0)
	{
		if (counter > 6)
			character->sprite->orderLayer = pos.y;
		return ;
	}
	character->sprite->orderLayer = 200000;
	float unit = 255.0f / (float)SPEED_SPRITE_TIME;
	for (int i = 0; i < speedSprites.size(); i++)
	{
		if (speedSprites[i].counter <= 0)
		{
			delete speedSprites[i].sprite;
			speedSprites.erase(speedSprites.begin() + i);
			i = (speedSprites.size() == 0) ? 0 : i - 1;
			continue ;
		}
		float alpha = unit * speedSprites[i].counter;
		int used = rounding(alpha);
		if (alpha < 0)
			alpha = 0;
		if (alpha > 255)
			alpha = 255;
		speedSprites[i].sprite->AlphaMod(alpha);
		speedSprites[i].counter--;
	}
}

void AxeJumpAnim::CreateLandingDusts()
{
	SDL_Point place = {character->sprite->dest.x, character->sprite->dest.y};
	place.x += 3000;
	place.y += 7000;
	CreateDust(place, Vector(1.0f, -0.3f));
	place.x -= 2500;
	CreateDust(place, Vector(-1.0f, -0.3f));
}

void AxeJumpAnim::StartSecondPhase()
{
	secondPhase = true;
	character->sprite->dest.x += 1000;
	character->sprite->setTexture(gameState.textures.attacks.jumpSlash[0]);
	attackTrail = new Sprite(gameState.textures.attacks.jumpSlash[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	attackTrail->orderLayer = character->sprite->orderLayer;
	attackTrail->z = character->sprite->z - 0.01f;
	gameState.render->AddSprite(attackTrail, BATTLEGROUND_LAYER);
	CreateLandingDusts();
	SetScreenShake(280, 7);
}

void AxeJumpAnim::UpdateJump()
{
	if (arch == NULL)
		return ;
	if (counter % 4 == 0)
		CreateSpeedSprite();
	arch->Update();
	if (arch->done)
	{
		delete arch;
		arch = NULL;
		gameState.battle.ground->map[ogPos.y][ogPos.x].character = NULL;
		gameState.battle.ground->map[ogPos.y][ogPos.x].blocked = false;
		gameState.battle.ground->PlaceCharacter(pos, character);
		StartSecondPhase();
	}
}

void AxeJumpAnim::UpdateSecondPhase()
{
	if (!secondPhase)
		return ;
	if (secondPhaseCounter == 5)
		createDamage = true;
	attackTrail->z = character->sprite->z - 0.01f;
	attackTrail->orderLayer = character->sprite->orderLayer;
	if (secondPhaseCounter > 10)
	{
		float unit = 255.0f / 20.0f;
		int count = secondPhaseCounter - 10;
		float alpha = 255.0f - (unit * (float)count);
		int used = rounding(alpha);
		if (used < 0)
			used = 0;
		if (used > 255)
			used = 255;
		attackTrail->AlphaMod(used);
	}
	secondPhaseCounter++;
	if (secondPhaseCounter > SECOND_PHASE_TIME)
	{
		character->setAnimationActive(false);
		character->sprite->setTexture(gameState.textures.chars.raiderIdle[0]);
		gameState.battle.ground->PlaceCharacter(pos, character);
		done = true;
	}
}

void AxeJumpAnim::Update()
{
	createDamage = false;
	if (done)
		return ;
	if (counter == 6)
		StartJump();
	UpdateJump();
	UpdateSpeedSprite();
	UpdateSecondPhase();
	counter++;
	if (counter > TIME_OUT)
		done = true;
}

void AxeJumpAnim::Destroy()
{
	if (arch != NULL)
		delete arch;
	for (int i = 0; i < speedSprites.size(); i++)
		delete speedSprites[i].sprite;
	character->setAnimationActive(false);
	if (attackTrail != NULL)
		delete attackTrail;
}
