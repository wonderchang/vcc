#include <stdio.h>

void VC_ERR(char *err_message);

int main() {
  VC_ERR("what the fuck");
}

void VC_ERR(char *err_message) {
  if(err_message != NULL)
    printf("Error: %s\n", err_message);
}
