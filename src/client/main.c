#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

struct context {
    SDL_Rect r;
    SDL_Renderer *renderer;
    SDL_Texture *img;
    bool should_quit;
};

void main_loop(void *context) 
{
    struct context *ctx = (struct context *)context;
    SDL_Event e;
    if (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT) {
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            ctx->should_quit = true;
            return;
        }               
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            ctx->should_quit = true;
            return;
        }

        SDL_Keycode key = e.key.keysym.sym;

        if (key == SDLK_w) { ctx->r.y -= 10; }
        if (key == SDLK_s) { ctx->r.y += 10; }
        if (key == SDLK_a) { ctx->r.x -= 10; }
        if (key == SDLK_d) { ctx->r.x += 10; }

        SDL_RenderClear(ctx->renderer);
        SDL_RenderCopy(ctx->renderer, ctx->img, NULL, &ctx->r);
        SDL_RenderPresent(ctx->renderer);
    }
}

int main()
{

    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize. Error: %s\n", SDL_GetError());
        return -1;
    }    

    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

    window = SDL_CreateWindow("Mage Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *img = IMG_LoadTexture(renderer, "assets/wiz.png");
    if (img == NULL)
    {
        printf("Couldn't load image. SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    int w, h;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect r;
    r.x = (SCREEN_WIDTH - w)/2; r.y = (SCREEN_HEIGHT - h)/2; r.w = w; r.h = h;

    struct context ctx = {.img = img, .r = r, .renderer = renderer, .should_quit = false};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, &ctx, -1, 1);
#else
    while (!ctx.should_quit)
    {
        main_loop(&ctx);
    }
#endif
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}


