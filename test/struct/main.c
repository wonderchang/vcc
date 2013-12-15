#include <stdio.h>

struct card {
  char *face;
  char *suit;
} aCard, *cardPtr;

int main(void) {
  //struct card aCard;
  //struct card *cardPtr;

  aCard.face = "Ace";
  aCard.suit = "Spades";

  cardPtr = &aCard;

  printf("%s%s%s\n%s%s%s\n%s%s%s\n", 
      aCard.face, " of ", aCard.suit, 
      cardPtr->face, " of ", cardPtr->suit, 
      (*cardPtr).face, " of ", (*cardPtr).suit);

  return 0;
}
