#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

int main()
{

    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize. Error: %s\n", SDL_GetError());
        return -1;
    }    

    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *img = IMG_LoadTexture(renderer, "assets/test.png");
    if (img == NULL)
    {
        printf("Couldn't load image. SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    int w, h;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect r;
    r.x = (SCREEN_WIDTH - w)/2; r.y = (SCREEN_HEIGHT - h)/2; r.w = w; r.h = h;

    while (1) 
    {
        SDL_Event e;
        if (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;

            SDL_RenderCopy(renderer, img, NULL, &r);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}


