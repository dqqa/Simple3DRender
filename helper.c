#include "helper.h"
#include <stdio.h>

char *shift_args(int *pargc, char ***pargv)
{
    if (pargc == NULL || *pargc == 0 || pargv == NULL || *pargv == NULL)
        return NULL;

    *pargc -= 1;
    return (**pargv)--;
}
