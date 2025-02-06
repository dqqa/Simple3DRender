#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#include "errors.h"
#include "helper.h"
#include "model3d.h"
#include "vertex.h"

#define TARGET_FPS 60

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Simeple minimalistic 3D renderer using RayLib"

#ifndef __cplusplus
#define BACKGROUND_COLOR ((Color){ 0x18, 0x18, 0x18, 0xff })
#else
#define BACKGROUND_COLOR (Color{ 0x18, 0x18, 0x18, 0xff })
#endif

#define ROTATION_SPEED 0.01f

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// Why not? :)
#include "cube.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    // const char *prg_name = shift_args(&argc, &argv);
    // const char *model_filename = shift_args(&argc, &argv);

    // if (!model_filename)
    // {
    //     fprintf(stderr, "Usage: %s <model.txt>\n", prg_name);
    //     return ERR_ARGS;
    // }

    Model3D cube_model = {
        cube_vertices,
        ARR_LEN(cube_vertices),
        cube_points,
        ARR_LEN(cube_points),
        0, 0, 0,
        1, 1, 1
    };
    (void)cube_model;
    // Vector3 camera =

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        (void)dt;
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        // Render
#ifdef DEBUG
        char buf[256];
        snprintf(buf, sizeof(buf), "FPS: %7.2f", 1.0f / dt);
        DrawText(buf, 10, 10, 20, WHITE);
#endif

        EndDrawing();
    }

    return ERR_OK;
}
