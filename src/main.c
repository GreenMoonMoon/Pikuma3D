#include <stdio.h>
#include "display.h"
#include "vector.h"
#include "camera.h"

/// Cube points cloud
#define NUMBER_OF_POINTS (9 * 9 * 9)
vec3_t cube_points[NUMBER_OF_POINTS];
vec2_t projected_points[NUMBER_OF_POINTS];

camera_t camera = {
    .position = {.x = 0.0f, .y = 0.0f, .z = -5.0f},
    .rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .fov = 640.0f
};

vec3_t cube_rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

bool is_running = false;

/// @brief Take a 3D vector and returns a projected point
/// @param point 3D vector representing a position in space
/// @return 2D point
vec2_t project(const vec3_t point)
{
    vec2_t projected_point = {
        .x = (camera.fov * point.x) / point.z,
        .y = (camera.fov * point.y) / point.z};
    return projected_point;
}

void setup(void)
{
    // Color format: ARGB
    // Allocate memory for color_buffer
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    if (!color_buffer)
    {
        fprintf(stderr, "Error allocating the color buffer.\n");
    }

    // Create the SDL texture used to display the color_buffer
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

    int cube_count = 0;
    const float factor = 2.0f / 9.0f;
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            for (int z = 0; z < 9; z++)
            {
                vec3_t point = {.x = x * factor - 1.0f,
                                .y = y * factor - 1.0f,
                                .z = z * factor - 1.0f};
                cube_points[cube_count++] = point;
            }
        }
    }
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
    //Update cube rotation
    cube_rotation.x += 0.01f;
    cube_rotation.y += 0.005f;
    cube_rotation.z += 0.02f;

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        // Get the point to process
        vec3_t point = cube_points[i];

        // Rotate the point around the Y axis
        vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
        transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

        // Translate the point away from the camera
        transformed_point.z -= camera.position.z;

        // Project the point on the screen        
        projected_points[i] = project(transformed_point);
    }
}

void render(void)
{
    // draw_grid();
    draw_point_grid(100, 100, 0xFFAAAAAA);
    // draw_rectangle(100, 100, 300, 200, 0xFF9922F0);

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        vec2_t projected_point = projected_points[i];

        draw_rectangle(
            projected_point.x + (window_width * 0.5f),
            projected_point.y + (window_height * 0.5f),
            5,
            5,
            0xFFFFFF00);
    }

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