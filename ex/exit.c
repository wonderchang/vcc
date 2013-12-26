#include <stdio.h>

void fun();

int main() {
  printf("Program start\n");
  fun();
  printf("Program end\n");
}

void fun() {
  printf("Now is in fun()\n");
  exit(1);
}
