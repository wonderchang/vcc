#include <stdio.h>
#include <string.h>

char *msg_tmp;
char msg[64];

void get_string(int num);

int main(int argc, char *argv[]) {

  printf("The program start.\n");

  int i;

  for(i = 0; i < 8; i++) {
    get_string(i);
    strcat(msg, msg_tmp);
    printf("msg_tmp = %s\n", msg_tmp);
  }
  
  printf("msg = %s\n", msg);

  printf("The program complete.\n");

  return 0;
}


void get_string(int num) {
  switch(num) {
    case 0: msg_tmp = "zero"; break;
    case 1: msg_tmp = "one"; break;
    case 2: msg_tmp = "two"; break;
    case 3: msg_tmp = "three"; break;
    case 4: msg_tmp = "four"; break;
    case 5: msg_tmp = "five"; break;
    case 6: msg_tmp = "six"; break;
    case 7: msg_tmp = "seven"; break;
  }
}
