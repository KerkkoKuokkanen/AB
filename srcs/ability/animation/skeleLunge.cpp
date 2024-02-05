
#include "../../../hdr/global.h"
#define SPEED_SPRTE_START 190000
#define SPRITE_TRAIL_TIME 20

SkeleLunge::SkeleLunge(Character *skele, Character *target, SDL_Point pos)
{
	SkeleLunge::skele = skele;
	SkeleLunge::target = target;
	SkeleLunge::pos = pos;
	SDL_Point dest = {target->sprite->dest.x, target->sprite->dest.y};
	startPosition = skele->position;
	lungeArch = new ThrowArch(skele->sprite, {skele->sprite->dest.x, skele->sprite->dest.y}, dest, 14000.0f, 335.0f);
	lungeArch->SetGoalMagnitude(900.0f);
	skele->setAnimationActive(true);
	skele->sprite->setTexture(gameState.textures.attacks.skeleLunge);
	SDL_Point place = {skele->sprite->dest.x + 3000, skele->sprite->dest.y + 5300};
	CreateDust(place, Vector(-1.0f, 0.0f));
	CreateDust(place, Vector(1.0f, 0.0f));
	speedSpriteCounter = SPEED_SPRTE_START;
}

void SkeleLunge::CreateTrailSprites()
{
	float scale = 255.0f / 20.0f;
	for (int i = 0; i < spriteTrail.size(); i++)
	{
		float alpha = scale * (float)spriteTrail[i].counter;
		spriteTrail[i].sprite->AlphaMod(rounding(alpha));
		spriteTrail[i].counter -= 1;
		if (spriteTrail[i].counter <= 0)
		{
			delete spriteTrail[i].sprite;
			spriteTrail.erase(spriteTrail.begin() + i);
			i = (spriteTrail.size() == 0) ? 0 : i - 1;
		}
	}
	if (!firstPhase)
		return ;
	if (counter % 4 == 0 && counter != 0)
	{
		Sprite *add = new Sprite(gameState.textures.attacks.skeleLunge, skele->sprite->dest, NULL, NULL, 0, FLIP_NONE);
		int countAdd = SPRITE_TRAIL_TIME;
		add->ColorMod(179, 24, 0);
		add->orderLayer = skele->sprite->orderLayer;
		add->orderLayer = speedSpriteCounter;
		speedSpriteCounter += 1;
		spriteTrail.push_back({add, countAdd});
		gameState.render->AddSprite(add, BATTLEGROUND_LAYER);
	}
}

void SkeleLunge::Update()
{
	createDamage = false;
	if (done)
		return ;
	lungeArch->Update();
	if (lungeArch->done)
	{
		delete lungeArch;
		lungeArch = NULL;
		if (firstPhase)
		{
			createDamage = true;
			firstPhase = false;
			skele->sprite->setTexture(gameState.textures.skeleIdle1);
			SDL_Rect dest = gameState.battle.ground->getTileDest(pos);
			SDL_Point place = {dest.x + 300, dest.y - 3900};
			lungeArch = new ThrowArch(skele->sprite, {skele->sprite->dest.x, skele->sprite->dest.y}, place, 6000.0f, 160.0f);
		}
		else
		{
			done = true;
			gameState.battle.ground->map[startPosition.y][startPosition.x].character = NULL;
			gameState.battle.ground->map[startPosition.y][startPosition.x].blocked = false;
			gameState.battle.ground->PlaceCharacter(pos, skele);
			skele->setAnimationActive(false);
			skele->sprite->setTexture(gameState.textures.skeleIdle1);
		}
	}
	CreateTrailSprites();
	counter++;
}

void SkeleLunge::Destroy()
{
	if (lungeArch != NULL)
		delete lungeArch;
	for (int i = 0; i < spriteTrail.size(); i++)
		delete spriteTrail[i].sprite;
	spriteTrail.clear();
}
