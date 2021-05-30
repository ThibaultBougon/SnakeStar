#pragma once
#include "types.h"
//#include "game.h"

typedef struct {
	int gCost;
	int hCost;
	int fCost;
	int origin;
	Coordinates pos;
	Direction dir;

	struct Node* next;
}Node;

void initAstar(Game game);
Node* pushFront(Node *list);
Node* popFront(Node* list);
void findNeighbor(Node** nodeArray, Snake snake);
void addNodeToList(Node** nodeArray, Node* newNode);

static inline void addNodeInArray(Node* previousNode, Node* newNode, Node* nextNode) {
	previousNode->next = newNode;
	newNode->next = nextNode;
}