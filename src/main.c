#include <SDL2/SDL.h>

#define WIN_W 640
#define WIN_H 480

typedef struct 
{
    int r;
    int g;
    int b;
} Color;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

int running = 1;

Color bg_color = { .r = 0, .g = 0, .b = 0 };
Color fg_color = { .r = 0xff, .g = 0xff, .b = 0xff };

void draw()
{
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main()
{
    if ((window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_OPENGL)) == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
        return(0);
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
        return(0);
    }
   
    if (SDL_RenderSetLogicalSize(renderer, WIN_W, WIN_H) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return(0);
    }

    SDL_RendererInfo* renderer_info = malloc(sizeof(SDL_RendererInfo));
    SDL_GetRendererInfo(renderer, renderer_info);

    printf("SDL Renderer: %s\n", renderer_info->name);

    while (running != 0)
    {
        draw();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
    }

    return 0;
}