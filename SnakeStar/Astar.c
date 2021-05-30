#include "Astar.h"
#include <math.h>

void initAstar(Game game) {
	Node nodeArray[4];
}

Node* pushFront(Node* list, int g, int h, Coordinates pos, int origin) {
	Node* newNode = malloc(sizeof(Node*));
	newNode->gCost = g;
	newNode->hCost = h;
	newNode->fCost = g+h;
	newNode->origin = origin;
	newNode->pos = pos;
	newNode->next = NULL;
	
	if (!list)
		return newNode;


}

Node* popFront(Node* list);

/*void findNeighbor(Node** nodeArray, Game game) {
	Coordinates actualPos = nodeArray[0]->pos;
	nodeArray[0]->pos.x ++;

	if (isAllowToGo(game.snake)) {
		createNode(game, actualPos, nodeArray, east);
	}
	game.snake.body->pos.x -=2;
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
	}

}

void createNode(Game game, Coordinates actualPos, Node** nodeArray, Direction dir) {
	Node* newNode = malloc(sizeof(Node*));
	newNode->hCost = calculateHCost(game);
	newNode->gCost = calculateGCost(game.snake, actualPos);
	newNode->fCost = (newNode->gCost + newNode->hCost);
	newNode->next = NULL;
	newNode->origin = nodeArray[0]->origin;
	newNode->pos.x = game.snake.body->pos.x;
	newNode->pos.y = game.snake.body->pos.y;
	newNode->dir = dir;
	addNodeToList(nodeArray, newNode);
}*/

int calculateHCost(Game game) {
	return(abs(game.food.pos.x - game.snake.body->pos.x) + abs(game.food.pos.y - game.snake.body->pos.y));
}

int calculateGCost(Snake snake, Coordinates actualPos) {
	return(abs(snake.body->pos.x - actualPos.x) + abs(snake.body->pos.y - actualPos.y));
}

void addNodeToList(Node** nodeArray, Node* newNode) {
	Node** buff = nodeArray;
	Node* previousNode = buff[0];
	while (buff[0]->fCost > newNode->fCost)
	{
		previousNode = buff[0];
		buff[0] = buff[0]->next;
	}

	if (buff[0]->fCost == newNode->fCost) {
		if (buff[0]->hCost < newNode->hCost || buff[0]->gCost < newNode->gCost) {
			addNodeInArray(previousNode, newNode, buff[0]);
		}
		else {
			addNodeInArray(buff[0], newNode, buff[0]->next);
		}
		return;
	}
	addNodeInArray(previousNode, newNode, buff[0]);
}