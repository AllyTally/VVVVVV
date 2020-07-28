#ifndef GRAPHICSRESOURCES_H
#define GRAPHICSRESOURCES_H

#include <SDL.h>

class GraphicsResources
{
public:
    void init(void);
    void destroy(void);

    SDL_Surface* im_tiles;
    SDL_Surface* im_tiles2;
    SDL_Surface* im_tiles3;
    SDL_Surface* im_entcolours;
    SDL_Surface* im_sprites;
    SDL_Surface* im_bfont;
    SDL_Surface* im_gamelogo;
    SDL_Surface* im_about1;
    SDL_Surface* im_about2;
    SDL_Surface* im_about3;
    SDL_Surface* im_about4;
};

#endif /* GRAPHICSRESOURCES_H */
