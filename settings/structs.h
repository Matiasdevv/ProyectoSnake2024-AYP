#ifndef STRUCTS_H_ /* Include guard */
#define STRUCTS_H_
#include <SDL2/SDL.h>

typedef struct
{
    int x, y, w, h;
} Segment;

typedef struct
{
    char name[50];
    int score;
    char difficulty[10];
} Player;

#endif
