#ifndef DISPLAY_H
#define DISPLAY_H

#include "triangle.h"

#include <stdbool.h>
#include "SDL.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int window_width;
extern int window_height;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

bool initialize_window(void);

void uninitialize_window(void);

void draw_pixel(int x, int y, uint32_t color);

void draw_grid(int w, int h, uint32_t color);

void draw_point_grid(int w, int h, uint32_t color);

void draw_rectangle(int x, int y, int width, int height, uint32_t color);

void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

void draw_triangle(triangle_t triangle, uint32_t color);

void render_color_buffer(void);

void clear_color_buffer(uint32_t clear_color);

#endif // DISPLAY_H