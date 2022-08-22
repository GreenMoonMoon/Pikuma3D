#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include "SDL.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int window_width;
extern int window_height;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

bool initialize_window(void);

void uninitialize_window(void);

void draw_grid(void);

void draw_point_grid(void);

void draw_rectangle(int x, int y, int width, int height, uint32_t color);

void render_color_buffer(void);

void clear_color_buffer(uint32_t clear_color);

#endif //DISPLAY_H