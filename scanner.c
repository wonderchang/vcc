#include "main.h"
#include "scanner.h"

//The buffer which store the reading line
char line_buffer[MAX_BUFLEN];
//The variable that save an character each time for get next char, to obtain the string of token
char token_string[MAX_TOKENLEN + 1];
//The flag that record it is end of file or not
int EOF_flag = 0;

//The type of state
typedef enum { 
  //Start and end
  START, DONE, READY_DONE,
  //White space
  BLANK,
  //Identifier and number
  INID, INNUM,
  //Characters
  INSTRING, BEG_CHAR, END_CHAR,
  //Conditions
  IN_EQ, IN_NEQ, IN_LT, IN_GT,
  //Comments
  IN_SLASH, SINGLE_COMMENT, MULTI_COMMENT, END_MULTI_COMMENT
} StateType;

//The reserved word list, used to get the reserved word token
static struct { 
  char* word;
  TokenType token_type;
} reserved_words[MAX_RW_NUM] = {
  {"bool", BOOL}, {"char", CHAR}, {"const", CONST}, {"string", STRING}, {"int", INT},
  {"if", IF}, {"else", ELSE}, {"while", WHILE}, 
  {"read", READ}, {"print", PRINT}, {"println", PRINTLN}, 
  {"main", MAIN}, {"FALSE", FALSE}, {"TRUE", TRUE}
};

int get_next_char() {
  line_pos++;
  int character;
  if(line_buffer[line_pos]) {
    //line_buffer haven't end, get the next char
    character = line_buffer[line_pos];
    return character;
  }
  else {
    //line_buffer ended, fget next line, and get the first char
    if(fgets(line_buffer, MAX_BUFLEN - 1, src) != NULL) {
      line_no++;
      line_pos = 0;
      character = line_buffer[line_pos];
      return character;
    }
    else {
      EOF_flag = 1;
      character = EOF;
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
  StateType state = START;
  int token_string_index = 0; 
  int character;
  int save;

  while(state != DONE) {
    character = get_next_char();
    save = 1;
    switch(state) {
      case START:
	if(character == ' ' || character == '\t' || character == '\n') state = START;
	else if(isalpha(character)) state = INID;
	else if(isdigit(character)) state = INNUM;
	else if(character == '\"') { state = INSTRING; save = 0; }
	else if(character == '\'') { state = BEG_CHAR; save = 0; }
	else if(character == '=') state = IN_EQ;
	else if(character == '!') state = IN_NEQ;
	else if(character == '<') state = IN_LT;
	else if(character == '>') state = IN_GT;
	else if(character == '/') state = IN_SLASH;
	else if(character == '+') { state = READY_DONE; token.type = PLUS; }
	else if(character == '-') { state = READY_DONE; token.type = MINUS; }
	else if(character == '*') { state = READY_DONE; token.type = TIMES; }
	else if(character == '%') { state = READY_DONE; token.type = MODE; }
	else if(character == '(') { state = READY_DONE; token.type = LP; }
	else if(character == ')') { state = READY_DONE; token.type = RP; }
	else if(character == ',') { state = READY_DONE; token.type = COMMA; }
	else if(character == ';') { state = READY_DONE; token.type = SEMICO; }
	else if(character == '{') { state = READY_DONE; token.type = LB; }
	else if(character == '}') { state = READY_DONE; token.type = RB; }
	else if(character == EOF) { state = DONE; token.type = END_FILE; }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case INID:
	if(isdigit(character)) state = INID;
	else if(isalpha(character)) state = INID;
	else { state = DONE; token.type = ID; back_next_char(); }
	break;
      case INNUM:
	if(isdigit(character)) state = INNUM;
	else if(!isalpha(character)) { state = DONE; token.type = NUMBER; back_next_char(); }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case INSTRING:
	if(character == '\"') { state = READY_DONE; token.type = STR_CONST; save = 0; }
	else state = INSTRING;
	break;
      case BEG_CHAR:
	state = END_CHAR;
	break;
      case END_CHAR:
	if(character == '\'') { state = READY_DONE; token.type = CHAR_CONST; save = 0; }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case IN_EQ:
	if(character == '=') { state = DONE; token.type = EQ; back_next_char(); }
	else { state = DONE; token.type = ASSIGN; back_next_char(); }
	break;
      case IN_NEQ:
	if(character == '=') { state = DONE; token.type = NEQ; back_next_char(); }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case IN_LT:
	if(character == '=') { state = DONE; token.type = LTEQ; back_next_char(); }
	else { state = DONE; token.type = LT; back_next_char(); } 
	break;
      case IN_GT:
	if(character == '=') { state = DONE; token.type = GTEQ; back_next_char(); }
	else { state = DONE; token.type = GT; back_next_char(); }
	break;
      case IN_SLASH:
	if(character == '/') state = SINGLE_COMMENT;
	else if(character == '*') state = MULTI_COMMENT;
	else { state = DONE; token.type = DIVIDE; back_next_char(); }
	break;
      case SINGLE_COMMENT:
	if(character == '\n') { state = DONE; token.type = COMMENT; back_next_char(); }
	else state = SINGLE_COMMENT;
	break;
      case MULTI_COMMENT:
	if(character == '*') state = END_MULTI_COMMENT;
	else state = MULTI_COMMENT;
	break;
      case END_MULTI_COMMENT:
	if(character == '/') { state = READY_DONE; token.type = COMMENT; }
	else state = MULTI_COMMENT;
	break;
      case READY_DONE:
	state = DONE; back_next_char();
	break;
      case DONE:
	break;
      default:
	state = DONE; token.type = ERROR; back_next_char();
	printf("The Unexpected State, Fucking Bug!\n");
	break;
    }
    if(state == DONE) { 
      if(token.type == ERROR)
	token_string[token_string_index++] = (char) character;
      token_string[token_string_index] = '\0';
      if(token.type == ID)
	token.type = reserved_lookup(token_string);
    }
    else {
      if(state != START && (save) && (token_string_index <= MAX_TOKENLEN)) {
	token_string[token_string_index++] = (char) character;
      }
    }
  }
  if(token.type == END_FILE)
    token.string = "EOF";
  else 
    token.string = token_string;
  return token;
}

void print_token(Token token) {
  printf("filename.c:%d:%d, ", line_no, line_pos);
  print_token_type(token.type);
  printf("\t\ttoken: [%s]\n", token.string);
}


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
