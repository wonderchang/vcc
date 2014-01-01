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
    //To hold that no generate the three output file
    remove_output_file();
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

void remove_output_file() {
  remove(obj_name);
  remove(err_name);
  remove(lst_name);
}

void clean_err_msg() {
  for(int i = 0; i < ERR_MSG_LEN; i++)
    err_msg[i] = '\0';
}


void get_token_type_string(TokenType token_type) {
  switch(token_type) {
    case SPACE: token_type_string = "space"; break;
    case ID: token_type_string = "identifier"; break;
    case NUMBER: token_type_string = "number"; break;
    case CHAR_CONST: token_type_string = "character constant"; break;
    case STR_CONST: token_type_string = "string constant"; break;
    case BOOL_VAL: token_type_string = "boolean value"; break;
    case COMMENT: token_type_string = "comment"; break;
    case PLUS: token_type_string = "+"; break;
    case MINUS: token_type_string = "-"; break;
    case ASSIGN: token_type_string = "="; break;
    case TIMES: token_type_string = "*"; break;
    case DIVIDE: token_type_string = "/"; break;
    case MODE: token_type_string = "%"; break;
    case LT: token_type_string = "<"; break;
    case LTEQ: token_type_string = "<="; break;
    case GT: token_type_string = ">"; break;
    case GTEQ: token_type_string = ">="; break;
    case EQ: token_type_string = "=="; break;
    case NEQ: token_type_string = "!="; break;
    case LP: token_type_string = "("; break;
    case RP: token_type_string = ")"; break;
    case LB: token_type_string = "{"; break;
    case RB: token_type_string = "}"; break;
    case COMMA: token_type_string = ","; break;
    case SEMICO: token_type_string = ";"; break;
    case SQ: token_type_string = "\'"; break;
    case DQ: token_type_string = "\""; break;
    case BOOL: token_type_string = "bool"; break;
    case CHAR: token_type_string = "char"; break;
    case CONST: token_type_string = "const"; break;
    case STRING: token_type_string = "string"; break;
    case INT: token_type_string = "int"; break;
    case IF: token_type_string = "if"; break;
    case ELSE: token_type_string = "else"; break;
    case WHILE: token_type_string = "while"; break;
    case READ: token_type_string = "read"; break;
    case PRINT: token_type_string = "print"; break;
    case PRINTLN: token_type_string = "println"; break;
    case MAIN: token_type_string = "main"; break;
    case FALSE: token_type_string = "FALSE"; break;
    case TRUE: token_type_string = "TRUE"; break;
    case END_FILE: token_type_string = "EOF"; break;
    case ERROR: token_type_string = "error"; break;
    default:
		token_type_string = "Unexpected token type occur, fucking bug in get_token_type_in_string function at err-han.c";
		break;
  }
}

