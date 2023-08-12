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
SDL_Rect pattern_rect = {
    .w = 0x20,
    .h = 0x20
};

int running = 1;
int pattern_boundary = PATTERN_SIZE << 5;
int pattern[PATTERN_SIZE] = {
    0x08,
    0x10,
    0x3c,
    0x5e,
    0x4e,
    0x66,
    0x3c,
    0x00
};

Color bg_color = { .r = 0xff, .g = 0xff, .b = 0xff };
Color fg_color = { .r = 0xb2, .g = 0xb2, .b = 0xb2 };

void toggle_bit(int x, int y)
{
    pattern[y] ^= 1 << x;
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);

    pattern_rect.y = 0;

    for (int i = 0; i < PATTERN_SIZE; i++)
    {
        pattern_rect.x = (PATTERN_SIZE - 1) << 5;

        for (int j = 0; j < PATTERN_SIZE; j++)
        {
            if ((pattern[i] >> j) & 1)
            {
                SDL_SetRenderDrawColor(renderer, fg_color.r, fg_color.g, fg_color.b, 0xff);
            }
            else 
            {
                SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 0xff);
            }

            SDL_RenderFillRect(renderer, &pattern_rect);

            pattern_rect.x -= 0x20;
        }

        pattern_rect.y += 0x20;

        printf("%02x ", pattern[i]);
    }

    printf("\n");

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

    draw();

    while (running != 0)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        char within_x = event.button.x >= 0 && event.button.x <= pattern_boundary;
                        char within_y = event.button.y >= 0 && event.button.y <= pattern_boundary;

                        if (within_x && within_y)
                        {
                            int y = event.button.y >> 5;
                            int x = (pattern_boundary - event.button.x) >> 5;

                            toggle_bit(x, y);
                            draw();
                        }
                    }
            }
        }
    }

    return 0;
}