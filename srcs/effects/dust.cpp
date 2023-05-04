
#include "../../hdr/global.h"

//x' = x cos θ − y sin θ
//y' = x sin θ + y cos θ

Dust::Dust(SDL_Point position, Vector direction)
{
	int dustAmount = rand() % 5 + 20;
	lifeTime = 60;
	direction = direction.Normalized();
	for (int i = 0; i < dustAmount; i++)
	{
		t_Dust add;
		add.lifeTime = rand() % 25 + 12;
		int sign = (rand() % 2 == 1) ? (-1) : 1;
		float angleVariance = (float_rand() * 0.5f) * sign;
		add.direction = {
			direction.x * cos(angleVariance) - direction.y * sin(angleVariance),
			direction.x * sin(angleVariance) + direction.y * cos(angleVariance)
		};
		add.velocity = (float)(rand() % 10 + 10);
		SDL_Rect dest = {
			position.x + rand() % 1500 - rand() % 1500,
			position.y + rand() % 600 - rand() % 600,
			600, 600
		};
		add.dust = new Sprite(gameState.textures.dust, dest, NULL, NULL, 0, FLIP_NONE);
		dusts.push_back(add);
		gameState.render->AddSprite(dusts[i].dust, DUST_LAYER);
	}
}

void Dust::Destroy()
{
	for (int i = 0; i < dusts.size(); i++)
		delete dusts[i].dust;
	auto it = std::find(gameState.updateObjs.dusts.begin(), gameState.updateObjs.dusts.end(), this);
	if (it != gameState.updateObjs.dusts.end())
		gameState.updateObjs.dusts.erase(it);
	delete this;
}

void Dust::Update()
{
	for (int i = 0; i < dusts.size(); i++)
	{
		if (dusts[i].lifeTime <= 0)
		{
			dusts[i].dust->Deactivate();
			continue ;
		}
		Vector move(dusts[i].direction.x * dusts[i].velocity, dusts[i].direction.y * dusts[i].velocity);
		dusts[i].dust->Move(move);
		dusts[i].lifeTime--;
	}
	lifeTime--;
	if (lifeTime <= 0)
		Destroy();
}
