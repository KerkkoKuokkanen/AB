
#ifndef SPRITE_H
# define SPRITE_H

#include "../ab.h"

class Sprite
{
	private:
		SDL_Rect *srect = NULL;
		SDL_Texture *sprite = NULL;
		SDL_FPoint *point = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool staticSprite = false;
		Uint8 alpha = 255;
		bool active = true;
		bool translated = true;
		bool deleteTexture = false;
		bool scaled = true;
		bool removed = false;
	public:
		double angle = 0.0;
		float z = 0.0f;
		SDL_Rect dest = {0, 0, 0, 0};
		int spritesLayer;
		int orderLayer = 0;
		Uint8 red = 0;
		Uint8 green = 0;
		Uint8 blue = 0;
		void SetRemoved() {removed = true;};
		Sprite(SDL_Texture *sprite, SDL_Rect dest, SDL_Rect *srect, SDL_FPoint *point, const double angle, const int flip, bool staticSprite = false) {
			Sprite::sprite = sprite;
			Sprite::dest = dest;
			Sprite::srect = srect;
			Sprite::point = point;
			Sprite::angle = angle;
			if (flip == FLIP_HORIZONTAL)
				Sprite::flip = SDL_FLIP_HORIZONTAL;
			else if (flip == FLIP_VERTICAL)
				Sprite::flip = SDL_FLIP_VERTICAL;
			Sprite::staticSprite = staticSprite;
			spritesLayer = -1;
		};
		~Sprite();
		Uint8 getAlpha() {return(alpha);};
		void setSRect(SDL_Rect *srect) {Sprite::srect = srect;};
		void setScaled(bool scaled) {Sprite::scaled = scaled;};
		void setDeleteTexture(bool deleteTexture) {Sprite::deleteTexture = deleteTexture;};
		void Destroy() {delete this;};
		void Activate() {active = true;};
		void Deactivate() {active = false;};
		bool getStatus() {return (active);};
		void setTranslation(bool set) {translated = set;};
		void RemoveFromRenderer();
		void Render(SDL_Renderer *rend);
		void Move(Vector amount) {
			int xMove = amount.x;
			int yMove = amount.y;
			if (amount.x - xMove >= 0.5f)
				xMove += 1;
			if (amount.y - yMove >= 0.5f)
				yMove += 1;
			dest.x += xMove;
			dest.y += yMove;
		};
		void Position(Vector to) {
			int xMove = to.x;
			int yMove = to.y;
			if (to.x - xMove >= 0.5f)
				xMove += 1;
			if (to.y - yMove >= 0.5f)
				yMove += 1;
			dest.x = xMove;
			dest.y = yMove;
		};
		void setAngle(const double angle) {Sprite::angle = angle;};
		void addAngle(const double angle) {Sprite::angle += angle;};
		double getAngle() {return (angle);};
		void setFlip(const int flip) {
			if (flip == FLIP_HORIZONTAL)
				Sprite::flip = SDL_FLIP_HORIZONTAL;
			else if (flip == FLIP_VERTICAL)
				Sprite::flip = SDL_FLIP_VERTICAL;
			else
				Sprite::flip = SDL_FLIP_NONE;
		};
		void AlphaMod(Uint8 alpha) {Sprite::alpha = alpha;};
		void ClearAlphaMod() {Sprite::alpha = 255;};
		void ColorMod(Uint8 r, Uint8 g, Uint8 b) {red = r; green = g; blue = b;};
		void ClearColorMod() {red = 0; green = 0; blue = 0;};
		void setPortion(SDL_Rect srect) {Sprite::srect = &srect;};
		void setTexture(SDL_Texture *texture) {sprite = texture;};
		SDL_Texture *getTexture() {return (sprite);};
		void setDepth(float z) {Sprite::z = z;};
		void setPoint(SDL_FPoint point) {Sprite::point = &point;};
		void setStatic(bool staticSprite) {Sprite::staticSprite = staticSprite;};
		void setWidthAndHeight(const int width, const int height) {dest.w = width; dest.h = height;};
		void setWidth(int width) {Sprite::dest.w = width;};
		void setHeight(int height) {Sprite::dest.h = height;};
		void setDest(SDL_Rect dest) {Sprite::dest = dest;};
		void setAll(SDL_Rect *dest, SDL_Rect *srect, SDL_FPoint *point, const double *angle, const int flip){
			if (dest != NULL)
			{
				Sprite::dest.x = dest->x;
				Sprite::dest.y = dest->y;
				Sprite::dest.w = dest->w;
				Sprite::dest.h = dest->h;
			}
			if (srect != NULL)
				Sprite::srect = srect;
			if (point != NULL)
				Sprite::point = point;
			if (angle != NULL)
				Sprite::angle = *angle;
			if (flip == FLIP_HORIZONTAL)
				Sprite::flip = SDL_FLIP_HORIZONTAL;
			else if (flip == FLIP_VERTICAL)
				Sprite::flip = SDL_FLIP_VERTICAL;
			else
				Sprite::flip = SDL_FLIP_NONE;
		};
};

#endif
