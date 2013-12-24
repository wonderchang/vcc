#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUFLEN 256
#define MAX_TOKENLEN 256;
#define MAX_RW_NUM 14;

FILE *source;
int lineno;
int linepos;

char line_buffer[MAX_BUFLEN];
int line_position = 0;
int current_line_buffer_string_size = 0;
int EOF_flag = 0;

char token_string[MAX_TOKENLEN + 1];

typedef enum { 
  START,
  INID, INNUM,
  INSTRING, BEG_CHAR, END_CHAR,
  IN_EQ, IN_NEQ, IN_LT, IN_GT,
  SLASH, SINGLE_COMMENT, MULTI_COMMENT, END_MULTI_COMMENT,
  DONE
} StateType;

typedef enum {
  //Reserved word
  BOOL, CHAR, CONST, STRING, INT, IF, ELSE, WHILE,
  READ, PRINT, PRINTLN, MAIN, FALSE, TRUE,
  //Meaningful token
  ID, NUMBER, CHAR_CONST, STR_CONST, BOOL_VAL, COMMENT,
  //Special symbol
  PLUS, MINUS, ASSIGN, TIMES, DIVIDE, MODE,
  LT, LTEQ, GT, GTEQ, EQ, NEQ,
  LP, RP, LB, RB, COMMA, SEMICO, SQ, DQ,
  //Exception
  ENDFILE, ERROR
} TokenType;

struct { 
  char* word;
  TokenType token_type;
} reserved_words[MAX_RW_NUM] = {
  {"bool", BOOL}, {"char", CHAR}, {"CONST", CONST}, {"string", STRING}, {"int", INT},
  {"if", IF}, {"else", ELSE}, {"while", WHILE}, 
  {"read", READ}, {"PRINT", PRINT}, {"PRINTLN", PRINTLN}, 
  {"main", MAIN}, {"FALSE", FALSE}, {"TRUE", TRUE}
};

struct {
  char* token_string;
  int token_lineno;
  int token_linepos;
  TokenType token_type;
} Token;


int get_next_char();
void back_next_char();
TokenType get_token();
void print_token_type(TokenType token_type);

