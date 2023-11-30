
#include "../../../hdr/global.h"
#define TIME_OUT 500
#define BEAT_TIME 60
#define SPRITE_W 500
#define BEAT_WIDTH 80

HeartBeat::HeartBeat(Character *character, Character *target)
{
	HeartBeat::character = character;
	HeartBeat::target = target;
	anim = new WitchAnimation(character, WitchAnimationType::RED, 1);
	SDL_Rect dest = gameState.battle.ground->getTileDest(target->position);
	srectUnit = SPRITE_W / BEAT_TIME;
	dest.y -= 3500;
	dest.x += 600;
	dest.w = 5000;
	dest.h = 5000;
	outline = new Sprite(gameState.textures.attacks.heartBeat[0], dest, NULL, NULL, 0, FLIP_NONE);
	outline->AlphaMod(120);
	outline->ColorMod(240, 89, 77);
	outline->orderLayer = target->sprite->orderLayer;
	outline->z = target->sprite->z + 0.1f;
	gameState.render->AddSprite(outline, BATTLEGROUND_LAYER);
	backGround = new Sprite(gameState.textures.attacks.heartBeat[1], dest, NULL, NULL, 0, FLIP_NONE);
	backGround->orderLayer = outline->orderLayer;
	backGround->z = outline->z - 0.05f;
	gameState.render->AddSprite(backGround, BATTLEGROUND_LAYER);
}

void HeartBeat::UpdateOutline()
{
	if (counter % 5 == 0)
	{
		int alpha = rand() % 50 + 100;
		outline->AlphaMod(alpha);
	}
	if (anim != NULL)
	{
		anim->Update();
		if (anim->done)
		{
			delete anim;
			anim = NULL;
		}
	}
}

void HeartBeat::CreatePulse()
{
	float wUnit = (float)outline->dest.w / (float)SPRITE_W;
	SDL_Rect dest = outline->dest;
	dest.w = rounding(wUnit * (float)BEAT_WIDTH);
	beat = new Sprite(gameState.textures.attacks.heartBeat[0], dest, &srect, NULL, 0, FLIP_NONE);
	beat->orderLayer = outline->orderLayer;
	beat->z = outline->z + 0.1f;
	srect.h = 500;
	srect.y = 0;
	srect.x = 0;
	srect.w = BEAT_WIDTH;
	beat->ColorMod(105, 5, 0);
	gameState.render->AddSprite(beat, BATTLEGROUND_LAYER);
}

void HeartBeat::ManagePulseMove()
{
	int count = counter - 6;
	float wUnit = (float)outline->dest.w / (float)SPRITE_W;
	srect.x += srectUnit;
	beat->dest.x += rounding(wUnit * (float)srectUnit);
}

void HeartBeat::ManagePulse()
{
	if (counter == 6)
		CreatePulse();
	if (beat == NULL)
		return ;
	if (counter > 6)
		ManagePulseMove();
	if (counter >= BEAT_TIME)
	{
		delete beat;
		beat = NULL;
		conterSave = counter;
		createEffect = true;
	}
}

void HeartBeat::ManageSize()
{
	if (counter < 20)
		return ;
	if (counter > 50)
		return ;
	if (counter < 35)
	{
		outline->dest = {
			outline->dest.x - 20,
			outline->dest.y - 20,
			outline->dest.w + 40,
			outline->dest.h + 40
		};
		backGround->dest = outline->dest;
		beat->dest.y = outline->dest.y;
		beat->dest.h = outline->dest.h;
		beat->dest.x -= 5;
		return ;
	}
	outline->dest = {
			outline->dest.x + 20,
			outline->dest.y + 20,
			outline->dest.w - 40,
			outline->dest.h - 40
		};
	beat->dest.y = outline->dest.y;
	beat->dest.h = outline->dest.h;
	beat->dest.x += 5;
	backGround->dest = outline->dest;
}

void HeartBeat::Update()
{
	createEffect = false;
	if (done)
		return ;
	UpdateOutline();
	ManageSize();
	ManagePulse();
	if (counter == 18)
		PlaySound(gameState.audio.heartBeat, Channels::VOLUME_45, 0);
	counter++;
	if (conterSave != (-1) && counter > conterSave + 15)
		done = true;
	if (counter >= TIME_OUT)
		done = true;
}

void HeartBeat::Destroy()
{
	if (outline != NULL)
		delete outline;
	if (beat != NULL)
		delete beat;
	if (backGround != NULL)
		delete backGround;
	if (anim != NULL)
		delete anim;
}
