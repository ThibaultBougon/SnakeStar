#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "SFML/Graphics.h"

#define MAPSIZE 20

typedef struct
{
	int x;
	int y;
}Coordinates;

typedef enum
{
	north,
	south,
	west,
	east
}Direction;

typedef struct
{
	Coordinates pos;
	struct SnakesBody* next;
	sfColor color;
}SnakesBody;

typedef struct
{
	Direction dir;
	SnakesBody* body;
}Snake;

typedef struct {
	Coordinates pos;
	sfColor color;
}Food;

typedef struct {
	sfRenderWindow* window;
	Snake snake;
	Food food;
}Game;

static inline int isAllowToGo(SnakesBody body) {
	if (body.pos.x == 0 || body.pos.y == 0 ||
		body.pos.x == MAPSIZE - 1 || body.pos.y == MAPSIZE - 1)
		return 0;
	return collideWithBody(body);
}
int collideWithBody(SnakesBody body);