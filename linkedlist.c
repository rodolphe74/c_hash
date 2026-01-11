#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_list(List *list)
{
	list->first = NULL;
	list->last = NULL;
}

Element *create_element(void *data, size_t sz)
{
	Element *e = malloc(sizeof(Element));
	e->data = malloc(sz);
	memcpy(e->data, data, sz);
	// printf("%d\n", *((int *)e->data));
	e->next = NULL;
	return e;
}

void free_element(Element *element)
{
	free(element->data);
	free(element);
}

void add_element(List *list, Element *element)
{
	if (list->first == NULL) {
		list->first = element;
		list->last = element;
		list->last->next = NULL;
	} else if (list->first == list->last) {
		list->first->next = element;
		list->last = element;
		list->last->next = NULL;
	} else {
		list->last->next = element;
		element->next = NULL;
		list->last = list->last->next;
	}
}

void insert_after_element(List *list, Element *which, Element *element)
{
	if (which == list->first) {
		Element *temp = list->first->next;
		list->first = element;
		element->next = temp;
	} else if (which == list->last) {
		add_element(list, element);
	} else {
		Element *temp = which->next;
		which->next = element;
		element->next = temp;
	}
}

Element *search_element(List *list, void *data, int (*cmp)(void *, void *))
{
	Element *e = list->first;
	while (e != NULL) {
		void *current_data = e->data;
		if (cmp(current_data, data) == 0) {
			return e;
		}
		e = e->next;
	}
	return NULL;
}

void remove_element(List *list, Element *element)
{
	// empty list
	if (list->first == NULL) {
		return;
	}

	// 1 element
	if (list->last == NULL) {
		free_element(list->first);
		list->first = NULL;
		list->last = NULL;
		return;
	}

	// remove first element
	if (element == list->first) {
		list->first = element->next;
		free_element(element);
		return;
	}

	Element *e = list->first;
	while (e != NULL) {
		if (e->next == element) {
			break;
		}
		e = e->next;
	}

	e->next = element->next;
	free_element(element);
}

void do_on_list(List *list, void (*to_do)(void *))
{
	Element *e = list->first;
	while (e != NULL) {
		to_do(e->data);
		e = e->next;
	}
}

void free_list(List *list)
{
	Element *e = list->first;
	while (e != NULL) {
		Element *temp = e->next;
		free(e->data);	// free node
		free(e);		// free element
		e = temp;
	}
}

void display_list(List *list, void (*disp)(void *))
{
	Element *e = list->first;
	while (e != NULL) {
		printf("[%p,", (void *)e);
		disp(e->data);
		printf("]");
		e = e->next;
	}
	printf("->NULL\n");
}

size_t size_list(List *list)
{
	Element *e = list->first;
	int count = 0;
	while (e != NULL) {
		count++;
		e = e->next;
	}
	return count;
}
