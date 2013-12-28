#include <stdio.h>

typedef enum {
  IF, THEN
} TokenType;

static struct { 
  char* str;
  TokenType tok;
} reservedWords[8] = {
  {"if",IF},
  {"then",THEN},
};

int main() {
  printf("%s\n", reservedWords[0].str);
  return 0;
}


