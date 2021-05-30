#pragma once
#include "types.h"

void initSnake(Snake* snake);
SnakesBody* addPart(Coordinates pos, SnakesBody* body);
int removeSnake(Snake *snake);
void move(Snake snake, int x, int y);
int moveNorth(Snake *snake);
int moveWest(Snake *snake);
int moveSouth(Snake *snake);
int moveEast(Snake *snake);
void add(Snake *snake);
int snakeLenght(Snake snake);
Coordinates lfpos(Snake* snake);