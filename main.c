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

#define FOV 10.0f // Not shure about what exactly this is

#define SCALE 100.0f

#define LINE_WIDTH 1
#define ROTATION_SPEED (DEG2RAD * 1.f)

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// Why not? :)
#include "cube.h"

Vector2 projection(const Vector3 *point3d, float fov)
{
    Vector2 res;

    res.x = (fov * point3d->x) / (fov + point3d->z);
    res.y = (fov * point3d->y) / (fov + point3d->z);

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

    float rotation = 0.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        (void)dt;
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        // Vector2 mouse_pos = GetMousePosition();

        // Render

        for (size_t vert = 0; vert < cube_model.vert_cnt; vert++)
        {
            Vertex *v = &cube_model.vertices[vert];

            Vector3 new_start3d = Vector3RotateByAxisAngle(cube_model.points[v->start], (Vector3){ 0, 0, 1 }, rotation);
            Vector3 new_end3d = Vector3RotateByAxisAngle(cube_model.points[v->end], (Vector3){ 0, 0, 1 }, rotation);

            Vector2 start = projection(&new_start3d, FOV);
            Vector2 end = projection(&new_end3d, FOV);
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
