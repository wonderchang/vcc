#include "main.h"
#include "scanner.h"

FILE *source;
int line_no;
int line_pos;

int main(int argc, char *argv[]) {
  source = fopen(argv[1], "r");
  Token current_token;
  line_no = 0;
  line_pos = 0;

  current_token = get_token();
  while(current_token.type != END_FILE) {
    print_token(current_token);
    current_token = get_token();;
  }

  fclose(source);
}
