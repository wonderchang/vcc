#include <stdio.h>

int main() {
  char string[10] = "123456789";
  printf("The program start\n");

  printf("string = %s-----\n", string);
  string[7] = '\0';
  string[8] = '\0';
  printf("string = %s-----\n", string);

  printf("The program completed\n");
}
