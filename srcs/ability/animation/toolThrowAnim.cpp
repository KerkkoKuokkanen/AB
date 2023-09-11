
#include "../../../hdr/global.h"

ToolThrowAnim::ToolThrowAnim(Character *character, SDL_Point target)
{
	character->setAnimationActive(true);
	ToolThrowAnim::character = character;
	ToolThrowAnim::target = target;
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(target);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(character->position);
	Vector dir((float)(dest1.x - dest2.x), (float)(dest1.y - dest2.y));
	dir = dir.Normalized();
	mover = new CharacterMover(character, dir, 13, 13, 300.0f);
	box = gameState.updateObjs.objUpdate->GetToolBox(character);
	box->sprite->Deactivate();
}

void ToolThrowAnim::CreateTrail()
{
	character->sprite->setTexture(gameState.textures.attacks.toolThrow[0]);
	trail = new Sprite(gameState.textures.attacks.toolThrow[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->setDepth(character->sprite->z + 0.1f);
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	box->SetToolThrow(target);
	box->sprite->Activate();
}

void ToolThrowAnim::UpdateTrail()
{
	if (trail == NULL || counter < 6)
		return ;
	trail->dest = character->sprite->dest;
	int count = counter - 5;
	float unit = 255.0f / 18;
	int alpha = 255 - rounding(unit * (float)count);
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	trail->AlphaMod(alpha);
}

void ToolThrowAnim::Update()
{
	if (done)
		return ;
	int ret = mover->Update();
	counter = ret;
	UpdateTrail();
	if (ret == 4)
		CreateTrail();
	if (ret == 24)
		character->sprite->setTexture(gameState.textures.chars.smithIdle[0]);
	if (ret == (-1))
	{
		done = true;
		return ;
	}
}

void ToolThrowAnim::Destroy()
{
	character->setAnimationActive(false);
	delete trail;
	delete mover;
	box->sprite->Activate();
}
