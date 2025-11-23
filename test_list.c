#include "linkedlist.h"
#include <stdio.h>

int cmp_int(void *a, void *b)
{
	int ia = *(int *)a;
	int ib = *(int *)b;
	return (ia - ib);
}

void disp_int(void *a)
{
	int ia = *(int *)a;
	printf("%d", ia);
}

int main()
{
	int a = 42;
	int b = 66;
	int c = 98;
	int d = 102;
	int z = 87;

	List list;
	init_list(&list);
	Element *e = create_element(&a, sizeof(int));

	Element *f = create_element(&b, sizeof(int));
	Element *g = create_element(&c, sizeof(int));
	// freeElement(e);

	add_element(&list, e);
	add_element(&list, f);
	add_element(&list, g);

	display_list(&list, disp_int);

	Element *j = create_element(&z, sizeof(int));
	insert_after_element(&list, g, j);

	display_list(&list, disp_int);

	Element *s = search_element(&list, &a, cmp_int);
	printf("\ns=%d\n", *((int *)s->data));

	remove_element(&list, s);
	display_list(&list, disp_int);

	remove_element(&list, list.first);
	display_list(&list, disp_int);

	remove_element(&list, list.last);
	display_list(&list, disp_int);

	free_list(&list);
}