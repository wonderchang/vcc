#include <stdio.h>

int main(void) {
  FILE *fPtr;
  char character;
  int i;
  fPtr = fopen("test.c", "r");
  while(fgets(&character, 1, fPtr) != NULL) {
    printf("character = '%c'\n", character);
  }

  fclose(fPtr);

  return 0;
}

