# c_hash
Pure C hashtable container

<img src="struct.png" width=400>

# Minimal use
## string as key, string as value
```C
HashTable hashtable_str;
init_hashtable(&hashtable_str, cmp_key_str);
char *key_a = "Bonjour";
char *value_a = "Salutation";
put(&hashtable_str, key_a, value_a, strlen(key_a) + 1, strlen(value_a) + 1);

char *k = "Bonjour";
char *v = get(&hashtable_str, k, strlen(k) + 1);
printf("Value:%s\n", v);
free_hashtable(&hashtable_str);
```


## int as key, int as value
```C
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

free_hashtable(&hashtable_int);
```


# string as key, struct as value
```C
typedef struct {
	const char insee[127];
	const char commune[127];
	const char code_postal[127];
	const char acheminement[127];
} CodePostal;

static const CodePostal codes_postaux[] = {{"01001", "L ABERGEMENT CLEMENCIAT", "01400", "L ABERGEMENT CLEMENCIAT"},
										   {"01002", "L ABERGEMENT DE VAREY", "01640", "L ABERGEMENT DE VAREY"},
										   {"01004", "AMBERIEU EN BUGEY", "01500", "AMBERIEU EN BUGEY"},
										   {"01005", "AMBERIEUX EN DOMBES", "01330", "AMBERIEUX EN DOMBES"},
										   {"01006", "AMBLEON", "01300", "AMBLEON"},
										   {"01007", "AMBRONAY", "01500", "AMBRONAY"},
										   {"01008", "AMBUTRIX", "01500", "AMBUTRIX"},
										   {"01009", "ANDERT ET CONDON", "01300", "ANDERT ET CONDON"},
										   {"01010", "ANGLEFORT", "01350", "ANGLEFORT"},
										   {"01011", "APREMONT", "01100", "APREMONT"}};
static const int codes_postaux_count = 10;

HashTable hashtable_cp;
init_with_index_size_hashtable(&hashtable_cp, cmp_key_str, 64);

for (int i = 0; i < codes_postaux_count; i++) {
  char *key = (char *)codes_postaux[i].insee;
  put(&hashtable_cp, key, (CodePostal *)&codes_postaux[i], strlen(key) + 1, sizeof(CodePostal));
}

char *kcp = "01008";
CodePostal *cp = get(&hashtable_cp, kcp, strlen(kcp) + 1);
if (cp) display_code_postal(cp);
free_hashtable(&hashtable_cp);
```

# string as key, dynamic struct as value
```C
typedef struct {
	char *insee;
	char *commune;
	char *code_postal;
	char *acheminement;
} CodePostalDynamic;

static const CodePostal codes_postaux[] = {{"01001", "L ABERGEMENT CLEMENCIAT", "01400", "L ABERGEMENT CLEMENCIAT"},
										   {"01002", "L ABERGEMENT DE VAREY", "01640", "L ABERGEMENT DE VAREY"},
										   {"01004", "AMBERIEU EN BUGEY", "01500", "AMBERIEU EN BUGEY"},
										   {"01005", "AMBERIEUX EN DOMBES", "01330", "AMBERIEUX EN DOMBES"},
										   {"01006", "AMBLEON", "01300", "AMBLEON"},
										   {"01007", "AMBRONAY", "01500", "AMBRONAY"},
										   {"01008", "AMBUTRIX", "01500", "AMBUTRIX"},
										   {"01009", "ANDERT ET CONDON", "01300", "ANDERT ET CONDON"},
										   {"01010", "ANGLEFORT", "01350", "ANGLEFORT"},
										   {"01011", "APREMONT", "01100", "APREMONT"}};
static const int codes_postaux_count = 10;

char *copy_key(const CodePostal *cp)
{
	return strdup(cp->insee);
}

CodePostalDynamic *copy_code_postal(const CodePostal *cp)
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
	CodePostalDynamic *cp = (CodePostalDynamic *)n->data;
	free(cp->insee);
	free(cp->commune);
	free(cp->code_postal);
	free(cp->acheminement);
	free(n->data);
}

void code_postal_deep_copy(Node *target, void *value, size_t value_size)
{
	Node *t = (Node *)target;
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

HashTable hashtable_cp_dyn;
init_with_index_size_and_value_copy_hashtable(&hashtable_cp_dyn, cmp_key_str, 64, code_postal_deep_copy,
											  free_code_postal_node);
for (int i = 0; i < codes_postaux_count; i++) {
	char *key = copy_key((CodePostal*) &codes_postaux[i]);
	put(&hashtable_cp_dyn, key, copy_code_postal((CodePostal *) &codes_postaux[i]), strlen(key) + 1, sizeof(CodePostalDynamic));
}
char *kcp_dyn = "01009";
CodePostalDynamic *cp_dyn = get(&hashtable_cp_dyn, kcp_dyn, strlen(kcp_dyn) + 1);
if (cp_dyn) display_code_postal_dyn(cp_dyn);
free_hashtable(&hashtable_cp_dyn);
```

