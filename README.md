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
