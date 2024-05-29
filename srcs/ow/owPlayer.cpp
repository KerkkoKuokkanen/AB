
#include "../../hdr/ow/owPlayer.h"
#include "../../hdr/ow/owHeader.h"
#include "../../hdr/ow/owKeys.h"
#include "../../hdr/ow/owAudio.h"

long findLargest(long a, long b, long c, long d)
{
	long largest = std::numeric_limits<long>::min();;
	if (a != 0 && a > largest)
		largest = a;
	if (b != 0 && b > largest)
		largest = b;
	if (c != 0 && c > largest)
		largest = c;
	if (d != 0 && d > largest)
		largest = d;
	return (largest);
}

static int GetMoveDirection() // 0 = no key 1 = left, 2 = right, 3 = up, 4 = down
{
	static long left = 0;
	static long right = 0;
	static long up = 0;
	static long down = 0;
	left = (owKeys.left == 0) ? 0 : left - 1;
	right = (owKeys.right == 0) ? 0 : right - 1;
	up = (owKeys.up == 0) ? 0 : up - 1;
	down = (owKeys.down == 0) ? 0 : down - 1;
	if (left == 0 && right == 0 && up == 0 && down == 0)
		return (0);
	long largest = findLargest(left, right, up, down);
	if (largest == left)
		return (1);
	if (largest == right)
		return (2);
	if (largest == up)
		return (3);
	return (4);
}

Player::Player(SDL_Point pos)
{
	current = {pos.x, pos.y};
	last = current;
	sprite = new Sprite(owState.textures.mule, {DIMENTIONS * pos.x, DIMENTIONS * pos.y, DIMENTIONS, DIMENTIONS}, NULL, NULL, 0, FLIP_NONE);
	sprite->orderLayer = 2;
	owState.renderer->AddSprite(sprite, TILE_LAYER);
	SDL_Point startPosition = {pos.x * DIMENTIONS + DIMENTIONS / 2, pos.y * DIMENTIONS + DIMENTIONS / 2};
	gameCamera.x = startPosition.x;
	gameCamera.y = startPosition.y;
}

void Player::MovePlayer()
{
	int direction = GetMoveDirection();
	if (direction == 0)
		return ;
	if (moveDelayer > 0)
		return ;
	bool gotIt = false;
	if (direction == 1)
	{
		sprite->setFlip(FLIP_NONE);
		gotIt = SetBGPosition(current.x - 1, current.y, delayTime + 12);
	}
	else if (direction == 2)
	{
		sprite->setFlip(FLIP_HORIZONTAL);
		gotIt = SetBGPosition(current.x + 1, current.y, delayTime + 12);
	}
	else if (direction == 3)
		gotIt = SetBGPosition(current.x, current.y - 1, delayTime + 12);
	else if (direction == 4)
		gotIt = SetBGPosition(current.x, current.y + 1, delayTime + 12);
	SDL_Point pos = GetBGPosition();
	current = {pos.x, pos.y};
	SDL_Point endPos = {DIMENTIONS * pos.x, DIMENTIONS * pos.y};
	if (gotIt)
	{
		PlaySound(owAudio.owSteps[0], OwChannels::VOLUME_16, 0);
		PlaySound(owAudio.owSteps[1], OwChannels::VOLUME_12, 0);
		moveDelayer = delayTime;
		if (mover != NULL)
			delete mover;
		mover = new OwSpriteMover(sprite, {sprite->dest.x, sprite->dest.y}, endPos, moveDelayer + 2);
		OwCameraHandler *handler = GetReferenceToCamHandler();
		handler->SetBaseMove({sprite->dest.x + 1600, sprite->dest.y + 1600}, {endPos.x + 1600, endPos.y + 1600}, moveDelayer);
	}
}

void Player::Update()
{
	MovePlayer();
	if (mover != NULL)
	{
		mover->Update();
		if (mover->done)
		{
			delete mover;
			mover = NULL;
		}
	}
	if (moveDelayer > 0)
		moveDelayer--;
}

void Player::Destroy()
{
	if (sprite != NULL)
		delete sprite;
}
