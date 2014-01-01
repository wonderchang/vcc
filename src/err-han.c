#include "./include/main.h"
#include "./include/err-han.h"

void VC_ERR(char *err_message) {
  if(err_message != NULL) {
    printf("%s:%d:%d, Error: %s\n", src_name, line_no, line_pos, err_message);
    fprintf(err_f, "%s:%d:%d, Error: %s\n", src_name, line_no, line_pos, err_message);
  }
}

void VC_MATCH(TokenType token_type) {
  while(current_token.type == COMMENT)
    current_token = get_token();
  if(current_token.type == token_type) {
    //printf("match, current_token = %d, token = %d\n", current_token.type, token_type);
    current_token = get_token();
  }
  else {
    //printf("not match, current_token = %d, token = %d\n", current_token.type, token_type);
    VC_ERR("token expected");
    exit(1);
  }
}

void VC_CHECK(TokenType op, TokenType op1, TokenType op2, TokenType op3, TokenType op4, TokenType op5, TokenType op6, TokenType op7, TokenType op8) {
  while(current_token.type == COMMENT)
    current_token = get_token();
  //printf("now current_token = %d\n", current_token.type);
  while(current_token.type != op && current_token.type != op1 && current_token.type != op2 && current_token.type != op3 && current_token.type != op4 && current_token.type != op5 && current_token.type != op6 && current_token.type != op7 && current_token.type != op8) {
    current_token = get_token();
    //printf("skip, current_token = %d\n", current_token.type);
    VC_ERR("Unexpected token");
  }
}
