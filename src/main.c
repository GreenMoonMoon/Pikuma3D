#include <stdio.h>
#include "display.h"
#include "vector.h"
#include "camera.h"
#include "mesh.h"
#include "triangle.h"

vec3_t cube_rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

// mesh data processed for rendering
vec3_t transformed_mesh_vertices[MESH_VERTEX_COUNT];
triangle_t projected_mesh_faces[MESH_FACE_COUNT];

// Camera
camera_t camera = {
    .position = {.x = 0.0f, .y = 0.0f, .z = -5.0f},
    .rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .fov = 640.0f};

// Game variables
bool is_running = false;
int previous_frame_time;

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
    int remaining_time = FRAME_TARGET_TIME - (previous_frame_time - SDL_GetTicks());
    if (remaining_time > 0 && remaining_time <= FRAME_TARGET_TIME)
        SDL_Delay(remaining_time);

    previous_frame_time = SDL_GetTicks();

    // Update cube rotation
    cube_rotation.x += 0.01f;
    cube_rotation.y += 0.005f;
    cube_rotation.z += 0.02f;

    // Tranform each vertex
    for (int i = 0; i < MESH_VERTEX_COUNT; i++)
    {
        vec3_t vertex = cube_vertices[i];

        // Rotate the point around the Y axis
        vec3_t transformed_vertex = vec3_rotate_x(vertex, cube_rotation.x);
        transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
        transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

        // Translate the point away from the camera
        transformed_vertex.z -= camera.position.z;

        transformed_mesh_vertices[i] = transformed_vertex;
    }

    // For each face, project its vertices
    for (int i = 0; i < MESH_FACE_COUNT; i++)
    {
        face_t face = cube_faces[i];

        triangle_t triangle;
        // Project the point on the screen
        for (int j = 0; j < 3; j++)
        {
            triangle.points[j] = project(transformed_mesh_vertices[face.indices[j]]);
            triangle.points[j].x += (window_width * 0.5f);
            triangle.points[j].y += (window_height * 0.5f);
        }
        projected_mesh_faces[i] = triangle;
    }
}

void render(void)
{
    // draw_grid();
    draw_point_grid(100, 100, 0xFFAAAAAA);
    // draw_rectangle(100, 100, 300, 200, 0xFF9922F0);

    for (int i = 0; i < MESH_FACE_COUNT; i++)
    {
        triangle_t triangle = projected_mesh_faces[i];
        draw_triangle(triangle, 0xFFFFFF00);
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