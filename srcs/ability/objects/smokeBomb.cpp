
#include "../../../hdr/global.h"

bool SmokeBomb::CheckIfNextTo(SDL_Point start, SDL_Point target)
{
	if (target.x == start.x && target.y == start.y)
		return (true);
	int xr = getXToRight(start);
	if (target.x == xr && target.y == start.y + 1)
		return (true);
	if (target.x == xr && target.y == start.y - 1)
		return (true);
	int xl = getXToLeft(start);
	if (target.x == xl && target.y == start.y + 1)
		return (true);
	if (target.x == xl && target.y == start.y - 1)
		return (true);
	return (false);
}

SmokeBomb::SmokeBomb(SDL_Point start, SDL_Point target)
{
	if (CheckIfNextTo(start, target))
	{
		PlaySound(gameState.audio.smokeBomb, Channels::SMOKE_BOMB, 0);
		destroy = true;
		setEffect = true;
		return ;
	}
	SDL_Rect dest = gameState.battle.ground->getTileDest(target);
	SmokeBomb::target = {dest.x + 3150, dest.y + 1700};
	SmokeBomb::start.x = gameState.battle.ground->map[start.y][start.x].character->sprite->dest.x;
	SmokeBomb::start.y = gameState.battle.ground->map[start.y][start.x].character->sprite->dest.y;
	SDL_Rect destination = {SmokeBomb::start.x + 2900, SmokeBomb::start.y + 1500, 1500, 1500};
	SmokeBomb::start = {destination.x + 750, destination.y + 750};
	granade = new Sprite(gameState.textures.smokeBomb, destination, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(granade, DUST_LAYER);
	Vector dir = Vector(SmokeBomb::target.x - SmokeBomb::start.x, SmokeBomb::target.y - SmokeBomb::start.y).Normalized();
	direction = {dir.x, dir.y};
	if (dir.x < 0.0f)
		rotationAdd = -28.0f;
}

bool SmokeBomb::MoveSmoke()
{
	float speed = 400.0f;
	Vector dir(direction.x * speed, direction.y * speed);
	granade->Move(dir);
	SDL_FPoint pos = {(float)(granade->dest.x + granade->dest.w / 2), (float)(granade->dest.y + granade->dest.h / 2)};
	if (Vector(target.x - pos.x, target.y - pos.y).Magnitude() < 800.0f)
		return (true);
	return (false);
}

void SmokeBomb::Finale()
{
	PlaySound(gameState.audio.smokeBomb, Channels::SMOKE_BOMB, 0);
	destroy = true;
	setEffect = true;
	delete granade;
	granade = NULL;
	return ;
}

void SmokeBomb::Update()
{
	if (granade == NULL)
		return ;
	if (MoveSmoke())
	{
		Finale();
		return ;
	}
	if (counter > 50)
	{
		Finale();
		return ;
	}
	granade->setAngle(rotation);
	rotation += rotationAdd;
	counter++;
}
