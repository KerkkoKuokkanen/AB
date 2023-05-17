
#include "../../hdr/global.h"

void Particle::setPosition(Vector pos)
{
	Particle::pos.x = pos.x;
	Particle::pos.y = pos.y;
	sprite->Position(pos);
}

void Particle::setDirection(Vector dir)
{
	Vector d = dir.Normalized();
	Particle::dir.x = d.x;
	Particle::dir.y = d.y;
}

void Particle::setSpeed(float speed)
{
	Particle::speed = speed;
}

void Particle::setLifeTime(int lifeTime)
{
	life = lifeTime;
	ogLife = lifeTime;
}

void Particle::setGravity(int sign)
{
	gravity = sign;
	if (gravity == 1)
		return ;
	if (gravity == 2)
		return ;
	gravity = 0;
}

void setScale(float scale)
{
	return ;
}

void Particle::setTexture(SDL_Texture *text)
{
	sprite->setTexture(text);
}

void Particle::init()
{
	SDL_Rect dest = {0, 0, 200, 200};
	sprite = new Sprite(gameState.textures.KillParticle[0], dest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(sprite, PARTICLE_LAYER);
}

void Particle::Activate()
{
	sprite->Activate();
	active = true;
}

void Particle::Deactivate()
{
	sprite->Deactivate();
}

void Particle::Update()
{
	if (life <= 0)
	{
		active = false;
		sprite->Deactivate();
		return ;
	}
	sprite->Move(Vector(dir.x * speed, dir.y * speed));
	speed /= 1.015f;
	life--;
}
