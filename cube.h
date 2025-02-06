Vector3 cube_vertices[] = {
    { -1, -1, -1 },
    { -1, -1, 1 },
    { 1, -1, -1 },
    { -1, 1, -1 },
    { -1, 1, 1 },
    { 1, -1, 1 },
    { 1, 1, -1 },
    { 1, 1, 1 }
};

Edge cube_edges[] = {
    { 0, 1 },
    { 0, 2 },
    { 0, 3 },
    { 2, 5 },
    { 3, 6 },
    { 3, 4 },
    { 4, 7 },
    { 6, 7 },
    { 7, 5 },
    { 5, 1 },
    { 4, 1 },
    { 2, 6 }
};
