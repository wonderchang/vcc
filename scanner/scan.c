#include <stdio.h>

static int getNextChar(void);

#define MAX_BUFLEN 256

FILE *source;
int lineno;
int linepos;

char line_buffer[MAX_BUFLEN];
int line_position = 0;
int current_line_buffer_string_size = 0;
int EOF_flag = 0;

typedef enum { 
  START, DONE,
  INASSIGN, INCOMMENT, INID, INNUM,
  BEG_CHAR, END_CHAR, INSTRING,
  IN_EQ, IN_NE, IN_LE, IN_GE
} StateType;

typedef enum {
  ENDFILE,ERROR,
  IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
  ID,NUM,
  ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
} TokenType;


int main(void) {

  lineno = -1;
  source = fopen("test.c", "r");
  char c;

  while(!EOF_flag) {
    c = get_next_char();
    printf("main output: %c\n", c);
  }

  fclose(source);
  return 0;
}

int get_next_char() {
  linepos++;
  int current_char;
  if(line_buffer[linepos]) {
    //line_buffer haven't end, get the next char
    current_char = line_buffer[linepos];
    printf("linepos = %d, current_char = '%c'\n", linepos, current_char);
    return current_char;
  }
  else {
    //line_buffer ended, fget next line, and get the first char
    if(fgets(line_buffer, MAX_BUFLEN - 1, source) != NULL) {
      lineno++;
      linepos = 0;
      current_char = line_buffer[linepos];
      printf("Get the new line:\n");
      printf("\t%d\t%s\n", lineno, line_buffer);
      printf("linepos = %d, current_char = '%c'\n", linepos, current_char);
      return current_char;
    }
    else {
      EOF_flag = 1;
      return EOF;
    }
  }
}

TokenType get_token() {

  TokenType current_token;
  StateType state = START;
  int c;

  while(state != DONE) {
    c = get_next_char();
    switch(state) {
      case START:
	break;
      case INID:
	break;
      case INSIGN:
	break;
      case INNUM:
	break;
      case INSTRING:
	break;
      case BEG_CHAR:
	break;
      case IN_EQ:
	break;
      case IN_NE:
	break;
      case IN_LE:
	break;
      case IN_GE:
	break;
      case DONE:
	break;
      default:
	break;
    }
  }



  return current_token;
}

