
#include "../../../hdr/global.h"

static Vector GetDirection(SDL_Point cPoint, SDL_Point tPoint)
{
	SDL_Rect dest1 = gameState.battle.ground->getTileDest(cPoint);
	SDL_Rect dest2 = gameState.battle.ground->getTileDest(tPoint);
	Vector dir((float)(dest2.x - dest1.x), (float)(dest2.y - dest1.y));
	dir = dir.Normalized();
	return (dir);
}

AcidBombAnim::AcidBombAnim(Character *character, SDL_Point target, t_Ability *ability)
{
	AcidBombAnim::character = character;
	AcidBombAnim::target = target;
	AcidBombAnim::ability = ability;
	character->setAnimationActive(true);
	Vector moverDirection = GetDirection(character->position, target);
	if (moverDirection.x < 0.0f)
		angleAddition = -angleAddition;
	mover = new CharacterMover(character, moverDirection, 12, 12, 200.0f);
}

static float GetHeightForThrow(SDL_Point start, SDL_Point end)
{
	Vector mag((float)(end.x - start.x), (float)(end.y - start.y));
	float magnitude = mag.Magnitude();
	if (magnitude < 6000.0f)
		return (3500.0f);
	if (magnitude > 18000.0f)
		return (15000.0f);
	float unit = 14000.0f / 18000.0f;
	float amount = unit * magnitude;
	return (amount);
}

void AcidBombAnim::StartThrow()
{
	PlaySound(gameState.audio.toolThrow, Channels::TOOL_THROW, 0);
	character->sprite->dest.x += 200;
	character->sprite->setTexture(gameState.textures.attacks.alchemistThrow[0]);
	trail = new Sprite(gameState.textures.attacks.alchemistThrow[1], character->sprite->dest, NULL, NULL, 0, FLIP_NONE);
	trail->orderLayer = character->sprite->orderLayer;
	trail->z = character->sprite->z - 0.04f;
	gameState.render->AddSprite(trail, BATTLEGROUND_LAYER);
	bombCreated = true;
	SDL_Rect bombDest = {character->sprite->dest.x + 4700, character->sprite->dest.y + 1600, 1650, 1650};
	bomb = new Sprite(gameState.textures.attacks.bombs[1], bombDest, NULL, NULL, 0, FLIP_NONE);
	gameState.render->AddSprite(bomb, OBJECT_LAYER);
	SDL_Rect dst = gameState.battle.ground->getTileDest(target);
	dst.x += 1800;
	dst.y += 1000;
	arch = new ThrowArch(bomb, {bomb->dest.x, bomb->dest.y}, {dst.x, dst.y},
						GetHeightForThrow({bomb->dest.x, bomb->dest.y}, {dst.x, dst.y}), 360.0f);
}

void AcidBombAnim::UpdateBomb()
{
	if (bomb == NULL)
		return ;
	if (arch == NULL)
		return ;
	arch->Update();
	bomb->addAngle(angleAddition);
	if (arch->done)
	{
		PlaySound(gameState.audio.acidBomb[0], Channels::VOLUME_55, 0);
		PlaySound(gameState.audio.acidBomb[1], Channels::VOLUME_9, 0);
		PlaySound(gameState.audio.acidBomb[2], Channels::VOLUME_26, 0);
		SetScreenShake(200, 6);
		SDL_Point pos = {bomb->dest.x + 800, bomb->dest.y + 400};
		t_DamageBomb *used = (t_DamageBomb*)ability->stats;
		new AcidBombBlast(pos, used->version);
		delete arch;
		delete bomb;
		arch = NULL;
		bomb = NULL;
	}
}

void AcidBombAnim::UpdateTrail(int ret)
{
	if (trail == NULL)
		return ;
	trail->dest = character->sprite->dest;
	int count = ret - 5;
	if (count == 17)
	{
		delete trail;
		trail = NULL;
		character->sprite->setTexture(gameState.textures.chars.AlchemistIdle[0]);
		return ;
	}
	float unit = 255.0f / 17.0f;
	float alpha	= 255.0f - unit * (float)count;
	int used = rounding(alpha);
	trail->AlphaMod(used);
}

void AcidBombAnim::UpdateMover()
{
	if (mover == NULL)
		return ;
	int ret = mover->Update();
	UpdateTrail(ret);
	if (ret == 5)
		StartThrow();
	if (ret == (-1))
	{
		delete mover;
		mover = NULL;
		character->sprite->setTexture(gameState.textures.chars.AlchemistIdle[0]);
		character->setAnimationActive(false);
	}
}

void AcidBombAnim::Update()
{
	createDamage = false;
	if (done)
		return ;
	if (bombCreated && bomb == NULL && damageCreated == false)
	{
		createDamage = true;
		damageCreated = true;
	}
	if (CheckIfDone())
	{
		done = true;
		return ;
	}
	UpdateMover();
	UpdateBomb();
	counter++;
	if (counter > 300)
	{
		done = true;
		createDamage = true;
	}
}

bool AcidBombAnim::CheckIfDone()
{
	if (mover == NULL && arch == NULL && bomb == NULL)
		return (true);
	return (false);
}

void AcidBombAnim::Destroy()
{
	if (trail != NULL)
		delete trail;
	if (mover != NULL)
		delete mover;
	if (arch != NULL)
		delete arch;
	if (bomb != NULL)
		delete bomb;
	character->setAnimationActive(false);
}
