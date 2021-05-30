#pragma once
#include "Snake.h"
#include "food.h"

#include "Astar.h"

#define HEIGHT 600
#define WIDTH 800

typedef struct {
	struct KeyCodeMap* next;
	sfKeyCode key;
	int (*move)(Snake*);
}KeyCodeMap;

void game();
void initMap(sfRenderWindow* window);
sfRectangleShape* setRectPos(sfRectangleShape* rect, sfColor color, int x, int y);
void dispSnake(sfRenderWindow* window, Snake body);
void dispFood(Food food, sfRenderWindow* window);
void clear(sfRenderWindow* window, Snake snake);
void gameLoop(Game game, KeyCodeMap* moveMap);

void printGame(Game *game);
KeyCodeMap* mapSet(KeyCodeMap* map, sfKeyCode key, void (*move)(Snake*));
void removeMap(KeyCodeMap* map);
void controller(KeyCodeMap* map, sfEvent eventKey, Game* game);

