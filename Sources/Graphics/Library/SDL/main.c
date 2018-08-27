#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
int main(int argc, char **argv)
{
	// initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	// make sure SDL cleans up before exit
	atexit(SDL_Quit);

	// create a new window
	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16,
										   SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!screen)
	{
		printf("Unable to set 640x480 video: %s\n", SDL_GetError());
		return 1;
	}

	// load an image
	SDL_Surface *bmp = IMG_Load(argv[1]);
	if (!bmp)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}

	// centre the bitmap on screen
	SDL_Rect dstrect;
	dstrect.x = (screen->w - bmp->w) / 2;
	dstrect.y = (screen->h - bmp->h) / 2;

	// program main loop
	int done = 0;
	while (!done)
	{
		// message processing loop
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// check for messages
			switch (event.type)
			{
				// exit if the window is closed
			case SDL_QUIT:
				done = 1;
				break;

				// check for keypresses
			case SDL_KEYDOWN:
			{
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = 1;
				break;
			}
			} // end switch
		}	 // end of message processing

		// DRAWING STARTS HERE

		// clear screen
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

		// draw bitmap
		SDL_BlitSurface(bmp, 0, screen, &dstrect);

		// DRAWING ENDS HERE

		// finally, update the screen :)
		SDL_Flip(screen);
	} // end main loop

	// free loaded bitmap
	SDL_FreeSurface(bmp);

	// all is well ;)
	printf("Exited cleanly\n");
	return 0;
}