int main(int argc, char* argv[]) {

  lineno = -1;
  source = fopen(argv[1], "r");

  get_token();
  get_token();
  get_token();
  get_token();
  get_token();
  get_token();

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

void back_next_char() {
  if(!EOF_flag) linepos--;
}

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reserved_lookup (char * s) { 
  int i;
  for (i = 0; i < MAX_SW_NUM; i++)
    if (!strcmp(s ,reserved_words[i].word))
      return reserved_words[i].token_type;
  return ID;
}

TokenType get_token() {

  int token_string_index = 0; 
  TokenType token_type;
  StateType state = START;
  int save;
  int c;

  while(state != DONE) {
    c = get_next_char();
    save = 1;
    switch(state) {
      case START:
	if(c == ' ' || c == '\t' || c == '\n') state = START;
	else if(isalpha(c)) state = INID;
	else if(isdigit(c)) state = INNUM;
	else if(c == '\"') state = INSTRING;
	else if(c == '\'') state = BEG_CHAR;
	else if(c == '=') state = IN_EQ;
	else if(c == '!') state = IN_NEQ;
	else if(c == '<') state = IN_LT;
	else if(c == '>') state = IN_GT;
	else if(c == '/') state = SLASH;
	else {
	  state = DONE;
	  switch(c) {
	    case '+': token_type = PLUS; break;
	    case '-': token_type = MINUS; break;
	    case '*': token_type = TIMES; break;
	    case '%': token_type = MODE; break;
	    case '(': token_type = LP; break;
	    case ')': token_type = RP; break;
	    case ',': token_type = COMMA; break;
	    case ';': token_type = SEMICO; break;
	    case '{': token_type = LB; break;
	    case '}': token_type = RB; break;
	    case EOF: token_type = ENDFILE; break;
	    default: token_type = ERROR; break;
	  }
	}
	break;
      case INID:
	if(isdigit(c)) state = INID;
	else if(isalpha(c)) state = INID;
	else { state = DONE; token_type = ID; back_next_char(); }
	break;
      case INNUM:
	if(isdigit(c)) state = INNUM;
	else if(!isalpha(c)) { state = DONE; token_type = NUMBER; back_next_char(); }
	else { state = DONE; token_type = ERROR; }
	break;
      case INSTRING:
	if(isalpha(c)) state = INSTRING;
	else { state = DONE; token_type = STR_CONST; back_next_char(); }
	break;
      case BEG_CHAR:
	state = END_CHAR;
	break;
      case END_CHAR:
	if(c == '\'') { state = DONE; token_type = CHAR_CONST; back_next_char(); }
	else { state = DONE; token_type = ERROR; }
	break;
      case IN_EQ:
	if(c == '=') { state = DONE; token_type = EQ; back_next_char(); }
	else { state = DONE; token_type = ASSIGN; back_next_char(); }
	break;
      case IN_NEQ:
	if(c == '=') { state = DONE; token_type = NEQ; back_next_char(); }
	else { state = DONE; token_type = ERROR; }
	break;
      case IN_LT:
	if(c == '=') { state = DONE; token_type = LTEQ; back_next_char(); }
	else { state = DONE; token_type = LT; }
	break;
      case IN_GT:
	if(c == '=') { state = DONE; token_type = GTEQ; back_next_char(); }
	else { state = DONE; token_type = GT; }
	break;
      case SLASH:
	if(c == '/') state = SINGLE_COMMENT;
	else if(c == '*') state = MULTI_COMMENT;
	else { state = DONE; token_type = DIVIDE; back_next_char(); }
	break;
      case SINGLE_COMMENT:
	if(c == '\n') { state = DONE; token_type = COMMENT; back_next_char(); }
	else state = SINGLE_COMMENT;
	break;
      case MULTI_COMMENT:
	if(c == '*') state = END_MULTI_COMMENT;
	else state = MULTI_COMMENT;
	break;
      case END_MULTI_COMMENT:
	if(c == '/') { state = DONE; token_type = COMMENT; back_next_char(); }
	else state = MULTI_COMMENT;
	break;
      case DONE:
	break;
      default:
	state = DONE;
	token_type = ERROR;
	printf("The Unexpected Stage, Fucking Bug!\n");
	break;
    }
    if((save) && (token_string_index <= MAX_TOKENLEN))
      token_string[token_string_index++] = (char) c;
    if (state == DONE) { 
      token_string[token_string_index] = '\0';
      if (token_type == ID)
	token_type = reserved_lookup(token_string);
    }
  }
  print_token_type(token_type);
  return token_type;
}

void print_token_type(TokenType token_type) {
  switch(token_type) {
    case RW:
      printf("token type: RW\n");
      break;
    case ID:
      printf("token type: ID\n");
      break;
    case NUMBER:
      printf("token type: NUMBER\n");
      break;
    case CHAR_CONST:
      printf("token type: CHAR_CONST\n");
      break;
    case STR_CONST:
      printf("token type: STR_CONST\n");
      break;
    case BOOL_VAL:
      printf("token type: BOOL_VAL\n");
      break;
    case COMMENT:
      printf("token type: COMMENT\n");
      break;
    case PLUS:
      printf("token type: PLUS\n");
      break;
    case MINUS:
      printf("token type: MINU\n");
      break;
    case ASSIGN:
      printf("token type: ASSIGN\n");
      break;
    case TIMES:
      printf("token type: TIMES\n");
      break;
    case DIVIDE:
      printf("token type: DIVIDE\n");
      break;
    case MODE:
      printf("token type: MODE\n");
      break;
    case LT:
      printf("token type: LT\n");
      break;
    case LTEQ:
      printf("token type: LTEQ\n");
      break;
    case GT:
      printf("token type: GT\n");
      break;
    case GTEQ:
      printf("token type: GTEQ\n");
      break;
    case EQ:
      printf("token type: EQ\n");
      break;
    case NEQ:
      printf("token type: NEQ\n");
      break;
    case LP:
      printf("token type: LP\n");
      break;
    case RP:
      printf("token type: RP\n");
      break;
    case LB:
      printf("token type: LB\n");
      break;
    case RB:
      printf("token type: RB\n");
      break;
    case COMMA:
      printf("token type: COMMA\n");
      break;
    case SEMICO:
      printf("token type: SEMICO\n");
      break;
    case SQ:
      printf("token type: SQ\n");
      break;
    case DQ:
      printf("token type: DQ\n");
      break;
    case ENDFILE:
      printf("token type: ENDFILE\n");
      break;
    case ERROR:
      printf("token type: ERROR\n");
      break;
    default:
      printf("Unexpected token type occur, fucking bug!\n");
      break;
  }
}
