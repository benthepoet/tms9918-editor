#include <SDL2/SDL.h>

#define WIN_W 640
#define WIN_H 480
#define PATTERN_SIZE 8

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
int pattern[PATTERN_SIZE] = {
    0x00,
    0x00,
    0x04,
    0x06,
    0xff,
    0x06,
    0x04,
    0x00
};

Color bg_color = { .r = 0xff, .g = 0xff, .b = 0xff };
Color fg_color = { .r = 0xb2, .g = 0xb2, .b = 0xb2 };

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = 0x20;
    rect.h = 0x20;

    for (int i = 0; i < PATTERN_SIZE; i++)
    {
        rect.x = (PATTERN_SIZE - 1) * rect.w;
        rect.y = i * rect.h;

        for (int j = 0; j < PATTERN_SIZE; j++)
        {
            int k = (pattern[i] >> j) & 1;
            int e = pattern[i] >> j;
            printf("%d, %d, %d\n", rect.x, rect.y, e);

            if (k)
            {
                SDL_SetRenderDrawColor(renderer, fg_color.r, fg_color.g, fg_color.b, 0xff);
            }
            else 
            {
                SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 0xff);
            }

            SDL_RenderFillRect(renderer, &rect);

            rect.x -= 0x20;
        }
    }

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

        SDL_Delay(2000);

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