#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
	int value;
	struct Node *next;
};
typedef struct Node Node;

struct LinkedList {
	Node *head;
};
typedef struct LinkedList LinkedList;

struct DNode {
	int value;
	struct DNode *next;
	struct DNode *prev;
};
typedef struct DNode DNode;
struct DList {
	DNode *head;
};
typedef struct DList DList;


void print_node(Node *node) {
	printf("%d\n", node->value);

}

/**
 * new_node - Returns a new node with the given value
 */
Node* new_node(int value) {
	Node *n = malloc(sizeof(Node)); // Allocate a **new** memory blcok for a `Node`
	n->value = value; // Assign it the value
	return n;
}

/**
 * new_dnode - Returns a new node that can be doubly linked
 */
DNode *new_dnode(int value) {
	DNode *n = malloc(sizeof(DNode));
	n->value = value;
	return n;
}

/**
 * print_list - Prints all the values sequentially in a singly linked list
 */
void print_list(LinkedList *list) {
	Node *curr = list->head;
	while(true) {
		print_node(curr);
		if(curr->next) {
			curr = curr->next;
		} else {
			break;
		}
	}
}

/**
 * print_list - Prints all the values sequentially in a singly linked list
 */
void print_dlist(DList *list) {
	DNode *curr = list->head;
	while(true) {
		printf("%d\n", curr->value);
		if(curr->next) {
			curr = curr->next;
		} else {
			break;
		}
	}
}

/**
 * new_list - Creates an singly linked list
 */
LinkedList new_list() {
	LinkedList list = { 0 }; // Create with null head
	return list;
}

/**
 * new_dlist - Creates an empty doubly linked list
 */
DList new_dlist() {
	DList list = { 0 };
	return list;
}

/**
 * enqueue - Enqueues a value at the end of a singly linked list
 */
void enqueue(int value, LinkedList *list) {
	Node *n = new_node(value);

	// If our list is empty, make our newly allocated `Node` the head
	if(list->head == NULL) {
		list->head = n;
		return;
	}

	// Otherwise, traverse the list until we reach the tail
	Node *curr = list->head;
	Node *next = curr->next;
	while(next) { // Run this loop until we encounter a null pointer
		curr = curr->next;
		next = curr->next;
	}
	// Once `tail` becomes a null pointer, `curr` is the last element of the list
	curr->next = n;
}

/**
 * enqueue_dlist - Enqueues a value at the end of a doubly linked list
 */
void enqueue_dlist(int value, DList *list) {
	DNode *n = new_dnode(value);

	// If our list is empty, make our newly allocated `Node` the head
	if(list->head == NULL) {
		list->head = n;
		return;
	}

	// Otherwise, traverse the list until we reach the tail
	DNode *curr = list->head;
	DNode *next = curr->next;
	while(next) { // Run this loop until we encounter a null pointer
		curr = curr->next;
		next = curr->next;
	}
	// Once `tail` becomes a null pointer, `curr` is the last element of the list
	curr->next = n;
	n->prev = curr;
}


int main() {
	DList list = new_dlist();
	enqueue_dlist(1, &list);
	enqueue_dlist(2, &list);
	enqueue_dlist(3, &list);
	enqueue_dlist(4, &list);
	enqueue_dlist(5, &list);

	DNode *curr = list.head;
	DNode *next = list.head->next;
	printf("%d\n", curr->value);
	while(next) {
		printf("%d\n", next->value);
		curr = next;
		next = curr->next;
	}
	while(curr) {
		printf("%d\n", curr->value);
		curr = curr->prev;
	}

	return 0;
}
