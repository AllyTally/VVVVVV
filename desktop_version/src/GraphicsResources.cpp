#include "GraphicsResources.h"

#include "Alloc.h"
#include "FileSystemUtils.h"
#include "Vlogging.h"
#include "Screen.h"

// Used to load PNG data
extern "C"
{
    extern unsigned lodepng_decode32(
        unsigned char** out,
        unsigned* w,
        unsigned* h,
        const unsigned char* in,
        size_t insize
    );
    extern const char* lodepng_error_text(unsigned code);
}

SDL_Surface* LoadImageRaw(const char* filename, unsigned char** data)
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    unsigned int width, height;
    unsigned int error;

    unsigned char* fileIn;
    size_t length;
    FILESYSTEM_loadAssetToMemory(filename, &fileIn, &length, false);
    if (fileIn == NULL)
    {
        SDL_assert(0 && "Image file missing!");
        return NULL;
    }
    error = lodepng_decode32(data, &width, &height, fileIn, length);
    VVV_free(fileIn);

    if (error != 0)
    {
        vlog_error("Could not load %s: %s", filename, lodepng_error_text(error));
        return NULL;
    }

    loadedImage = SDL_CreateRGBSurfaceWithFormatFrom(
        *data,
        width,
        height,
        32,
        width * 4,
        SDL_PIXELFORMAT_ABGR8888
    );

    return loadedImage;
}

SDL_Surface* LoadImageSurface(const char* filename)
{
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    unsigned char* data;

    SDL_Surface* loadedImage = LoadImageRaw(filename, &data);
    if (loadedImage != NULL)
    {
        optimizedImage = SDL_ConvertSurfaceFormat(
            loadedImage,
            SDL_PIXELFORMAT_ARGB8888,
            0
        );
        VVV_freefunc(SDL_FreeSurface, loadedImage);
        VVV_free(data);
        SDL_SetSurfaceBlendMode(optimizedImage, SDL_BLENDMODE_BLEND);
        return optimizedImage;
    }
    else
    {
        VVV_free(data);
        vlog_error("Image not found: %s", filename);
        SDL_assert(0 && "Image not found! See stderr.");
        return NULL;
    }
}

SDL_Texture* LoadImage(const char *filename, const TextureLoadType loadtype)
{
    unsigned char* data;

    SDL_Surface* loadedImage = LoadImageRaw(filename, &data);

    if (loadedImage != NULL)
    {
        switch (loadtype)
        {
        case TEX_WHITE:
            SDL_LockSurface(loadedImage);
            for (int i = 0; i < loadedImage->w * loadedImage->h; i++)
            {
                Uint8 r, g, b, a;
                SDL_GetRGBA(((Uint32*)loadedImage->pixels)[i], loadedImage->format, &r, &g, &b, &a);
                ((Uint32*)loadedImage->pixels)[i] = SDL_MapRGBA(loadedImage->format, 255, 255, 255, a);
            }
            SDL_UnlockSurface(loadedImage);
            break;
        case TEX_GRAYSCALE:
            SDL_LockSurface(loadedImage);
            for (int i = 0; i < loadedImage->w * loadedImage->h; i++)
            {
                Uint8 r, g, b, a;
                SDL_GetRGBA(((Uint32*)loadedImage->pixels)[i], loadedImage->format, &r, &g, &b, &a);

                // Magic numbers used for grayscaling (eyes percieve certain colors brighter than others)
                r *= 0.299;
                g *= 0.587;
                b *= 0.114;

                const double gray = SDL_floor(r + g + b + 0.5);

                ((Uint32*)loadedImage->pixels)[i] = SDL_MapRGBA(loadedImage->format, gray, gray, gray, a);
            }
            SDL_UnlockSurface(loadedImage);
            break;
        default:
            break;
        }

        //Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface(gameScreen.m_renderer, loadedImage);
        if (texture == NULL)
        {
            vlog_error("Failed creating texture: %s. SDL error: %s\n", filename, SDL_GetError());
        }

        VVV_freefunc(SDL_FreeSurface, loadedImage);
        VVV_free(data);

        return texture;
    }
    else
    {
        VVV_free(data);
        vlog_error("Image not found: %s", filename);
        SDL_assert(0 && "Image not found! See stderr.");
        return NULL;
    }
}

