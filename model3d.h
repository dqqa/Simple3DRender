#ifndef MODEL3D_H__
#define MODEL3D_H__

#include "raylib.h"

#include "edge.h"
#include <stddef.h>

typedef struct __model3d
{
    Vector3 *vertices;
    size_t vertices_cnt;

    Edge *edges;
    size_t edges_cnt;

    float rotation_x;
    float rotation_y;
    float rotation_z;

    float scale_x;
    float scale_y;
    float scale_z;
} Model3D;

#endif // MODEL3D_H__
