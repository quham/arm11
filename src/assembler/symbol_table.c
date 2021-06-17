#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

Table *makeTable(void) {
  Table *table = malloc(sizeof(Table));
  table->size = malloc(sizeof(size_t));
  table->max_size = malloc(sizeof(size_t));
  table->elements = calloc(INITIAL_MAX_TABLE_SIZE, sizeof(Pair));
  *table->size = 0;
  *table->max_size = INITIAL_MAX_TABLE_SIZE;
  return table;
}

void put(Table *table, char *key, word32 value) {
  assert(*table->max_size >= INITIAL_MAX_TABLE_SIZE);

  // resize
  if (*table->size == *table->max_size) {
    *table->max_size *= 2;
    table->elements = realloc(table->elements, *table->max_size * sizeof(Pair));
    assert(table->elements != NULL);
  }

  Pair pair;
  pair.value = value;
  char *str = calloc(sizeof(char), LINE_LENGTH);
  safeStrCpy(str, key);
  pair.key = str;
  table->elements[*table->size] = pair;
  (*table->size)++;
}

word32 lookup(Table *table, char *str) {
  for (size_t i = 0; i < *table->size; i++) {
    Pair pair = table->elements[i];
    printf("key: %s\n", pair.key);
    if (!strcmp(pair.key, str)) {
      return pair.value;
    }
  }
  perror("Error: key not in map\n");
  exit(EXIT_FAILURE);
}

void freeTable(Table *table) {
  for (size_t i = 0; i < *table->size; i++) {
    free(table->elements[i].key);
  }
  free(table->size);
  free(table->max_size);
  free(table->elements);
  free(table);
}
