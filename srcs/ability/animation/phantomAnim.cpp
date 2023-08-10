
#include "../../../hdr/global.h"
#define PART_AMOUNT 350
#define SCALE_TIME 20

static Color GetColor()
{
	int hit = rand() % 100;
	if (hit > 91)
		return (Color(255, 255, 255));
	if (hit < 70)
		return (Color(0, 76, 255));
	if (hit > 25)
		return (Color(0, 217, 255));
	if (hit > 10)
		return (Color(0, 255, 213));
	return (Color(1, 1, 1));
}

void PhantomAnim::CreateSprite(SDL_Point target)
{
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	SDL_Point pos = {tDest.x + 2500, tDest.y + 1500};
	SDL_Rect dest = {pos.x, pos.y, 6800, 0}; //8160
	SDL_Rect srect = {0, 0, 1000, 0}; //1200
	t_SpriteAndSRect add;
	add.srect = srect;
	Sprite *sprite = new Sprite(gameState.textures.chars.lionIdle[0], dest, NULL, NULL, 0, FLIP_NONE);
	sprites.push_back(add);
	sprite->setSRect(&sprites[sprites.size() - 1].srect);
	sprite->ColorMod(0, 217, 255);
	sprite->AlphaMod(170);
	sprite->orderLayer = target.y;
	int height = gameState.battle.ground->map[target.y][target.x].height;
	sprite->setDepth((float)height * (float)BATTLE_DEPTH_UNIT + 8.0f);
	gameState.render->AddSprite(sprite, BATTLEGROUND_LAYER);
	sprites[sprites.size() - 1].sprite = sprite;
}

void PhantomAnim::CreateParticles(SDL_Point target)
{
	SDL_Rect tDest = gameState.battle.ground->getTileDest(target);
	SDL_Point pos = {tDest.x + 2500, tDest.y + 1500};
	for (int i = 0; i < PART_AMOUNT; i++)
	{
		int xAdd = rand() % 200 - 100;
		int yAdd = rand() % 200 - 100;
		float angle = float_rand() * (PI * 0.6f);
		angle = (rand() % 2 == 0) ? angle : -angle;
		Vector dir(0.0f, -1.0f);
		vectorRotate(dir, angle);
		float drag = 1.01f + float_rand() * 0.1f;
		float speed = rand() % 200 + 40;
		Vector place((float)(pos.x + xAdd), (float)(pos.y + yAdd));
		int life = rand() % 40 + 60;
		gameState.updateObjs.partManager->CreateModParticle(dir, place, speed, GetColor(), Color(1, 1, 1), life, drag, false);
	}
}

PhantomAnim::PhantomAnim(std::vector<SDL_Point> targets)
{
	done = false;
	for (int i = 0; i < targets.size(); i++)
	{
		CreateSprite(targets[i]);
		CreateParticles(targets[i]);
	}
}

void PhantomAnim::ScaleKnight(int index)
{
	if (counter > SCALE_TIME)
		return ;
	float unit = 8160.0f / (float)SCALE_TIME;
	int scale = rounding(unit * (float)counter);
	float sUnit = 1200.0f / (float)SCALE_TIME;
	int sScale = rounding(sUnit * (float)counter);
	if (sScale > 1200)
		sScale = 1200;
	if (sScale < 0)
		sScale = 0;
	sprites[index].srect.h = sScale;
	sprites[index].sprite->dest.h = scale;
	sprites[index].sprite->dest.y -= 408;
}

void PhantomAnim::UpdateKnight()
{
	if (counter > 100)
		return ;
	for (int i = 0; i < sprites.size(); i++)
	{
		ScaleKnight(i);
	}
}

void PhantomAnim::Update()
{
	if (done)
		return ;
	UpdateKnight();
	counter++;
	if (counter > 120)
		done = true;
}

void PhantomAnim::Destroy()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		delete sprites[i].sprite;
	}
}
