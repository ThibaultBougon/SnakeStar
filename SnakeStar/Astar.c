#include "Astar.h"
#include <math.h>

void initAstar(Game game) {
	Node** nodeArray = NULL;
	nodeArray = malloc(4 * sizeof(Node));
	if (!nodeArray)
		return;
	for (int i = 0; i < 4; ++i) {
		nodeArray[i] = NULL;
	}
	nodeArray[0]=firstNode(game);

	findNeighbor(nodeArray, game);


	for (int i = 0; i <4; ++i) {
	//for (int i = 3; i >=0; --i) {
		freeArray(nodeArray[i]);
		free(nodeArray[i]);
	}
}

void freeArray(Node* node) {
	if (!node)
		return;
	while (node) {
		Node* del = node;
		node = node->next;
		free(del);
	}
}

Node* firstNode(Game game) {
	Node* newNode = malloc(sizeof(Node*));
	newNode->gCost = 0;
	newNode->hCost = calculateHCost(game.food, game.snake.body->pos);
	newNode->fCost = newNode->gCost + newNode->hCost;
	newNode->dir = north;
	newNode->body = *game.snake.body;
	newNode->origin = 0;
	newNode->next = NULL;
	
	return newNode;
}

void findNeighbor(Node** nodeArray, Game game) {
	/*Coordinates actualPos = nodeArray[0]->pos;
	nodeArray[0]->pos.x ++;*/

	SnakesBody movingSnake = nodeArray[0]->body;
	moveEast(&movingSnake);

	if (isAllowToGo(movingSnake)) {
		nodeArray = createNode(game, movingSnake, nodeArray, east);
	}
	/*game.snake.body->pos.x -=2;
	if (isAllowToGo(game.snake)) {
		createNode(game, actualPos, nodeArray, west);
	}
	game.snake.body->pos.x ++;
	game.snake.body->pos.y++;
	if (isAllowToGo(game.snake)) {
		createNode(game, actualPos, nodeArray, south);
	}
	game.snake.body->pos.y -=2;
	if (isAllowToGo(game.snake)) {
		createNode(game, actualPos, nodeArray, north);
	}*/
}

Node** createNode(Game game, SnakesBody body, Node** nodeArray, Direction dir) {
	Node* newNode = malloc(sizeof(Node*));
	newNode->hCost = calculateHCost(game.food, body.pos);
	newNode->gCost = calculateGCost(game.snake, body.pos);
	newNode->fCost = (newNode->gCost + newNode->hCost);
	newNode->next = NULL;
	//newNode->pos.x = game.snake.body->pos.x;
	//newNode->pos.y = game.snake.body->pos.y;
	newNode->dir = dir;
	newNode->body = body;
	if (nodeArray[0]->origin == 0) {
		switch (dir)
		{
		case east :
			newNode->origin = 3;
		case west :
			newNode->origin = 1;
		case north :
			newNode->origin = 2;
		default:
			break;
		}
	}
	else {
		newNode->origin = nodeArray[0]->origin;
	}
	return(addNodeToList(nodeArray, newNode));
}

int calculateHCost(Food food, Coordinates actualPos) {
	return(abs(food.pos.x - actualPos.x) + abs(food.pos.y - actualPos.y));
}

int calculateGCost(Snake snake, Coordinates actualPos) {
	return(abs(snake.body->pos.x - actualPos.x) + abs(snake.body->pos.y - actualPos.y));
}

Node** addNodeToList(Node** nodeArray, Node* newNode) {
	Node** buff = nodeArray;
	Node* previousNode = NULL;
	Node* nextNode = NULL;
	if (buff[0]->next) {
		while (buff[0]->fCost > newNode->fCost)
		{
			previousNode = buff[0];
			buff[0] = buff[0]->next;
		}
		nextNode = buff[0]->next;
	}

	if (buff[0]->fCost == newNode->fCost && ((buff[0]->hCost > newNode->hCost) ||
			(buff[0]->gCost > newNode->gCost && buff[0]->hCost == newNode->hCost))) {
		addNodeInArray(buff[0], newNode, nextNode);
		return;
	}
	addNodeInArray(&previousNode, &newNode, &buff[0]);
	buff[0] = newNode;
	return nodeArray;
}