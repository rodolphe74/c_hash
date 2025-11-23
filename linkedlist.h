#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct Element {
	void *data;
	struct Element *next;
} Element;

// typedef Element List;

typedef struct List {
	Element *first;
	Element *last;
} List;

void init_list(List *list);
Element *create_element(void *data, size_t sz);
void free_element(Element *element);
void add_element(List *list, Element *element);
void insert_after_element(List *list, Element *which, Element *element);
Element *search_element(List *list, void *data, int (*cmp)(void *, void *));
void remove_element(List *list, Element *element);
void do_on_list(List *list, void (*to_do)(void *));
void free_list(List *list);
void display_list(List *list, void (*disp)(void *));
size_t size_list(List *list);

#endif