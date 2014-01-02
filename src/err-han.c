#include "./include/main.h"
#include "./include/scan.h"
#include "./include/err-han.h"
#include "./include/util.h"

char *token_type_string;
char err_msg[ERR_MSG_LEN];

//Error Report, print the error message to the screen and the report file
void VC_ERR(char *err_message) {
  if(err_message != NULL) {
    printf("%s:%d:%d, Error: %s\n", src_name, token_line_no, token_line_pos, err_message);
    fprintf(err_f, "%s:%d:%d, Error: %s\n", src_name, token_line_no, token_line_pos, err_message);
  }
}

//To check the neccessary expected token is match or not, is fatal error
void VC_MATCH(TokenType token_type) {
  //To skip the COMMENT token
  while(current_token.type == COMMENT)
    current_token = get_token();
  if(current_token.type == token_type) {
    //If the token is expected, good and get next token to continue
    current_token = get_token();
  }
  else {
    //else is lossing the expected token, get the fatal error and stop
    clean_err_msg();
    get_token_type_string(token_type);
    strcat(err_msg, "Token ");
    strcat(err_msg, token_type_string);
    strcat(err_msg, " expected.");
    VC_ERR(err_msg);
    current_token = get_token();
    //To hold that no generate the three output file
    //remove_output_file();
    //exit(1);
  }
}

void VC_CHECK(TokenType op, TokenType op1, TokenType op2, TokenType op3, TokenType op4, TokenType op5, TokenType op6, TokenType op7, TokenType op8) {
  //To skip the COMMENT token
  while(current_token.type == COMMENT)
    current_token = get_token();
  //printf("now current_token = %s\n", current_token.string);
  while(current_token.type != op && current_token.type != op1 && current_token.type != op2 && current_token.type != op3 && current_token.type != op4 && current_token.type != op5 && current_token.type != op6 && current_token.type != op7 && current_token.type != op8) {
    //printf("skip, current_token = %d\n", current_token.type);
    clean_err_msg();
    strcat(err_msg, "Unexpected token ");
    strcat(err_msg, current_token.string);
    VC_ERR(err_msg);
    current_token = get_token();
  }
}

void remove_output_file() {
  remove(obj_name);
  remove(err_name);
  remove(lst_name);
}

void clean_err_msg() {
  for(int i = 0; i < ERR_MSG_LEN; i++)
    err_msg[i] = '\0';
}

