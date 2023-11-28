
#include "../../../hdr/global.h"
#define TIMEOUT 500
#define DEFAULT_DROP_AMOUNT 50
#define DROP_ADDITION 25
#define MAX_DIST 2000.0f
#define MAX_LAND_DIST 4000.0f

AcidRain::AcidRain(Character *character, SDL_Point destination, int intensity)
{
	animation = new WitchAnimation(character, WitchAnimationType::GREEN, intensity);
	AcidRain::intensity = intensity;
	SDL_Rect dest = gameState.battle.ground->getTileDest(destination);
	defDropPos = {dest.x - 1000, dest.y - 14000};
	tileDestMid = {dest.x + 2300, dest.y - 1000};
	targetDestination = destination;
	spriteDepth = gameState.battle.ground->map[destination.y][destination.x].height * BATTLE_DEPTH_UNIT + 7.1f;
}

void AcidRain::UpdateAnimation()
{
	if (animation == NULL)
		return ;
	animation->Update();
	if (animation->done)
	{
		delete animation;
		animation = NULL;
	}
}

static Color GetRainColor()
{
	int hit = rand() % 100;
	if (hit > 80)
		return (Color(1, 250, 1));
	if (hit > 60)
		return (Color(1, 20, 1));
	if (hit > 25)
		return (Color(18, 102, 41));
	return (Color(53, 189, 90));
}

static Color GetDropColor()
{
	int hit = rand() % 100;
	if (hit > 80)
		return (Color(1, 150, 1));
	if (hit > 60)
		return (Color(1, 20, 1));
	if (hit > 25)
		return (Color(8, 52, 21));
	return (Color(23, 89, 30));
}

SDL_Point AcidRain::GetDropPosition()
{
	Vector dir(0.0f, -1.0f);
	float angle = float_rand() * PI;
	angle = (rand() % 2 == 0) ? -angle : angle;
	vectorRotate(dir, angle);
	float dist = float_rand() * MAX_DIST;
	float xAdd = dir.x * dist;
	float yAdd = dir.y * dist;
	float x = (float)defDropPos.x + xAdd;
	float y = (float)defDropPos.y + yAdd;
	SDL_Point ret = {rounding(x), rounding(y)};
	return (ret);
}

SDL_Point AcidRain::GetLandingPosition()
{
	Vector dir(0.0f, -1.0f);
	float angle = float_rand() * PI;
	angle = (rand() % 2 == 0) ? -angle : angle;
	vectorRotate(dir, angle);
	float dist = float_rand() * MAX_LAND_DIST;
	float xAdd = dir.x * dist;
	float yAdd = dir.y * dist;
	float x = (float)tileDestMid.x + xAdd;
	float y = (float)tileDestMid.y + yAdd;
	SDL_Point ret = {rounding(x), rounding(y)};
	return (ret);
}

int AcidRain::GetOrderLayer(int landY)
{
	int order = targetDestination.y;
	if (landY > tileDestMid.y)
		order += 1;
	return (order);
}

Vector AcidRain::GetDirection(SDL_Point start, SDL_Point land)
{
	SDL_Point dir = {land.x - start.x, land.y - start.y};
	Vector retDir((float)dir.x, (float)dir.y);
	retDir = retDir.Normalized();
	return (retDir);
}

void AcidRain::CreateDrops()
{
	int amount = DEFAULT_DROP_AMOUNT + (DROP_ADDITION * intensity);
	for (int i = 0; i < amount; i++)
	{
		SDL_Point pos = GetDropPosition();
		SDL_Point landPos = GetLandingPosition();
		int order = GetOrderLayer(landPos.y);
		Vector direction = GetDirection(pos, landPos);
		float speed = (float)(rand() % 50 + 400);
		t_RainDrop add;
		SDL_Rect dest = {pos.x, pos.y, 350, 480};
		float angle = -(5.0f + rand() % 16);
		add.drop = new Sprite(gameState.textures.attacks.rainDrop, dest, NULL, NULL, angle, FLIP_NONE);
		add.drop->orderLayer = order;
		add.drop->z = spriteDepth;
		int startAlpha = rand() % 30 + 20;
		add.drop->AlphaMod(startAlpha);
		add.alpha = startAlpha;
		add.direction = {direction.x, direction.y};
		add.speed = speed;
		add.heightDestination = landPos.y;
		Color used = GetRainColor();
		add.drop->ColorMod(used.r, used.g, used.b);
		gameState.render->AddSprite(add.drop, BATTLEGROUND_LAYER);
		drops.push_back(add);
	}
}

void AcidRain::MoveDrop(t_RainDrop *drop)
{
	float speed = drop->speed;
	float xAdd = drop->direction.x * speed;
	float yAdd = drop->direction.y * speed;
	drop->drop->Move(Vector(xAdd, yAdd));
}

void AcidRain::ManageDropAlpha(t_RainDrop *drop)
{
	int alpha = drop->alpha;
	if (alpha >= 255)
		return ;
	alpha += 20;
	if (alpha > 255)
		alpha = 255;
	drop->drop->AlphaMod(alpha);
}

void AcidRain::CreateDropParticle(t_RainDrop *drop)
{
	SDL_Rect dest = drop->drop->dest;
	SDL_Point pos = {dest.x + 160, dest.y + 220};
	Vector dir(0.0f, -1.0f);
	float angle = float_rand() * (PI / 3.0f);
	angle = (rand() % 2 == 0) ? -angle : angle;
	vectorRotate(dir, angle);
	float speed = float_rand() * 50.0f + 80.0f;
	Color used = GetDropColor();
	int life = 13;
	gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)pos.x, (float)pos.y), speed, used, used, life, 1.01f, false, 0.14f);
}

void AcidRain::UpdateDrops()
{
	if (counter > 8 && counter < 65)
	{
		if (counter % 3 == 0)
			CreateDrops();
	}
	for (int i = 0; i < drops.size(); i++)
	{
		MoveDrop(&drops[i]);
		ManageDropAlpha(&drops[i]);
		if (drops[i].drop->dest.y > drops[i].heightDestination)
		{
			if (rand() % 6 == 0)
				CreateDropParticle(&drops[i]);
			delete drops[i].drop;
			drops.erase(drops.begin() + i);
			i = (drops.size() == 0) ? 0 : i - 1;
		}
	}
}

void AcidRain::PlayRainSound()
{
	if (intensity < 2)
	{
		PlaySound(gameState.audio.rainAttack[0], Channels::VOLUME_48, 0);
		return ;
	}
	if (intensity < 4)
	{
		PlaySound(gameState.audio.rainAttack[0], Channels::VOLUME_52, 0);
		return ;
	}
	if (intensity < 6)
	{
		PlaySound(gameState.audio.rainAttack[0], Channels::VOLUME_56, 0);
		return ;
	}
	PlaySound(gameState.audio.rainAttack[0], Channels::VOLUME_60, 0);
}

void AcidRain::Update()
{
	createDamage = false;
	if (done)
		return ;
	UpdateAnimation();
	UpdateDrops();
	counter++;
	if (counter == 9)
		PlayRainSound();
	if (counter == 56)
		createDamage = true;
	if (counter > 65 && drops.size() == 0)
		done = true;
	if (counter >= TIMEOUT)
		done = true;
}

void AcidRain::Destroy()
{
	if (animation != NULL)
		delete animation;
	for (int i = 0; i < drops.size(); i++)
		delete drops[i].drop;
	drops.clear();
}
