#include <stdio.h>

typedef enum {
  START, DONE,
  ID, INUM
} TokenType;

typedef struct {
  int id;
  TokenType type;
} Token;


int main() {
  Token list[2];
  list[0].id = 1;
  list[0].type = ID;
  list[0].id = 3;
  list[1].type = START;
  printf("[0] id = %d, type = %d\n", list[0].id, list[0].type);
  printf("[1] id = %d, type = %d\n", list[1].id, list[1].type);
}
