#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

Table *makeTable() {
  Table *table = malloc(sizeof(Table));
  table->size = malloc(sizeof(int));
  table->max_size = malloc(sizeof(int));
  table->elements = calloc(INITIAL_MAX_TABLE_SIZE, sizeof(Pair));
  *table->size = 0;
  *table->max_size = INITIAL_MAX_TABLE_SIZE;
  return table;
}

void put(Table *table, Pair pair) {
  assert(*table->max_size >= INITIAL_MAX_TABLE_SIZE);
  if (*table->size == *table->max_size) {
    *table->max_size *= 2;
    table->elements = realloc(table->elements, *table->max_size * sizeof(Pair));
    assert(table->elements != NULL);
  }
  table->elements[*table->size] = pair;
  (*table->size)++;
}

word32 lookup(Table *table, char *str) {
  for (int i = 0; i < *table->size; i++) {
    Pair pair = table->elements[i];
    if (!strcmp(pair.key, str)) {
      return pair.value;
    }
  }
  perror("Error: key not in map\n");
  exit(EXIT_FAILURE);
}

void freeTable(Table *table) {
  free(table->elements);
  free(table->size);
  free(table->max_size);
  free(table);
}

// Debugging
void test_table() {
  Table *table = makeTable();
  printf("size: %d\n", *table->size);
  Pair pair0 = {"str0", 0xe701a8e0};
  Pair pair1 = {"str1", 0xe701a8e1};
  Pair pair2 = {"str2", 0xe701a8e2};
  Pair pair3 = {"str3", 0xe701a8e3};
  Pair pair4 = {"str4", 0xe701a8e4};
  Pair pair5 = {"str5", 0xe701a8e5};
  Pair pair6 = {"str6", 0xe701a8e6};
  Pair pair7 = {"str7", 0xe701a8e7};
  Pair pair8 = {"str8", 0xe701a8e8};
  Pair pair9 = {"str9", 0x123456};
  put(table, pair0);
  put(table, pair1);
  put(table, pair2);
  put(table, pair3);
  put(table, pair4);
  put(table, pair5);
  put(table, pair6);
  put(table, pair7);
  put(table, pair8);
  put(table, pair9);
  printf("%08x\n", lookup(table, pair0.key));
  printf("%08x\n", lookup(table, pair1.key));
  printf("%08x\n", lookup(table, pair2.key));
  printf("%08x\n", lookup(table, pair3.key));
  printf("%08x\n", lookup(table, pair4.key));
  printf("%08x\n", lookup(table, pair5.key));
  printf("%08x\n", lookup(table, pair6.key));
  printf("%08x\n", lookup(table, pair7.key));
  printf("%08x\n", lookup(table, pair8.key));
  printf("%08x\n", lookup(table, pair9.key));
  freeTable(table);
}
