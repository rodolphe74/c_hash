#include "linkedlist.h"
#include "hash.h"
#include "codes_postaux.h"
#include <stdio.h>
#include <string.h>

void display_code_postal(CodePostalDynamic *codePostal)
{
	printf("Commune: %s  code insee:%s\n", codePostal->commune, codePostal->insee);
}

char *copy_key(const CodePostalDynamic *cp) {
	return strdup(cp->insee);
}

CodePostalDynamic *copy_code_postal(const CodePostalDynamic *cp)
{
	CodePostalDynamic *c = malloc(sizeof(CodePostalDynamic));
	c->insee = strdup(cp->insee);
	c->commune = strdup(cp->commune);
	c->code_postal = strdup(cp->code_postal);
	c->acheminement = strdup(cp->acheminement);
	return c;
}




void free_code_postal_node(Node *n)
{
	free(n->key);
	CodePostalDynamic *cp = (CodePostalDynamic *) n->data;
	free(cp->insee);
	free(cp->commune);
	free(cp->code_postal);
	free(cp->acheminement);
	free(n->data);
}

void code_postal_deep_copy(Node *target, void *value, size_t value_size)
{
	Node *t = (Node *)target;

	// Libérer l'ancienne struct si elle existe
	if (t->data) {
		CodePostalDynamic *old = (CodePostalDynamic *)t->data;
		free(old->insee);
		free(old->commune);
		free(old->code_postal);
		free(old->acheminement);
		free(old);
	}

	CodePostalDynamic *cp_source = (CodePostalDynamic *)value;
	CodePostalDynamic *cp_target = malloc(sizeof(CodePostalDynamic));

	cp_target->insee = strdup(cp_source->insee);
	cp_target->commune = strdup(cp_source->commune);
	cp_target->code_postal = strdup(cp_source->code_postal);
	cp_target->acheminement = strdup(cp_source->acheminement);

	t->data = cp_target;
}




int main()
{
	init_cp_dynamic();

	HashTable hashtable_cp;
	init_with_index_size_and_value_copy_hashtable(&hashtable_cp, cmp_key_str, 64, code_postal_deep_copy, free_code_postal_node);

	printf("nombre de communes: %d\n", codes_postaux_count);

	for (int i = 0; i < codes_postaux_count; i++) {
		char *key = copy_key(&code_postaux_alloc[i]);
		put(&hashtable_cp, key, copy_code_postal(&code_postaux_alloc[i]), strlen(key) + 1, sizeof(CodePostalDynamic));
	}

	printf("max bucket size: %d\n", get_max_bucket_size(&hashtable_cp));
	printf("mean bucket size: %d\n", get_mean_bucket_size(&hashtable_cp));

	char *key_1 = "77322";
	CodePostalDynamic *codePostal = get(&hashtable_cp, key_1, strlen(key_1) + 1);
	if (codePostal) {
		display_code_postal(codePostal);
	} else {
		printf("Code postal %s non trouvé\n", key_1);
	}

	// check all
	int count = 0;
	for (int i = 0; i < codes_postaux_count; i++) {
		char *key = (char *) code_postaux_alloc[i].insee;
		CodePostalDynamic *codePostal = get(&hashtable_cp, key, strlen(key) + 1);

		if (!codePostal) {
			printf("code insee %s non trouvé\n", key);
		} else {
			count++;
		}
	}
	printf("\ncount: %d\n", count);

	free_hashtable(&hashtable_cp);
	free_cp_dynamic();
	return 0;
}