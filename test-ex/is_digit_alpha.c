#include <stdio.h>
#include <ctype.h>

int main() {
  int a = '1';
  char b = 'c';

  if(isalpha(b)) {
    printf("a is a alpha.\n");
  }
  else {
    printf("a is not a alpha.\n");
  }


  return 0;
}

