#pragma once
#include "types.h"
//#include "game.h"
#include "Snake.h"

typedef struct {
	int gCost;
	int hCost;
	int fCost;
	int origin;
	//Coordinates pos;
	Direction dir;
	SnakesBody body;

	struct Node* next;
}Node;

void initAstar(Game game);
Node* firstNode(Game game);
Node* popFront(Node* list);
void findNeighbor(Node** nodeArray, Game game);
Node** addNodeToList(Node** nodeArray, Node* newNode);
Node** createNode(Game game, SnakesBody body, Node** nodeArray, Direction dir);
void freeArray(Node* node);
int calculateHCost(Food food, Coordinates actualPos);
int calculateGCost(Snake snake, Coordinates actualPos);

static inline void addNodeInArray(Node** previousNode, Node** newNode, Node** nextNode) {
	if(*previousNode)
		(*previousNode)->next = *newNode;
	(*newNode)->next = *nextNode;
}