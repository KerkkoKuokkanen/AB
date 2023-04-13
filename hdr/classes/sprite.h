
#ifndef SPRITE_H
# define SPRITE_H

#include "../ab.h"

class Sprite
{
	private:
		double angle = 0.0;
		SDL_Rect *srect = NULL;
		SDL_Texture *sprite = NULL;
		SDL_FPoint *point = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool staticSprite = false;
	public:
		SDL_Rect dest = {0, 0, 0, 0};
		int spritesLayer;
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
		void RemoveFromRenderer();
		void Render(SDL_Renderer *rend) {
			SDL_FRect rect = translateSprite(dest, staticSprite);
			SDL_RenderCopyExF(rend, sprite, srect, &rect, angle, NULL, flip);
		};
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
		void setFlip(const int flip) {
			if (flip == FLIP_HORIZONTAL)
				Sprite::flip = SDL_FLIP_HORIZONTAL;
			else if (flip == FLIP_VERTICAL)
				Sprite::flip = SDL_FLIP_VERTICAL;
			else
				Sprite::flip = SDL_FLIP_NONE;
		};
		void setPortion(SDL_Rect srect) {Sprite::srect = &srect;};
		void setPoint(SDL_FPoint point) {Sprite::point = &point;};
		void setStatic(bool staticSprite) {Sprite::staticSprite = staticSprite;};
		void setWidthAndHeight(const int width, const int height) {dest.w = width; dest.h = height;};
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
