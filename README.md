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
```
