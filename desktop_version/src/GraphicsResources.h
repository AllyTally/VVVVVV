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
};

#endif /* GRAPHICSRESOURCES_H */
