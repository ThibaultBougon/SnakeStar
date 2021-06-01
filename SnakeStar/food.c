#include "food.h"
#include <time.h>

void setFood(Food* food) {
	food->color = sfColor_fromRGB(255, 255, 255);
	food->pos.x = 5;
	food->pos.y = 5;


	/*rand(time(NULL));
  int buufX = food->pos.x;
	int buufY = food->pos.y;
	while (buufX == food->pos.x)
		food->pos.x = (rand() % (MAPSIZE-2))+1;
	while (buufY == food->pos.y)
		food->pos.y = (rand() % (MAPSIZE - 2)) + 1;*/
}