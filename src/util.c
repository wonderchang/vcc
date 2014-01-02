#include "./include/main.h"
#include "./include/util.h"

int calculate_string_length(char *string) {
  int length = 0;
  while(string[length] != '\0')
    length++;
  return length;
}

int is_datatype_except_const(Token token) {
  if(token.type == INT || token.type == CHAR || token.type == STRING || token.type == BOOL)
    return 1;
  else
    return 0;
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
	printf("Unexpected token type occur, fucking bug in get_token_type_in_string function at err-han.c");
	break;
  }
}
