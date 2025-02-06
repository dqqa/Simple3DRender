#ifndef MODEL3D_H__
#define MODEL3D_H__

#include "raylib.h"

#include "vertex.h"
#include <stddef.h>

typedef struct __model3d
{
    Vertex *vertices;
    size_t vert_cnt;

    Vector3 *points;
    size_t points_cnt;

    float rotation_x;
    float rotation_y;
    float rotation_z;

    float scale_x;
    float scale_y;
    float scale_z;
} Model3D;

#endif // MODEL3D_H__
