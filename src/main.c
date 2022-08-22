#include <stdio.h>
#include "display.h"

bool is_running = false;

void setup(void)
{
    // Allocate memory for color_buffer
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    if (!color_buffer)
    {
        fprintf(stderr, "Error allocating the color buffer.\n");
    }

    // Create the SDL texture used to display the color_buffer
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}

void teardown(void)
{
    free(color_buffer);
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            is_running = false;
        }
        break;
    }
}

void update(void)
{
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
    SDL_RenderClear(renderer);

    // draw_grid();
    // draw_point_grid();
    draw_rectangle(100, 100, 300, 200, 0xFF9922F0);

    render_color_buffer();
    clear_color_buffer(0x00000000);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *args[])
{

    // Initialize window and renderer
    is_running = initialize_window();

    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }

    teardown();

    uninitialize_window();
    return 0;
}