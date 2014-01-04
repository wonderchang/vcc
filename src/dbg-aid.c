#include "./include/main.h"
#include "./include/dbg-aid.h"

//Print the token information
void print_token(Token token) {
  printf("filename.c:%d:%d, ", token_line_no, token_line_pos);
  print_token_type(token.type);
  printf("location(%p)\t\ttoken: [%s]\n", &(token.string), token.string);
}

//To Return the string that the token type it is, help the print_token function
void print_token_type(TokenType token_type) {
  switch(token_type) {
    case SPACE:
      printf("token type: SPACE, ");
      break;
    case ID:
      printf("token type: ID, ");
      break;
    case NUMBER:
      printf("token type: NUMBER, ");
      break;
    case CHAR_CONST:
      printf("token type: CHAR_CONST, ");
      break;
    case STR_CONST:
      printf("token type: STR_CONST, ");
      break;
    case BOOL_VAL:
      printf("token type: BOOL_VAL, ");
      break;
    case COMMENT:
      printf("token type: COMMENT, ");
      break;
    case PLUS:
      printf("token type: PLUS, ");
      break;
    case MINUS:
      printf("token type: MINU, ");
      break;
    case ASSIGN:
      printf("token type: ASSIGN, ");
      break;
    case TIMES:
      printf("token type: TIMES, ");
      break;
    case DIVIDE:
      printf("token type: DIVIDE, ");
      break;
    case MODE:
      printf("token type: MODE, ");
      break;
    case LT:
      printf("token type: LT, ");
      break;
    case LTEQ:
      printf("token type: LTEQ, ");
      break;
    case GT:
      printf("token type: GT, ");
      break;
    case GTEQ:
      printf("token type: GTEQ, ");
      break;
    case EQ:
      printf("token type: EQ, ");
      break;
    case NEQ:
      printf("token type: NEQ, ");
      break;
    case LP:
      printf("token type: LP, ");
      break;
    case RP:
      printf("token type: RP, ");
      break;
    case LB:
      printf("token type: LB, ");
      break;
    case RB:
      printf("token type: RB, ");
      break;
    case COMMA:
      printf("token type: COMMA, ");
      break;
    case SEMICO:
      printf("token type: SEMICO, ");
      break;
    case SQ:
      printf("token type: SQ, ");
      break;
    case DQ:
      printf("token type: DQ, ");
      break;
    case BOOL:
      printf("token type: BOOL, ");
      break;
    case CHAR:
      printf("token type: CHAR, ");
      break;
    case CONST:
      printf("token type: CONST, ");
      break;
    case STRING:
      printf("token type: STRING, ");
      break;
    case INT:
      printf("token type: INT, ");
      break;
    case IF:
      printf("token type: IF, ");
      break;
    case ELSE:
      printf("token type: ELSE, ");
      break;
    case WHILE:
      printf("token type: WHILE, ");
      break;
    case READ:
      printf("token type: READ, ");
      break;
    case PRINT:
      printf("token type: PRINT, ");
      break;
    case PRINTLN:
      printf("token type: PRINTLN, ");
      break;
    case MAIN:
      printf("token type: MAIN, ");
      break;
    case FALSE:
      printf("token type: FALSE, ");
      break;
    case TRUE:
      printf("token type: TRUE, ");
      break;
    case END_FILE:
      printf("token type: ENDFILE, ");
      break;
    case ERROR:
      printf("token type: ERROR, ");
      break;
    default:
      printf("Unexpected token type occur, fucking bug!, ");
      break;
  }
}
