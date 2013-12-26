
int main(int argc, char* argv[]) {

  Token token;

  line_no = 0;
  source = fopen(argv[1], "r");

  printf("program start\n");

  token = get_token();
  while(token.type != END_FILE && token.type != ERROR) {
    print_token(token);
    token = get_token();
  }

  fclose(source);
  return 0;
}


