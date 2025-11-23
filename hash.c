#include "hash.h"
#include <string.h>
#include <stdio.h>

int cmp_key_str(void *a, void *b)
{
	Node na = *(Node *)a;
	Node nb = *(Node *)b;
	char *sa = (char *)na.key;
	char *sb = (char *)nb.key;
	return strcmp(sa, sb);
}

int cmp_key_int(void *a, void *b)
{
	Node na = *(Node *)a;
	Node nb = *(Node *)b;
	int ia = *((int *)(na.key));
	int ib = *((int *)(nb.key));
	return (ia - ib);
}

void shallow_copy(Node *target, void *source, size_t size)
{
	Node *t = (Node *)target;
	free(t->data);
	t->data = malloc(size);
	memcpy(t->data, source, size);
}

void default_free_node(Node *n)
{
	free(n->key);
	free(n->data);
}

// Hash basé sur les octets, type DJB2 modifié pour 32 bits
uint32_t hash_bytes_to_uint32(const void *data, size_t len)
{
	uint32_t hash = 5381;
	const unsigned char *bytes = (const unsigned char *)data;

	for (size_t i = 0; i < len; ++i) {
		hash = ((hash << 5) + hash) ^ bytes[i]; // hash * 33 ^ byte
	}

	return hash;
}

void init_hashtable(HashTable *hastable, int (*cmp_key)(void *, void *))
{
	hastable->index_size = INDEX_SIZE;
	hastable->buckets = malloc(sizeof(List) * hastable->index_size);
	for (int i = 0; i < hastable->index_size; i++) {
		init_list(&hastable->buckets[i]);
	}
	hastable->key_cmp = cmp_key;
	hastable->value_copy = shallow_copy;
	hastable->free_node = default_free_node;
}

void init_with_index_size_hashtable(HashTable *hastable, int (*cmp_key)(void *, void *), size_t index_size)
{
	hastable->index_size = index_size;
	hastable->buckets = malloc(sizeof(List) * hastable->index_size);
	for (int i = 0; i < hastable->index_size; i++) {
		init_list(&hastable->buckets[i]);
	}
	hastable->key_cmp = cmp_key;
	hastable->value_copy = shallow_copy;
	hastable->free_node = default_free_node;
}

void init_with_index_size_and_value_copy_hashtable(
	HashTable *hastable, int (*cmp_key)(void *, void *), size_t index_size,
	void (*value_deep_copy)(Node *target, void *value, size_t _value_size), void (*free_node)(Node *n))
{
	init_with_index_size_hashtable(hastable, cmp_key, index_size);
	hastable->value_copy = value_deep_copy;
	hastable->free_node = free_node;
}

void put(HashTable *hashtable, void *key, void *value, size_t key_size, size_t value_size)
{
	uint32_t hash = hash_bytes_to_uint32(key, key_size);
	uint32_t index = hash % hashtable->index_size;
	List *list = &hashtable->buckets[index];

	// search existing key
	Node t = {key, NULL};

	Element *e = search_element(list, &t, hashtable->key_cmp);
	if (e) {
		Node *n = e->data;
		hashtable->value_copy(n, value, value_size);
		return;
	}

	// no key found
	Node node;
	node.key = malloc(key_size);
	memcpy(node.key, key, key_size);
	node.data = malloc(value_size);
	memcpy(node.data, value, value_size);
	Element *f = create_element(&node, sizeof(node));
	add_element(list, f);
}

void *get(HashTable *hashtable, void *key, size_t key_size)
{
	uint32_t hash = hash_bytes_to_uint32(key, key_size);
	uint32_t index = hash % hashtable->index_size;
	List *list = &hashtable->buckets[index];

	// search existing key
	Node t = {key, NULL};
	Element *e = search_element(list, &t, hashtable->key_cmp);

	if (!e) {
		return NULL;
	}

	Node *n = (Node *)e->data;
	if (n) {
		return n->data;
	}

	return NULL;
}

void free_hashtable(HashTable *hashtable)
{
	for (int i = 0; i < hashtable->index_size; i++) {
		List *list = &hashtable->buckets[i];
		Element *e = list->first;
		while (e != NULL) {
			Node *n = (Node *)e->data;
			hashtable->free_node(n);
			e = e->next;
		}
		free_list(list);
	}
	free(hashtable->buckets);
}

size_t get_max_bucket_size(HashTable *hashtable)
{
	size_t max = 0;
	for (int i = 0; i < hashtable->index_size; i++) {
		size_t sz = size_list(&hashtable->buckets[i]);
		max = sz > max ? sz : max;
	}
	return max;
}

size_t get_mean_bucket_size(HashTable *hashtable)
{
	size_t sum = 0;
	for (int i = 0; i < hashtable->index_size; i++) {
		size_t sz = size_list(&hashtable->buckets[i]);
		sum += sz;
	}
	return sum / INDEX_SIZE;
}
