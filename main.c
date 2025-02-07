#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#include "errors.h"
#include "helper.h"
#include "model3d.h"
#include "edge.h"

#define TARGET_FPS 60

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Simple minimalistic 3D renderer using RayLib"

#ifndef __cplusplus
#define BACKGROUND_COLOR ((Color){ 0x18, 0x18, 0x18, 0xff })
#else
#define BACKGROUND_COLOR (Color{ 0x18, 0x18, 0x18, 0xff })
#endif

#define FOCAL_LENGTH 10.0f

#define SCALE 100.0f

#define LINE_WIDTH 1
#define ROTATION_SPEED (DEG2RAD * 1.f)

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// // Standard film size
// int filmHeight = 24;
// int filmWidth = 36;

// // Formula to convert focalLength to field of view - In Unity they use Vertical FOV.
// // So we use the filmHeight to calculate Vertical FOV.
// double fovdub = Mathf.Rad2Deg * 2.0 * Math.Atan(filmHeight  / (2.0 * focalLen));
// float fov = (float) fovdub;

// or

// hFov = 2 * atan(tan( vFov/2 ) * width/height)

// Why not? :)
#include "cube.h"

Vector2 projection(const Vector3 *point3d, float focal_length)
{
    Vector2 res;

    res.x = (focal_length * point3d->x) / (focal_length + point3d->z);
    res.y = (focal_length * point3d->y) / (focal_length + point3d->z);

    return res;
}

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
        cube_edges,
        ARR_LEN(cube_edges),
        0, 0, 0,
        1, 1, 1
    };
    (void)cube_model;
    // Vector3 camera =

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    float rotation = 0.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        (void)dt;
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        // Vector2 mouse_pos = GetMousePosition();

        // Render

        for (size_t edge = 0; edge < cube_model.edges_cnt; edge++)
        {
            Edge *e = &cube_model.edges[edge];

            Vector3 new_start3d = Vector3RotateByAxisAngle(cube_model.vertices[e->start], (Vector3){ 1, 1, 1 }, rotation);
            Vector3 new_end3d = Vector3RotateByAxisAngle(cube_model.vertices[e->end], (Vector3){ 1, 1, 1 }, rotation);

            Vector2 start = projection(&new_start3d, FOCAL_LENGTH);
            Vector2 end = projection(&new_end3d, FOCAL_LENGTH);
            start = Vector2Add(Vector2Scale(start, SCALE), (Vector2){ WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 });
            end = Vector2Add(Vector2Scale(end, SCALE), (Vector2){ WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 });

            DrawLineV(start, end, WHITE);
        }

#ifdef DEBUG
        char buf[256];
        snprintf(buf, sizeof(buf), "FPS: %7.2f", 1.0f / dt);
        DrawText(buf, 10, 10, 20, WHITE);
#endif
        if (rotation + ROTATION_SPEED >= 360)
            rotation = rotation + ROTATION_SPEED - 360;
        else
            rotation += ROTATION_SPEED;
        EndDrawing();
    }

    return ERR_OK;
}
