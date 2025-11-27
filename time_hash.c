#include "hash.h"
#include "codes_postaux.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
#endif

// Fonction qui retourne le temps courant en millisecondes
long long current_time_millis() {
#ifdef _WIN32
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000LL) / freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
#endif
}



CodePostal *sequential_search(const char *insee, const CodePostal *array, size_t array_size) {
    for (int i = 0; i < codes_postaux_count; i++) {
        if (strcmp(insee, codes_postaux[i].insee) == 0) {
            return (CodePostal *) &codes_postaux[i];
        }
    }
    return NULL;
} 

int main() {

    // recherche séquencielle
    long long start = current_time_millis();
    int count = 0;
    for (int i = 0; i < codes_postaux_count; i++) {
        const char *key = (const char *) codes_postaux[i].insee;
        CodePostal *cp = sequential_search(key, codes_postaux, codes_postaux_count);
        if (cp) count++;
    }
    long long end = current_time_millis();
    if (count == codes_postaux_count) {
        printf("Sequential search %d - %lld millisec\n", count, end - start);
    }


    // recherche hashtable
    #define CP_INDEX_SIZE 1
    HashTable hashtable_cp;
	init_with_index_size_hashtable(&hashtable_cp, cmp_key_str, CP_INDEX_SIZE);

	for (int i = 0; i < codes_postaux_count; i++) {
		char *key = (char *) codes_postaux[i].insee;
		put(&hashtable_cp, key, (CodePostal *) &codes_postaux[i], strlen(key) + 1, sizeof(CodePostal));
	}

    start = current_time_millis();
    count = 0;
	for (int i = 0; i < codes_postaux_count; i++) {
		const char *key = (const char *) codes_postaux[i].insee;
        CodePostal *cph = get(&hashtable_cp, (char *) key, strlen(key) + 1);
        if (cph) count++;
    }
    end = current_time_millis();
    if (count == codes_postaux_count) {
        printf("Hashtable search %d - %lld millisec\n", count, end - start);
    }

    free_hashtable(&hashtable_cp);


    return 0;
	}