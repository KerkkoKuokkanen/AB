
#include "../../../hdr/global.h"

static Color getColor()
{
	int hit = rand() % 100;
	if (hit > 90)
		return (Color(1, 1, 1));
	if (hit > 70)
		return (Color(130, 73, 158));
	if (hit > 50)
		return (Color(44, 0, 66));
	return (Color(141, 35, 194));
}

HostEyesAnim::HostEyesAnim(Character *character, Character *target)
{
	HostEyesAnim::character = character;
	HostEyesAnim::target = target;
	character->setAnimationActive(true);
	character->sprite->setTexture(gameState.textures.attacks.hostEyes);
}

void HostEyesAnim::CreateEffects()
{
	SDL_Point place = {character->sprite->dest.x + 4800, character->sprite->dest.y + 2800};
	for (int i = 0; i < 200; i++)
	{
		Vector dir(1.0f, 0.0f);
		float angle = float_rand() * PI;
		angle = (rand() % 2 == 0) ? angle : -angle;
		vectorRotate(dir, angle);
		float speed = float_rand() * 130.0f + 30.0f;
		Color used = getColor();
		int life = rand() % 10 + 12;
		float drag = 1.0f + float_rand() * 0.1f;
		gameState.updateObjs.partManager->CreateModParticle(dir, Vector((float)place.x, (float)place.y), speed, used,
																							used, life, drag, false);
	}
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(character->position);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(target->position);
	SDL_FPoint pos1 = {(float)dest1.x, (float)dest1.y};
	SDL_FPoint pos2 = {(float)dest2.x, (float)dest2.y};
	float mag = Vector(pos2.x - pos1.x, pos2.y - pos1.y).Magnitude();
	if (mag >= 13000.0f)
	{
		effects.push_back(new HostEyesEffect(character, target, 22000.0f, true));
		effects.push_back(new HostEyesEffect(character, target, 10000.0f, true));
		effects.push_back(new HostEyesEffect(character, target, 11.0f, true));
		effects.push_back(new HostEyesEffect(character, target, 10000.0f, false));
		effects.push_back(new HostEyesEffect(character, target, 22000.0f, false));
		return ;
	}
	float mUnit = 19500.0f / 13000.0f;
	float max = 2500.0f + (mUnit * mag);
	float midUnit = 8900.0f / 13000.0f;
	float mid = 1100.0f + (midUnit * mag);
	effects.push_back(new HostEyesEffect(character, target, max, true));
	effects.push_back(new HostEyesEffect(character, target, mid, true));
	effects.push_back(new HostEyesEffect(character, target, 11.0f, true));
	effects.push_back(new HostEyesEffect(character, target, mid, false));
	effects.push_back(new HostEyesEffect(character, target, max, false));
}

void HostEyesAnim::UpdateEffects()
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update();
		if (effects[i]->done)
		{
			effects[i]->CreateParticles();
			delete effects[i];
			effects.erase(effects.begin() + i);
			i = (effects.size() == 0) ? 0 : i - 1;
		}
	}
}

void HostEyesAnim::Update()
{
	createEffect = false;
	if (done)
		return ;
	if (counter == 10)
		CreateEffects();
	UpdateEffects();
	if (counter == 60)
	{
		character->setAnimationActive(false);
		character->sprite->setTexture(gameState.textures.chars.mageIdle[0]);
	}
	counter++;
	if (effects.size() == 0 && counter > 15)
		done = true;
	if (counter > 450)
		done = true;
}

void HostEyesAnim::Destroy()
{
	character->setAnimationActive(false);
	character->sprite->setTexture(gameState.textures.chars.mageIdle[0]);
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];
}
