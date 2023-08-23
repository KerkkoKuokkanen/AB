
#include "../../hdr/global.h"

FlyingSnippet::FlyingSnippet(const char *text, Vector position, Vector direction, int size, int time)
{
	snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {(int)position.x, (int)position.y}, size, size / 2, TEXT_LAYER, false);
	snippet->SetScaled(false);
	Vector direc = direction.Normalized();
	dir.x = direc.x;
	dir.y = direc.y;
	FlyingSnippet::time = time;
	third = time * 0.33f;
}

void FlyingSnippet::ManageAlpha()
{
	if (time > third)
		return ;
	float unit = 255.0f / (float)third;
	float alpha = unit * (float)time;
	int used = rounding(alpha);
	if (used > 255)
		used = 255;
	if (used < 0)
		used = 0;
	snippet->SetAlphaMod(used);
}

void FlyingSnippet::ManageMovement()
{
	Vector direc(dir.x, dir.y);
	direc.x += xAdd;
	direc.y += yAdd;
	direc = direc.Normalized();
	speed /= drag;
	snippet->Move(Vector(direc.x * speed, direc.y * speed));
}

void FlyingSnippet::Update()
{
	if (done)
		return ;
	ManageMovement();
	ManageAlpha();
	if (time <= 0)
		done = true;
	time--;
}

void FlyingSnippet::Destroy()
{
	delete snippet;
}
