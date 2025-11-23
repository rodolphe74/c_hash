#include "hash.h"
#include <string.h>
#include <stdio.h>

int main()
{
	HashTable hashtable_str;
	init_hashtable(&hashtable_str, cmp_key_str);
	char *key_a = "Bonjour";
	char *value_a = "Salutation";
	put(&hashtable_str, key_a, value_a, strlen(key_a) + 1, strlen(value_a) + 1);

	char *k = "Bonjour";
	char *v = get(&hashtable_str, k, strlen(k) + 1);
	printf("Value:%s\n", v);

	HashTable hashtable_int;
	init_hashtable(&hashtable_int, cmp_key_int);
	int key_1 = 45;
	int value_1 = 5678;
	int key_2 = 6578;
	int value_2 = 6;
	put(&hashtable_int, &key_1, &value_1, sizeof(int), sizeof(int));
	int *w = get(&hashtable_int, &key_1, sizeof(int));
	if (w) printf("Value:%d\n", *w);

	put(&hashtable_int, &key_2, &value_2, sizeof(int), sizeof(int));
	w = get(&hashtable_int, &key_2, sizeof(int));
	if (w) printf("Value:%d\n", *w);

	printf("max bucket size: %d\n", get_max_bucket_size(&hashtable_int));
	printf("mean bucket size: %d\n", get_mean_bucket_size(&hashtable_int));

	free_hashtable(&hashtable_str);
	free_hashtable(&hashtable_int);
}