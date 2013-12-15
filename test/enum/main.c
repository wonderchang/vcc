#include <stdio.h>

enum Status { CONTINUE, WON, LOST };
void judgement(enum Status g);

int main(void) {
  enum Status gameStatus;
  printf("\nThe game start!\n");
  gameStatus = CONTINUE;
  judgement(gameStatus);
  gameStatus = WON;
  judgement(gameStatus);
  gameStatus = LOST;
  judgement(gameStatus);
}

void judgement(enum Status g) {
  if(g == CONTINUE) {
    printf("\nThe game continue\n");
  }
  else if(g == WON) {
    printf("\nThe game won\n");
  }
  else if(g == LOST) {
    printf("\nThe game lost\n");
  }
  else {
    printf("\nUnexpected Error\n");
  }
}
