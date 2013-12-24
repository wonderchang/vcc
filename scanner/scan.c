#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUFLEN 256
#define MAX_TOKENLEN 256
#define MAX_RW_NUM 14

FILE *source;
int line_no;
int line_pos;
int token_no;

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

typedef struct {
  int id;
  char* string;
  int line_no;
  int line_pos;
  TokenType type;
} Token;

typedef struct {
  int c;
  int line_no;
  int line_pos;
} Character;


Character get_next_char();
void back_next_char();
Token get_token();
void print_token(Token token);
void print_token_type(TokenType token_type);

int main(int argc, char* argv[]) {

  Token token;

  line_no = -1;
  token_no = -1;
  source = fopen(argv[1], "r");

  token = get_token();
  print_token(token);
  token = get_token();
  print_token(token);
  /*
  while(token.type != ENDFILE || token.type != ERROR) {
    token = get_token();
    print_token(token);
  }
  */

  fclose(source);
  return 0;
}

Character get_next_char() {
  line_pos++;
  Character character;
  if(line_buffer[line_pos]) {
    //line_buffer haven't end, get the next char
    character.c = line_buffer[line_pos];
    character.line_no = line_no;
    character.line_pos = line_pos;
    return character;
  }
  else {
    //line_buffer ended, fget next line, and get the first char
    if(fgets(line_buffer, MAX_BUFLEN - 1, source) != NULL) {
      line_no++;
      line_pos = 0;
      character.c = line_buffer[line_pos];
      character.line_no = line_no;
      character.line_pos = line_pos;
      return character;
    }
    else {
      EOF_flag = 1;
      character.c = EOF;
      character.line_no = line_no;
      character.line_pos = line_pos;
      return character;
    }
  }
}

void back_next_char() {
  if(!EOF_flag) line_pos--;
}

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reserved_lookup (char * s) { 
  int i;
  for (i = 0; i < MAX_RW_NUM; i++)
    if (!strcmp(s ,reserved_words[i].word))
      return reserved_words[i].token_type;
  return ID;
}

Token get_token() {

  Token token;
  Character character;
  StateType state = START;
  int token_string_index = 0; 
  int save;
  int first_loop = 1;

  while(state != DONE) {
    character = get_next_char();
    if(first_loop) {
      token.line_no = character.line_no;
      token.line_pos = character.line_pos;
      first_loop = 0;
    }
    save = 1;
    switch(state) {
      case START:
	if(character.c == ' ' || character.c == '\t' || character.c == '\n') state = START;
	else if(isalpha(character.c)) state = INID;
	else if(isdigit(character.c)) state = INNUM;
	else if(character.c == '\"') state = INSTRING;
	else if(character.c == '\'') state = BEG_CHAR;
	else if(character.c == '=') state = IN_EQ;
	else if(character.c == '!') state = IN_NEQ;
	else if(character.c == '<') state = IN_LT;
	else if(character.c == '>') state = IN_GT;
	else if(character.c == '/') state = SLASH;
	else {
	  state = DONE;
	  switch(character.c) {
	    case '+': token.type = PLUS; break;
	    case '-': token.type = MINUS; break;
	    case '*': token.type = TIMES; break;
	    case '%': token.type = MODE; break;
	    case '(': token.type = LP; break;
	    case ')': token.type = RP; break;
	    case ',': token.type = COMMA; break;
	    case ';': token.type = SEMICO; break;
	    case '{': token.type = LB; break;
	    case '}': token.type = RB; break;
	    case EOF: token.type = ENDFILE; break;
	    default: token.type = ERROR; break;
	  }
	}
	break;
      case INID:
	if(isdigit(character.c)) state = INID;
	else if(isalpha(character.c)) state = INID;
	else { state = DONE; token.type = ID; back_next_char(); }
	break;
      case INNUM:
	if(isdigit(character.c)) state = INNUM;
	else if(!isalpha(character.c)) { state = DONE; token.type = NUMBER; back_next_char(); }
	else { state = DONE; token.type = ERROR; save = 0; }
	break;
      case INSTRING:
	if(isalpha(character.c)) state = INSTRING;
	else { state = DONE; token.type = STR_CONST; back_next_char(); }
	break;
      case BEG_CHAR:
	state = END_CHAR;
	break;
      case END_CHAR:
	if(character.c == '\'') { state = DONE; token.type = CHAR_CONST; back_next_char(); }
	else { state = DONE; token.type = ERROR; save = 0; }
	break;
      case IN_EQ:
	if(character.c == '=') { state = DONE; token.type = EQ; back_next_char(); }
	else { state = DONE; token.type = ASSIGN; back_next_char(); }
	break;
      case IN_NEQ:
	if(character.c == '=') { state = DONE; token.type = NEQ; back_next_char(); }
	else { state = DONE; token.type = ERROR; save = 0; }
	break;
      case IN_LT:
	if(character.c == '=') { state = DONE; token.type = LTEQ; back_next_char(); }
	else { state = DONE; token.type = LT; }
	break;
      case IN_GT:
	if(character.c == '=') { state = DONE; token.type = GTEQ; back_next_char(); }
	else { state = DONE; token.type = GT; }
	break;
      case SLASH:
	if(character.c == '/') state = SINGLE_COMMENT;
	else if(character.c == '*') state = MULTI_COMMENT;
	else { state = DONE; token.type = DIVIDE; back_next_char(); }
	break;
      case SINGLE_COMMENT:
	if(character.c == '\n') { state = DONE; token.type = COMMENT; back_next_char(); }
	else state = SINGLE_COMMENT;
	break;
      case MULTI_COMMENT:
	if(character.c == '*') state = END_MULTI_COMMENT;
	else state = MULTI_COMMENT;
	break;
      case END_MULTI_COMMENT:
	if(character.c == '/') { state = DONE; token.type = COMMENT; back_next_char(); }
	else state = MULTI_COMMENT;
	break;
      case DONE:
	break;
      default:
	state = DONE;
	token.type = ERROR;
	save = 0;
	printf("The Unexpected Stage, Fucking Bug!\n");
	break;
    }
    if((save) && (token_string_index <= MAX_TOKENLEN)) {
      token_string[token_string_index++] = (char) character.c;
    }
    if(state == DONE) { 
      token_string[token_string_index] = '\0';
      if(token.type == ID)
	token.type = reserved_lookup(token_string);
    }
  }
  token.id = token_no + 1;
  token.string = token_string;
  return token;
}

void print_token(Token token) {
  printf("filename.c:%d:%d, token ID: %d, token: \"%s\", ", token.line_no, token.line_pos, token.id, token.string);
  print_token_type(token.type);
}


void print_token_type(TokenType token_type) {
  switch(token_type) {
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
    case BOOL:
      printf("token type: BOOL\n");
      break;
    case CHAR:
      printf("token type: CHAR\n");
      break;
    case CONST:
      printf("token type: CONST\n");
      break;
    case STRING:
      printf("token type: STRING\n");
      break;
    case INT:
      printf("token type: INT\n");
      break;
    case IF:
      printf("token type: IF\n");
      break;
    case ELSE:
      printf("token type: ELSE\n");
      break;
    case WHILE:
      printf("token type: WHILE\n");
      break;
    case READ:
      printf("token type: READ\n");
      break;
    case PRINT:
      printf("token type: PRINT\n");
      break;
    case PRINTLN:
      printf("token type: PRINTLN\n");
      break;
    case MAIN:
      printf("token type: MAIN\n");
      break;
    case FALSE:
      printf("token type: FALSE\n");
      break;
    case TRUE:
      printf("token type: TRUE\n");
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
