#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

FILE                   *fp;
SDL_Surface            *screen;
const int width  = 640;
const int height = 480;

void QuitSdl(SDL_Event event);
SDL_Surface* SDL_ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
// int ThreadCallBack(void *para);


int ShowImage(const char* filename)
{
    const SDL_VideoInfo    *monitor;
    SDL_Surface            *background;
    SDL_Surface            *ground;
    SDL_Event              event;
    SDL_Thread             *thread = NULL;

    void                   *param;
    
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Coundnot init SDL\n");
        exit(1);
    }
    
    monitor    = SDL_GetVideoInfo();
    screen     = SDL_SetVideoMode(width, height, 24, SDL_SWSURFACE);    
    background = IMG_Load(filename);;
    ground     = SDL_ScaleSurface(background, width, height); 
    SDL_BlitSurface(ground, NULL, screen, NULL);
    SDL_Flip(screen);

    // getchar();
    return 0;
}



Uint32 ReadPixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;
			break;

		case 2:
			return *(Uint16 *)p;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			return *(Uint32 *)p;
			break;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

SDL_Surface* SDL_ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
          SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
                                                          Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

         double    _stretch_factor_x = ((double)Width / (double)(Surface->w)),
            _stretch_factor_y = ((double)(Height) / (double)(Surface->h));

        for(Sint32 y = 0; y < Surface->h; y++) //Run across all Y pixels.
            for(Sint32 x = 0; x < Surface->w; x++) //Run across all X pixels.
                for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y) //Draw _stretch_factor_y pixels for each Y pixel.
                    for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x) //Draw _stretch_factor_x pixels for each X pixel.
                        DrawPixel(_ret, (Sint32)(_stretch_factor_x * x) + o_x, 
                                                         (Sint32)(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));

        return _ret;
}

