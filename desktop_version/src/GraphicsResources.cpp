#include "GraphicsResources.h"

#include <stdio.h>
#include <stdlib.h>

#include "FileSystemUtils.h"

// Used to load PNG data
extern "C"
{
	extern unsigned lodepng_decode24(
		unsigned char** out,
		unsigned* w,
		unsigned* h,
		const unsigned char* in,
		size_t insize
	);
	extern unsigned lodepng_decode32(
		unsigned char** out,
		unsigned* w,
		unsigned* h,
		const unsigned char* in,
		size_t insize
	);
}

SDL_Surface* LoadImage(const char *filename, bool noBlend = true, bool noAlpha = false)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	unsigned char *data;
	unsigned int width, height;

	unsigned char *fileIn = NULL;
	size_t length = 0;
	FILESYSTEM_loadFileToMemory(filename, &fileIn, &length);
	if (noAlpha)
	{
		lodepng_decode24(&data, &width, &height, fileIn, length);
	}
	else
	{
		lodepng_decode32(&data, &width, &height, fileIn, length);
	}
	FILESYSTEM_freeMemory(&fileIn);

	loadedImage = SDL_CreateRGBSurfaceFrom(
		data,
		width,
		height,
		noAlpha ? 24 : 32,
		width * (noAlpha ? 3 : 4),
		0x000000FF,
		0x0000FF00,
		0x00FF0000,
		noAlpha ? 0x00000000 : 0xFF000000
	);

	if (loadedImage != NULL)
	{
		optimizedImage = SDL_ConvertSurfaceFormat(
			loadedImage,
			SDL_PIXELFORMAT_ABGR8888, // FIXME: Format? -flibit
			0
		);
		SDL_FreeSurface( loadedImage );
		free(data);
		if (noBlend)
		{
			SDL_SetSurfaceBlendMode(optimizedImage, SDL_BLENDMODE_BLEND);
		}
		return optimizedImage;
	}
	else
	{
		fprintf(stderr,"Image not found: %s\n", filename);
		SDL_assert(0 && "Image not found! See stderr.");
		return NULL;
	}
}

void GraphicsResources::init(void)
{
	im_tiles =		LoadImage("graphics/tiles.png");
	im_tiles2 =		LoadImage("graphics/tiles2.png");
	im_tiles3 =		LoadImage("graphics/tiles3.png");
	im_entcolours =		LoadImage("graphics/entcolours.png");
	im_sprites =		LoadImage("graphics/sprites.png");
	im_bfont =		LoadImage("graphics/font.png");
	im_gamelogo =	LoadImage("graphics/gamelogo.png");
	im_about1 =	LoadImage("graphics/vvvvvv1.png");
	im_about2 =	LoadImage("graphics/vvvvvv2.png");
	im_about3 =	LoadImage("graphics/vvvvvv3.png");
	im_about4 =	LoadImage("graphics/vvvvvv4.png");
}


void GraphicsResources::destroy(void)
{
#define CLEAR(img) \
	SDL_FreeSurface(img); \
	img = NULL;

	CLEAR(im_tiles);
	CLEAR(im_tiles2);
	CLEAR(im_tiles3);
	CLEAR(im_entcolours);
	CLEAR(im_sprites);
	CLEAR(im_bfont);
	CLEAR(im_gamelogo);
	CLEAR(im_about1);
	CLEAR(im_about2);
	CLEAR(im_about3);
	CLEAR(im_about4);
#undef CLEAR
}
