#include "global.h"
#include "scanner.h"
#include "translator.h"
#include "code-gen.h"

Token current_token;
int error_level;

int translate() {
  current_token = get_token();
  if(current_token != END_FILE) {
    program(current_token);
    if(current_token != END_FILE) {
      VC_ERR("Extra chars after program ending");
    }
  }
  else {
    VC_ERR("The file is empty");
  }
  return error_level;
}


void program(Token token) {
  if(token != MAIN) 
    VC_ERR("main expected");
  else {
    pro_hdr(token);
    pro_body(current_token);
  }
}

void pro_hdr(Token token) {
  while(current_token == COMMENT)
    current_token = get_token();
  VC_MATCH(MAIN);
  VC_MATCH(LP);
  VC_MATCH(RP);
}

void pro_body(Token token) {
  if(token != LB)
    VC_ERR("{ missing");
  else {
    //code("prog_hdr");
  }
}

void VC_ERR(char *err_message) {
  if(err_message != NULL)
    printf("%d:%d, Error: %s\n", line_no, char_no, err_message);
}

void VC_MATCH(Token token) {
  if(current_token == token)
    current_token = get_token();
  else
    printf("token expected");
}

void VC_CHECK(Token first, Token follow) {

}

