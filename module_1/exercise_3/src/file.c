// Author: David Malášek

#include "../include/file.h"

char *read_string()
{
    static char buffer[32];
    fgets(buffer, 31, stdin);
    return (buffer);
}

int read_int()
{
    char buffer[32];

    fgets(buffer, 31, stdin);
    return (atoi(buffer));
}