#include "linkedlist.h"
#include "hash.h"
#include "codes_postaux.h"
#include <stdio.h>
#include <string.h>



void display_code_postal(CodePostal *codePostal)
{
	printf("Commune: %s  code insee:%s\n", codePostal->commune, codePostal->insee);
}

int main()
{
	HashTable hashtable_cp;
	init_with_index_size_hashtable(&hashtable_cp, cmp_key_str, 64);

	printf("nombre de communes: %d\n", codes_postaux_count);

	for (int i = 0; i < codes_postaux_count; i++) {
		char *key = (char *) codes_postaux[i].insee;
		put(&hashtable_cp, key, (CodePostal *) &codes_postaux[i], strlen(key) + 1, sizeof(CodePostal));
	}

	printf("max bucket size: %d\n", get_max_bucket_size(&hashtable_cp));
	printf("mean bucket size: %d\n", get_mean_bucket_size(&hashtable_cp));

	char *key_1 = "77322";
	CodePostal *codePostal = get(&hashtable_cp, key_1, strlen(key_1) + 1);
	if (codePostal) {
		display_code_postal(codePostal);
	} else {
		printf("Code postal %s non trouvé\n", key_1);
	}

	// check all
	int count = 0;
	for (int i = 0; i < codes_postaux_count; i++) {
		char *key = (char *) codes_postaux[i].insee;
		CodePostal *code_postal = get(&hashtable_cp, key, strlen(key) + 1);

		if (!code_postal) {
			printf("code insee %s non trouvé\n", key);
		} else {
			count++;
		}
	}
	printf("\ncount: %d\n", count);

	free_hashtable(&hashtable_cp);
	return 0;
}