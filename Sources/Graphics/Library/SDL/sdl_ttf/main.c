//focus on sdl

//SDL_ttf demo

//fosdl9_1.cpp
//10JUN2002
//ernest pazera

//requires static linkage to:
//sdl.lib, sdlmain.lib, sdl_ttf.lib

//requires dynamic linkage to:
//sdl.dll, sdl_ttf.dll

//include SDL stuff
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//include ability to exit program
#include <stdlib.h>

//screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//display surface
SDL_Surface *g_pDisplaySurface = NULL;

//bitmap surface
SDL_Surface *g_pTextSurface = NULL;

//font
TTF_Font *g_pFont = NULL;

//event structure
SDL_Event g_Event;
#define SDL_main main
//main function
int main(int argc, char *argv[])
{
    //initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        //error initializing SDL

        //report the error
        fprintf(stderr, "Could not initialize SDL!\n");

        //end the program
        exit(1);
    }
    else
    {
        //SDL initialized

        //report success
        fprintf(stdout, "SDL initialized properly!\n");

        //set up to uninitialize SDL at exit
        atexit(SDL_Quit);
    }

    //create windowed environment
    g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);

    //error check
    if (g_pDisplaySurface == NULL)
    {
        //report error
        // fprintf(stderr,"Could not set up display surface!\n");

        //exit the program
        exit(1);
    }

    //initialize SDL_ttf
    TTF_Init();

    //open font
    g_pFont = TTF_OpenFont("C:\\Windows\\Fonts\\consolai.ttf", 50);

    //set up color
    SDL_Color color1, color2;
    color1.r = 255;
    color1.g = 255;
    color1.b = 255;

    color2.r = 0;
    color2.g = 0;
    color2.b = 0;

    //render text
    g_pTextSurface = TTF_RenderText_Shaded(g_pFont, "Hello, world!", color1, color2);

    //rectangles
    SDL_Rect rcSrc;
    SDL_Rect rcDst;

    //source rectangle
    rcSrc.x = rcSrc.y = 0;
    rcSrc.w = g_pTextSurface->w;
    rcSrc.h = g_pTextSurface->h;

    //destination rectangle
    rcDst = rcSrc;
    rcDst.x = (SCREEN_WIDTH - rcDst.w) / 2;
    rcDst.y = (SCREEN_HEIGHT - rcDst.h) / 2;

    //blit the surface
    SDL_BlitSurface(g_pTextSurface, &rcSrc, g_pDisplaySurface, &rcDst);

    //repeat forever
    for (;;)
    {
        //wait for an event
        if (SDL_PollEvent(&g_Event) == 0)
        {
            //update the screen
            SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
        }
        else
        {
            //event occurred, check for quit
            if (g_Event.type == SDL_QUIT)
                break;
        }
    }

    //normal termination
    //fprintf(stdout,"Terminating normally.\n");

    //destroy text surface
    SDL_FreeSurface(g_pTextSurface);

    //close the font
    TTF_CloseFont(g_pFont);

    //quit SDL_ttf
    TTF_Quit();

    //return 0
    return (0);
}