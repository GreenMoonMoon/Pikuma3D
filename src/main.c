#include <stdio.h>
#include "display.h"
#include "vector.h"
#include "camera.h"
#include "mesh.h"
#include "triangle.h"
#include "array.h"

// mesh data processed for rendering
vec3_t *transformed_mesh_vertices = NULL;
triangle_t *projected_mesh_faces = NULL;

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
    // Load the cube mesh into the mesh global
    // load_cube_mesh();
    load_obj_file("C:/Users/josue/Projects/Pikuma3D/assets/objs/cube.obj");

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
    // Free resources
    free(color_buffer);
    array_free(mesh.vertices);
    array_free(mesh.faces);
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

    transformed_mesh_vertices = NULL;
    projected_mesh_faces = NULL;
    

    // Update cube rotation
    mesh.rotation.z += 0.02f;
    mesh.rotation.x += 0.01f;
    mesh.rotation.y += 0.005f;

    // Tranform each vertex
    for (int i = 0; i < array_length(mesh.vertices); i++)
    {
        vec3_t vertex = mesh.vertices[i];

        // Rotate the point around the Y axis
        vec3_t transformed_vertex = vec3_rotate_x(vertex, mesh.rotation.x);
        transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
        transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

        // Translate the point away from the camera
        transformed_vertex.z -= camera.position.z;

        array_push(transformed_mesh_vertices, transformed_vertex);
    }

    // For each face, project its vertices
    for (int i = 0; i < array_length(mesh.faces); i++)
    {
        face_t face = mesh.faces[i];

        triangle_t triangle;
        // Project the point on the screen
        for (int j = 0; j < 3; j++)
        {
            triangle.points[j] = project(transformed_mesh_vertices[face.indices[j]]);
            triangle.points[j].x += (window_width * 0.5f);
            triangle.points[j].y += (window_height * 0.5f);
        }
        array_push(projected_mesh_faces, triangle);
    }
}

void render(void)
{
    // draw_grid();
    draw_point_grid(100, 100, 0xFFAAAAAA);
    // draw_rectangle(100, 100, 300, 200, 0xFF9922F0);

    for (int i = 0; i < array_length(projected_mesh_faces); i++)
    {
        triangle_t triangle = projected_mesh_faces[i];
        draw_triangle(triangle, 0xFFFFFF00);
    }

    array_free(transformed_mesh_vertices);
    array_free(projected_mesh_faces);

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