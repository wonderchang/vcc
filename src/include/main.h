#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//The Number of the reserved words
#define MAX_RW_NUM 14
#define FILE_NAME_LEN 32

//The type of token
typedef enum {
  //Reserved word
  BOOL, CHAR, CONST, STRING, INT, IF, ELSE, WHILE,
  READ, PRINT, PRINTLN, MAIN, FALSE, TRUE,
  //Meaningful token
  ID, NUMBER, SIGN_NUM, CHAR_CONST, STR_CONST, BOOL_VAL, COMMENT,
  //Special symbol
  PLUS, MINUS, ASSIGN, TIMES, DIVIDE, MODE,
  LT, LTEQ, GT, GTEQ, EQ, NEQ,
  LP, RP, LB, RB, COMMA, SEMICO, SQ, DQ,
  //Exception
  END_FILE, ERROR,
  //White space
  SPACE
} TokenType;

//The token structure that contains some info
typedef struct {
  char *string;
  TokenType type;
} Token;

//The input file pointer
extern FILE *src_f;
extern char *src_name;
//The output file pointer
extern FILE *obj_f;
extern FILE *err_f;
extern FILE *lst_f;
//The output file name
extern char obj_name[FILE_NAME_LEN];
extern char err_name[FILE_NAME_LEN];
extern char lst_name[FILE_NAME_LEN];
//The position of each processing in the file
extern int token_line_no;
extern int token_line_pos;
extern Token current_token;

typedef enum {
  PROG_HDR, PROG_END
} ProgramState;


void vcc_prologue();
void process_cmd_argu();
void start_up_process();
void clean_up_process();
void vcc_epilogue();

