#ifndef GRAPHICSUTIL_H
#define GRAPHICSUTIL_H

#include <SDL.h>

void setRect(SDL_Rect& _r, int x, int y, int w, int h);

SDL_Surface* GetSubSurface( SDL_Surface* metaSurface, int x, int y, int width, int height );

SDL_Color ReadPixel(const SDL_Surface* surface, int x, int y);

void FillRect(const int x, const int y, const int w, const int h, const int r, int g, int b );

void FillRect(const int r, int g, int b );

void FillRect(SDL_Rect& rect, const int r, int g, int b );

void FillRect(SDL_Rect rect, SDL_Color color);

void FillRect(SDL_Color color);

void FillRect(int x, int y, int w, int h, SDL_Color color);

void FillRect(int r, int g, int b, int a);

void UpdateFilter(void);
void ApplyFilter(void);

#endif /* GRAPHICSUTIL_H */
