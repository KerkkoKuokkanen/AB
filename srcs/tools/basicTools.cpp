
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

t_TextAndSur	get_texture_and_surface_with_scale_mode(SDL_Renderer *rend, const char *filePath, SDL_ScaleMode scaleMode)
{
	SDL_Surface	*surface = IMG_Load(filePath);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, surface);
	SDL_SetTextureScaleMode(text, scaleMode);
	t_TextAndSur ret = {text, surface};
	return (ret);
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

void vectorRotate(Vector &vec, float angle)
{
	float x = vec.x * cos(angle) - vec.y * sin(angle);
	float y = vec.x * sin(angle) + vec.y * cos(angle);
	vec.x = x;
	vec.y = y;
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

Vector GetCharacterTopMid(Character *character)
{
	SDL_Surface *sur = getSurface(character);
	Uint32 *pixels = (Uint32*)sur->pixels;
	float x = character->sprite->dest.x + (character->sprite->dest.w / 2);
	int yStop = 0;
	bool broke = false;
	for (int i = 0; i < sur->h; i++)
	{
		for (int j = 0; j < sur->w; j++)
		{
			if (pixels[(i * sur->w) + j] == 0)
				continue ;
			broke = true;
			yStop = i;
			break ;
		}
		if (broke)
			break ;
	}
	if (!broke)
		return (Vector(x, (float)character->sprite->dest.y));
	float hUnit = (float)character->sprite->dest.h / (float)sur->h;
	float y = (float)character->sprite->dest.y + (hUnit * (float)yStop);
	return (Vector(x, y));
}

SDL_FRect	staitcTranslateSprite(SDL_Rect dest)
{
	float xUnit = gameState.screen.xStaticUnit;
	float yUnit = gameState.screen.yStaticUnit;
	SDL_FRect ret = {
		(float)dest.x / xUnit + (float)gameState.screen.midPointX,
		(float)dest.y / yUnit + (float)gameState.screen.midPointY,
		(float)dest.w / xUnit,
		(float)dest.h / yUnit * ASPECT_MULTI
	};
	return (ret);
}

SDL_FRect	translateSprite(SDL_Rect dest)
{
	SDL_FRect ret = {
		(float)(dest.x - gameState.camera.x + gameState.screenShake.xShake) / gameState.screen.xPixelUnit + gameState.screen.midPointX,
		(float)(dest.y - gameState.camera.y + gameState.screenShake.yShake) / gameState.screen.yPixelUnit * gameState.screen.aspectRatio + gameState.screen.midPointY,
		(float)dest.w / gameState.screen.xPixelUnit,
		(float)dest.h / gameState.screen.yPixelUnit * gameState.screen.aspectRatio
	};
	return (ret);
}

bool modPointCheck(SDL_Point &point, SDL_Rect &hitBox)
{
	SDL_Rect hb = hitBox;
	hb.h = rounding((float)hb.h * gameState.screen.aspectRatio);
	if (point.x >= hb.x && point.x <= (hb.x + hb.w) &&
		point.y >= hb.y && point.y <= (hb.y + hb.h)) {
		return (true);
	}
	return (false);
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

Vector getDirection(Vector generalDir)
{
	int randAssigner = rand() % 12;
	float angle = 0.0f;
	if (randAssigner < 4)
		angle = float_rand() * (PI / 8.0f);
	else if (randAssigner < 6)
		angle = float_rand() * (PI / 6.0f);
	else if (randAssigner < 8)
		angle = float_rand() * (PI / 4.0f);
	else if (randAssigner < 10)
		angle = float_rand() * PI;
	else
		angle = float_rand() * PI * 2.0f;
	angle = (rand() % 2 == 0) ? angle : angle * (-1.0f);
	float x = generalDir.x * cos(angle) - generalDir.y * sin(angle);
	float y = generalDir.x * sin(angle) + generalDir.y * cos(angle);
	return (Vector(x, y));
}

SDL_Surface *getSurface(Character *character)
{
	int text = character->currentTexture;
	switch (character->cSing)
	{
		case THIEF:
			if (text == 0)
				return (gameState.surfaces.thiefIdle1);
			else
				return (gameState.surfaces.thiefIdle2);
		case SKELE:
			if (text == 0)
				return (gameState.surfaces.skeleIdle1);
			else
				return (gameState.surfaces.skeleIdle2);
		case PYRO:
			if (text == 0)
				return (gameState.surfaces.pyroIdle1);
			else
				return (gameState.surfaces.pyroIdle2);
	}
	return (NULL);
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

t_GMU *getMapTopRight(SDL_Point pos)
{
	if (pos.y <= 0)
		return (NULL);
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	if (pos.x + modder >= gameState.battle.ground->map.size())
		return (NULL);
	return (&gameState.battle.ground->map[pos.y - 1][pos.x + modder]);
}

t_GMU *getMapTopLeft(SDL_Point pos)
{
	if (pos.y <= 0)
		return (NULL);
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	if (pos.x + modder < 0)
		return (NULL);
	return (&gameState.battle.ground->map[pos.y - 1][pos.x + modder]);
}

t_GMU *getMapDownRight(SDL_Point pos)
{
	if (pos.y + 1 >= gameState.battle.ground->map.size())
		return (NULL);
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	if (pos.x + modder >= gameState.battle.ground->map.size())
		return (NULL);
	return (&gameState.battle.ground->map[pos.y + 1][pos.x + modder]);
}

t_GMU *getMapDownLeft(SDL_Point pos)
{
	if (pos.y + 1 >= gameState.battle.ground->map.size())
		return (NULL);
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	if (pos.x + modder < 0)
		return (NULL);
	return (&gameState.battle.ground->map[pos.y + 1][pos.x + modder]);
}

int getXToRight(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? 0 : 1;
	return (pos.x + modder);
}

int getXToLeft(SDL_Point pos)
{
	int modder = (pos.y % 2 == 0) ? -1 : 0;
	return (pos.x + modder);
}

int	figure_the_delay(clock_t start, clock_t end)
{
	double	time;
	int		ret;
	time = 0.0;
	time += (double)(end - start) / CLOCKS_PER_SEC;
	ret = FRAME - (int)(time * 1000.0f);
	if (ret < 0)
		return (0);
	else
		return (ret);
}
