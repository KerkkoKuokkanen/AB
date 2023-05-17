
#include "../../hdr/ab.h"
#include "../../hdr/global.h"

SDL_Texture	*get_texture(SDL_Renderer *rend, const char *filePath)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	SDL_SetTextureScaleMode(text, SDL_ScaleModeLinear);
	return (text);
}

SDL_Texture	*get_texture_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	SDL_SetTextureScaleMode(text, scaleMode);
	return (text);
}

t_TextAndSur	get_texture_and_surface(SDL_Renderer *rend, const char *filePath)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_SetTextureScaleMode(text, SDL_ScaleModeLinear);
	t_TextAndSur ret = {text, surface};
	return (ret);
}

float	vectorAngle(Vector v1, Vector v2)
{
	float	a, b, c;
	a = v1.x * v2.x + v1.y * v2.y;
	b = sqrt(v1.x * v1.x + v1.y * v1.y);
	c = sqrt(v2.x * v2.x + v2.y * v2.y);
	return (acos(a / (b * c)));
}

int	degree(float angle)
{
	return ((angle * 180.0f) / PI);
}

int	rounding(float value)
{
	int val = static_cast<int>(value);
	float tester = value - val;
	if (tester >= 0.5f)
		return (val + 1);
	return (val);
}

SDL_FRect	translateSprite(SDL_Rect dest, bool staticSprite)
{
	int cx = 0;
	int cy = 0;
	float w = (float)gameState.screen.width;
	float h = (float)gameState.screen.height;
	if (!staticSprite)
	{
		cx = gameState.camera.x;
		cy = gameState.camera.y;
	}
	SDL_FRect ret = {
		(float)(dest.x - cx) / gameState.screen.xPixelUnit + gameState.screen.midPointX,
		(float)(dest.y - cy) / gameState.screen.yPixelUnit * gameState.screen.aspectRatio + gameState.screen.midPointY,
		(float)dest.w / gameState.screen.xPixelUnit,
		(float)dest.h / gameState.screen.yPixelUnit * gameState.screen.aspectRatio
	};
	return (ret);
}

bool pointCheck(SDL_Point &point, SDL_Rect &hitBox)
{
	if (point.x >= hitBox.x && point.x <= (hitBox.x + hitBox.w) &&
		point.y >= hitBox.y && point.y <= (hitBox.y + hitBox.h)) {
		return (true);
	}
	return (false);
}

bool boxCheck(SDL_Rect box1, SDL_Rect box2)
{
	if (box1.x < (box2.x + box2.w) && (box1.x + box1.w) > box2.x &&
		box1.y < (box2.y + box2.h) && (box1.y + box1.h) > box2.y)
		return (true);
	return (false);
}

bool CheckInsideShape(SDL_Point up, SDL_Point left, SDL_Point down, SDL_Point right, SDL_Point target)
{
	SDL_Point vec1 = {left.x - up.x, left.y - up.y};
	SDL_Point vec2 = {down.x - left.x, down.y - left.y};
	SDL_Point vec3 = {right.x - down.x, right.y - down.y};
	SDL_Point vec4 = {up.x - right.x, up.y - right.y};
	SDL_Point vp1 = {target.x - up.x, target.y - up.y};
	SDL_Point vp2 = {target.x - left.x, target.y - left.y};
	SDL_Point vp3 = {target.x - down.x, target.y - down.y};
	SDL_Point vp4 = {target.x - right.x, target.y - right.y};
	float cross1 = vec1.x * vp1.y - vec1.y * vp1.x;
	float cross2 = vec2.x * vp2.y - vec2.y * vp2.x;
	float cross3 = vec3.x * vp3.y - vec3.y * vp3.x;
	float cross4 = vec4.x * vp4.y - vec4.y * vp4.x;
	if (cross1 * cross2 > 0.0f && cross1 * cross3 > 0.0f && cross1 * cross4 > 0.0f)
		return (true);
	return (false);
}

void CreateDust(SDL_Point position, Vector direction)
{
	gameState.updateObjs.dusts.push_back(new Dust(position, direction));
}

void PlaySound(Mix_Chunk *clip, int channel, int loops)
{
	Mix_PlayChannel(channel, clip, loops);
}

float	float_rand()
{
	float	scale = ((double)rand() / (double)(RAND_MAX));
	return (scale);
}

int	figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;
	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000);
	if (ret < 0)
		return (0);
	else
		return (ret);
}
