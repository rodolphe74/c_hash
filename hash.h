#ifndef HASH_H
#define HASH_H

#include "linkedlist.h"
#include <stdint.h>
#include <stdlib.h>

#define INDEX_SIZE 4096

typedef struct Node {
	void *key;
	void *data;
} Node;

typedef struct HashTable {
	// List buckets[INDEX_SIZE];
	List *buckets;
	int (*key_cmp)(void *, void *);
	size_t index_size;
	void (*value_copy)(Node *target, void *value, size_t _value_size);
} HashTable;

int cmp_key_str(void *a, void *b);
int cmp_key_int(void *a, void *b);
uint32_t hash_bytes_to_uint32(const void *data, size_t len);
void init_hashtable(HashTable *hastable, int (*cmp_key)(void *, void *));
void init_with_index_size_hashtable(HashTable *hastable, int (*cmp_key)(void *, void *), size_t index_size);
void init_with_index_size_and_value_copy_hashtable(HashTable *hastable, int (*cmp_key)(void *, void *),
												   size_t index_size,
												   void (*value_deep_copy)(Node *target, void *value, size_t _value_size));
void set_index_size(HashTable *hastable, size_t index_size);
void put(HashTable *hashtable, void *key, void *value, size_t key_size, size_t value_size);
void *get(HashTable *hashtable, void *key, size_t key_size);
void free_hashtable(HashTable *hashtable);
size_t get_max_bucket_size(HashTable *hashtable);
size_t get_mean_bucket_size(HashTable *hashtable);

#endif