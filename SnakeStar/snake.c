#include "snake.h"
#include "log.h"

void initSnake(Snake* snake) {
	snake->dir = north;
	Coordinates initPos;
	initPos.x = MAPSIZE / 2;
	initPos.y = MAPSIZE / 2;
	snake->body = NULL;
	

	for (int i = 0; i < 3; ++i) {
		initPos.y = (MAPSIZE / 2)+i;
		snake->body = addPart(initPos, snake->body);
	}
}

 SnakesBody* addPart(Coordinates pos, SnakesBody *body) {
	SnakesBody *newPart = malloc(sizeof(*newPart));
	if (!newPart) {
		addLog(LOG_ERR, "add part not allocated");
		return 1;
	}
	newPart->pos = pos;
	newPart->next = NULL;

	if (!body) {
		newPart->color = sfColor_fromRGB(255, 0, 0);
		return newPart;
	}
	newPart->color = sfColor_fromRGB(255, 255, 0);


	SnakesBody *buff;
	buff = body;
	while (buff->next)
		buff = buff->next;
	buff->next = newPart;
	return body;
}

int removeSnake(Snake *snake) {
	if (!snake->body)
		return 0;
	while (snake->body)
	{
		SnakesBody *del = snake->body;
		snake->body = snake->body->next;
		free(del);
	}
	free(snake->body);
	return 0;
}

/*void move(Snake snake, int x, int y) {
	int actualX = 0;
	int actualY = 0;
	int buffX = snake.body->pos.x;
	int buffY = snake.body->pos.y;

	snake.body->pos.x += x;
	snake.body->pos.y += y;
	snake.body = snake.body->next;
	while (snake.body) {
		actualX = snake.body->pos.x;
		actualY = snake.body->pos.y;
		snake.body->pos.x = buffX;
		snake.body->pos.y = buffY;
		snake.body = snake.body->next;
		buffX = actualX;
		buffY = actualY;
	}
}*/

int snakeLenght(Snake snake) {//don t use atm
	int a = 0;
	while (snake.body) {
		++a;
		snake.body = snake.body->next;
	}
	return a;
}

/*int moveNorth(Snake *snake) {
	if (snake->dir == south)
		return 0;
	move(*snake, 0, -1);
	snake->dir = north;
	return 1;
}

int moveWest(Snake *snake) {
	if (snake->dir == east)
		return 0;
	move(*snake, -1, 0);
	snake->dir = west;
	return 1;
}

int moveSouth(Snake *snake) {
	if (snake->dir == north)
		return 0;
	move(*snake, 0, 1);
	snake->dir = south;
	return 1;
}

int moveEast(Snake*snake) {
	if (snake->dir == west)
		return 0;
	move(*snake, 1, 0);
	snake->dir = east;
	return 1;
}*/

void add(Snake* snake) {
	Coordinates pos = lfpos(snake);
	snake->body =  addPart(pos, snake->body);
}

Coordinates lfpos(Snake* snake) {
	SnakesBody* previous = NULL;
	SnakesBody* actual = snake->body;

	while (actual->next)
	{
		previous = actual;
		actual = actual->next;
		//buff = buff->next;
	}
	Coordinates pos;
	pos.x = previous->pos.x - actual->pos.x;
	pos.y = previous->pos.y - actual->pos.y;
	return pos;
}

/*int moveNorth(SnakesBody body) {
	move(&body, 0, -1);
	return 1;
}

int moveWest(SnakesBody body) {
	move(&body, -1, 0);
	return 1;
}

int moveSouth(SnakesBody body) {
	move(body, 0, 1);
	return 1;
}*/

int moveEast(SnakesBody* body) {
	move(body, 1, 0);
	return 1;
}

void move(SnakesBody* body, int x, int y) {
	int actualX = 0;
	int actualY = 0;
	int buffX = body->pos.x;
	int buffY = body->pos.y;

	body->pos.x += x;
	body->pos.y += y;
	body = body->next;
	while (body->next) {
		actualX = body->pos.x;
		actualY = body->pos.y;
		body->pos.x = buffX;
		body->pos.y = buffY;
		body = body->next;
		buffX = actualX;
		buffY = actualY;
	}
}