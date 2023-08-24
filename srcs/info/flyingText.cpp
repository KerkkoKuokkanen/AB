
#include "../../hdr/global.h"

FlyingSnippet::FlyingSnippet(const char *text, Vector position, Vector direction, int size, int time, int layer)
{
	snippet = new Snippet(text, FontTypes::GOOGLE_TEXT, true, {(int)position.x, (int)position.y}, size, size / 2, layer, false);
	Vector direc = direction.Normalized();
	dir.x = direc.x;
	dir.y = direc.y;
	FlyingSnippet::time = time;
	third = time * 0.33f;
	gameState.updateObjs.info->AddSnippet(this);
}

void FlyingSnippet::SetAmount(int amount)
{
	snippet->SetOutlineAmount(amount);
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

void FlyingSnippet::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	snippet->SetColor(r, g, b);
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

void FlyingSnippet::SetOrdering(int order)
{
	snippet->SetOrderLayer(order);
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
