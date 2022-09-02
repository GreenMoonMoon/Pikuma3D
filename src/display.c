#include "display.h"
#include <stdio.h>

SDL_Window *window;
SDL_Renderer *renderer;

int window_width;
int window_height;
uint32_t *color_buffer;
SDL_Texture *color_buffer_texture;

bool initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // Query maximum resolution of the monitor
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    // Set fullscreen
    window_width = display_mode.w;
    window_height = display_mode.h;

    // Create SDL window
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void uninitialize_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x > window_width || y > window_height) return;
    color_buffer[(y * window_width) + x] = color;
}

void draw_grid(int w, int h, uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            if (x % w == 0 || y % h == 0)
            {
                color_buffer[(y * window_width) + x] = color;
            }
        }
    }
}

void draw_point_grid(int w, int h, uint32_t color)
{
    for (int y = 0; y < window_height; y += h)
    {
        for (int x = 0; x < window_width; x += w)
        {
            color_buffer[(y * window_width) + x] = color;
        }
    }
}

// NOTE: Don't go trough the whole color_buffer, this isn't a shader. Just access the minimun amounth of index you need to display the shape.
void draw_rectangle(int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int current_x = j + x;
            int current_y = i + y;

            color_buffer[(current_y * window_width) + current_x] = color;
        }
    }
}

void render_color_buffer(void)
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(sizeof(uint32_t) * window_width));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t clear_color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            color_buffer[(y * window_width) + x] = clear_color;
        }
    }
}