#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include "Snake.h"
#include "log.h"
#include "game.h"

int main()
{
	initLog();
	game();
	closeLog();
	return 0;
}