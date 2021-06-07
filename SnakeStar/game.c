#include "game.h"
#include "log.h"
#include <time.h>


#define FPS 30
#define	TIMEUNTILUPDATE 1/FPS
#define VELOCITY 100

void game() {
	Game game;
	sfVideoMode mode = { WIDTH, HEIGHT, 32 };
	game.window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!game.window) {
		addLog(LOG_ERR, "window not open");
		return 1;
	}

	sfWindow_setFramerateLimit(game.window, 60);
	sfRenderWindow_clear(game.window, sfBlack);
	sfRenderWindow_display(game.window);
	
	initSnake(&game.snake);
	initMap(game.window);
	setFood(&game.food);
	
	initAstar(game);
	/*KeyCodeMap* moveMap = NULL;
	moveMap = mapSet(moveMap, sfKeyZ, &moveNorth);
	moveMap = mapSet(moveMap, sfKeyQ, &moveWest);
	moveMap = mapSet(moveMap, sfKeyS, &moveSouth);
	moveMap = mapSet(moveMap, sfKeyD, &moveEast);

	dispFood(game.food, game.window);
	dispSnake(game.window, game.snake);

	gameLoop(game, moveMap);*/

	clear(game.window, game.snake);
	//removeMap(moveMap);
}

void dispFood(Food food, sfRenderWindow* window) {
	sfRectangleShape* rect = sfRectangleShape_create();
	sfRenderWindow_drawRectangleShape(window, setRectPos(rect, food.color, food.pos.x, food.pos.y) , NULL);
	sfRectangleShape_destroy(rect);
}

/*void gameLoop(Game game, KeyCodeMap *moveMap) {

	float totaleTime = 0;
	float previousTimeElapsed = 0;
	float deltaTime = 0;
	float totaleTimeSinceUpdate = 0;
	sfEvent event;
	float totaleTimeSinceMove = 0;

	while (sfRenderWindow_isOpen(game.window))
	{
		totaleTime = clock();
		deltaTime = totaleTime - previousTimeElapsed;
		previousTimeElapsed = totaleTime;
		totaleTimeSinceUpdate += deltaTime;
		
		if (totaleTimeSinceUpdate >= TIMEUNTILUPDATE) {
			totaleTimeSinceUpdate = 0;
			printGame(&game);
		}

		totaleTimeSinceMove += deltaTime;
		if (totaleTimeSinceMove >= VELOCITY) {
			totaleTimeSinceMove = 0;
			sfRenderWindow_pollEvent(game.window, &event);
			//controller(moveMap, event, &game);
			if ((game.food.pos.x == game.snake.body->pos.x) && (game.food.pos.y == game.snake.body->pos.y)) {
				add(&game.snake);
				setFood(&game.food);
			}

			if (!isAllowToGo(game.snake))
				return;
		}
	}
}*/

int collideWithBody(SnakesBody body) {
	SnakesBody *buff = body.next;
	while (buff->next) {
		if (body.pos.x == buff->pos.x && body.pos.y == buff->pos.y) return 0;
		buff = buff->next;
	}
	return 1;
}

sfRectangleShape* setRectPos(sfRectangleShape* rect, sfColor color, int x, int y) {
	sfVector2f size;
	size.x = (WIDTH / MAPSIZE);
	size.y = (HEIGHT / MAPSIZE);
	sfRectangleShape_setSize(rect, size);
	sfRectangleShape_setFillColor(rect, color);

	sfVector2f pos;
	pos.x = x * (WIDTH / MAPSIZE);
	pos.y = y * (HEIGHT / MAPSIZE);
	sfRectangleShape_setPosition(rect, pos);

	return rect;
}

void initMap(sfRenderWindow* window) {
	sfRectangleShape* rect = sfRectangleShape_create();

	for (int y = 0; y < MAPSIZE; ++y) {
		for (int x = 0; x < MAPSIZE; ++x) {
			if (x == 0 || y == 0 || x == (MAPSIZE - 1) || y == (MAPSIZE - 1)) {
				sfRenderWindow_drawRectangleShape(window, setRectPos(rect, sfColor_fromRGB(0, 0, 255), x, y), NULL);
			}
			else {
				sfRenderWindow_drawRectangleShape(window, setRectPos(rect, sfColor_fromRGB(0, 255, 0), x, y), NULL);
			}
		}
	}
	sfRectangleShape_destroy(rect);
}

void dispSnake(sfRenderWindow* window, Snake snake) {
	sfRectangleShape* rect = sfRectangleShape_create();
	while (snake.body)
	{
		sfRenderWindow_drawRectangleShape(window, setRectPos(rect, snake.body->color, snake.body->pos.x, snake.body->pos.y), NULL);
		snake.body = snake.body->next;
	}
	sfRectangleShape_destroy(rect);
}

void clear(sfRenderWindow* window, Snake snake) {
	removeSnake(&snake);
	sfWindow_destroy(window);
}

/*void controller(KeyCodeMap *map, sfEvent eventKey, Game* game) {
	if (eventKey.type == sfEvtClosed) {
		sfRenderWindow_close(game->window);
		return;
	}
	for (KeyCodeMap* i = map; i != NULL; i = i->next) {
		if (i->key == eventKey.key.code) {
			int bool = i->move(&game->snake);
			if(bool)
				return;
		}
	}
	switch (game->snake.dir)
	{
		case north :
			moveNorth(&game->snake);
			break;
		case west :
			moveWest(&game->snake);
			break;
		case south :
			moveSouth(&game->snake);
			break;
		case east:
			moveEast(&game->snake);
			break;
		default:
			break;
	}
}*/

void printGame(Game *game) {
	sfRenderWindow_clear(game->window, sfBlack);
	initMap(game->window);
	dispFood(game->food, game->window);
	dispSnake(game->window, game->snake);
	sfRenderWindow_display(game->window);
}

KeyCodeMap* mapSet(KeyCodeMap *map, sfKeyCode key, void (*move)(Snake*)) {
	KeyCodeMap* newPart = malloc(sizeof(*newPart));
	if (!newPart) {
		addLog(LOG_ERR, "add map part not allocated");
		return;
	}
	newPart->key = key;
	newPart->move = move;
	newPart->next = NULL;

	if (!map)
		return;

	KeyCodeMap* buff = map;
	while (buff->next)
		buff = buff->next;
	buff->next = newPart;
	return map;
}

void removeMap(KeyCodeMap* map) {
	if (!map)
		return;
	while (map->next) {
		KeyCodeMap* del = map;
		map = map->next;
		free(del);
	}
	free(map);
	return 0;
}