SDL_Texture* LoadImage(const char* filename)
{
    return LoadImage(filename, TEX_COLOR);
}

void GraphicsResources::init(void)
{
    im_tiles            = LoadImage("graphics/tiles.png");
    im_tiles_white      = LoadImage("graphics/tiles.png", TEX_WHITE);
    im_tiles_tint       = LoadImage("graphics/tiles.png", TEX_GRAYSCALE);
    im_tiles2           = LoadImage("graphics/tiles2.png");
    im_tiles2_tint      = LoadImage("graphics/tiles2.png", TEX_GRAYSCALE);
    im_tiles3           = LoadImage("graphics/tiles3.png");
    im_entcolours       = LoadImage("graphics/entcolours.png");
    im_entcolours_tint  = LoadImage("graphics/entcolours.png", TEX_GRAYSCALE);
    im_sprites          = LoadImage("graphics/sprites.png", TEX_WHITE);
    im_flipsprites      = LoadImage("graphics/flipsprites.png", TEX_WHITE);
    im_sprites_surf     = LoadImageSurface("graphics/sprites.png");
    im_flipsprites_surf = LoadImageSurface("graphics/flipsprites.png");
    im_bfont            = LoadImage("graphics/font.png", TEX_WHITE);
    im_teleporter       = LoadImage("graphics/teleporter.png", TEX_WHITE);

    im_image0  = LoadImage("graphics/levelcomplete.png");
    im_image1  = LoadImage("graphics/minimap.png");
    im_image2  = LoadImage("graphics/covered.png");
    im_image3  = LoadImage("graphics/elephant.png");
    im_image4  = LoadImage("graphics/gamecomplete.png");
    im_image5  = LoadImage("graphics/fliplevelcomplete.png");
    im_image6  = LoadImage("graphics/flipgamecomplete.png");
    im_image7  = LoadImage("graphics/site.png");
    im_image8  = LoadImage("graphics/site2.png");
    im_image9  = LoadImage("graphics/site3.png");
    im_image10 = LoadImage("graphics/ending.png");
    im_image11 = LoadImage("graphics/site4.png");
    im_image12 = LoadImage("graphics/minimap.png");
}


void GraphicsResources::destroy(void)
{
    VVV_freefunc(SDL_DestroyTexture, im_tiles);
    VVV_freefunc(SDL_DestroyTexture, im_tiles_white);
    VVV_freefunc(SDL_DestroyTexture, im_tiles_tint);
    VVV_freefunc(SDL_DestroyTexture, im_tiles2);
    VVV_freefunc(SDL_DestroyTexture, im_tiles2_tint);
    VVV_freefunc(SDL_DestroyTexture, im_tiles3);
    VVV_freefunc(SDL_DestroyTexture, im_entcolours);
    VVV_freefunc(SDL_DestroyTexture, im_entcolours_tint);
    VVV_freefunc(SDL_DestroyTexture, im_sprites);
    VVV_freefunc(SDL_DestroyTexture, im_flipsprites);
    VVV_freefunc(SDL_DestroyTexture, im_bfont);
    VVV_freefunc(SDL_DestroyTexture, im_teleporter);

    VVV_freefunc(SDL_DestroyTexture, im_image0);
    VVV_freefunc(SDL_DestroyTexture, im_image1);
    VVV_freefunc(SDL_DestroyTexture, im_image2);
    VVV_freefunc(SDL_DestroyTexture, im_image3);
    VVV_freefunc(SDL_DestroyTexture, im_image4);
    VVV_freefunc(SDL_DestroyTexture, im_image5);
    VVV_freefunc(SDL_DestroyTexture, im_image6);
    VVV_freefunc(SDL_DestroyTexture, im_image7);
    VVV_freefunc(SDL_DestroyTexture, im_image8);
    VVV_freefunc(SDL_DestroyTexture, im_image9);
    VVV_freefunc(SDL_DestroyTexture, im_image10);
    VVV_freefunc(SDL_DestroyTexture, im_image11);
    VVV_freefunc(SDL_DestroyTexture, im_image12);

    VVV_freefunc(SDL_FreeSurface, im_sprites_surf);
    VVV_freefunc(SDL_FreeSurface, im_flipsprites_surf);
}
