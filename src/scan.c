#include "./include/main.h"
#include "./include/scan.h"
#include "./include/err-han.h"
#include "./include/dbg-aid.h"

//The buffer which store the reading line
char line_buffer[MAX_BUFLEN];
//The variable that save an character each time for get next char, to obtain the string of token
char token_string[MAX_TOKEN_LEN + 1];
//The flag that record it is end of file or not
int EOF_flag = 0;
//The current character position
int line_no = 0;
int char_pos = 0;

//The type of state
typedef enum { 
  //Start and end
  START, DONE, READY_DONE,
  //White space
  BLANK,
  //Identifier and number
  INID, INNUM, INSIGN, IN_PLUS, IN_MINUS,
  //Characters
  INSTRING, BEG_CHAR, END_CHAR,
  //Conditions
  IN_EQ, IN_NEQ, IN_LT, IN_GT,
  //Comments
  IN_SLASH, SINGLE_COMMENT, MULTI_COMMENT, END_MULTI_COMMENT,
  //Error
  ST_ERR, NUM_ERR, CHAR_ERR, NEQ_ERR
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
  char_pos++;
  int character;
  if(line_buffer[char_pos]) {
    //line_buffer haven't end, get the next char
    character = line_buffer[char_pos];
    return character;
  }
  else {
    //line_buffer ended, fget next line, and get the first char
    if(fgets(line_buffer, MAX_BUFLEN - 1, src_f) != NULL) {
      line_no++;
      char_pos = 0;
      character = line_buffer[char_pos];
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
  if(!EOF_flag) char_pos--;
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
  token_line_no = line_no;
  int token_string_index = 0; 
  int character;
  int save;

  while(state != DONE) {
    character = get_next_char();
    if(state == START) token_line_pos = char_pos + 1;
    save = 1;
    switch(state) {
      case START:
	if(character == ' ' || character == '\t' || character == '\n') state = START;
	else if(isalpha(character)) state = INID;
	else if(isdigit(character)) state = INNUM;
	else if(character == '\"') { state = INSTRING; save = 0; }
	else if(character == '\'') { state = BEG_CHAR; save = 0; }
	else if(character == '=') { state = IN_EQ; }
	else if(character == '!') { state = IN_NEQ; }
	else if(character == '<') { state = IN_LT; }
	else if(character == '>') { state = IN_GT; }
	else if(character == '/') { state = IN_SLASH; }
	else if(character == '+') { state = IN_PLUS; }
	else if(character == '-') { state = IN_MINUS; }
	else if(character == '*') { state = READY_DONE; token.type = TIMES; }
	else if(character == '%') { state = READY_DONE; token.type = MODE; }
	else if(character == '(') { state = READY_DONE; token.type = LP; }
	else if(character == ')') { state = READY_DONE; token.type = RP; }
	else if(character == ',') { state = READY_DONE; token.type = COMMA; }
	else if(character == ';') { state = READY_DONE; token.type = SEMICO; }
	else if(character == '{') { state = READY_DONE; token.type = LB; }
	else if(character == '}') { state = READY_DONE; token.type = RB; }
	else if(character == EOF) { state = DONE; token.type = END_FILE; }
	else state = ST_ERR;
	break;
      case INID:
	if(isdigit(character)) state = INID;
	else if(isalpha(character)) state = INID;
	else { state = DONE; token.type = ID; back_next_char(); }
	break;
      case INNUM:
	if(isdigit(character)) state = INNUM;
	else if(!isalpha(character)) { state = DONE; token.type = NUMBER; back_next_char(); }
	else state = NUM_ERR;
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
	else state = CHAR_ERR;
	break;
      case IN_EQ:
	if(character == '=') { state = READY_DONE; token.type = EQ; }
	else { state = DONE; token.type = ASSIGN; back_next_char(); }
	break;
      case IN_NEQ:
	if(character == '=') { state = READY_DONE; token.type = NEQ; }
	else state = NEQ_ERR;
	break;
      case IN_LT:
	if(character == '=') { state = READY_DONE; token.type = LTEQ; back_next_char(); }
	else { state = DONE; token.type = LT; back_next_char(); } 
	break;
      case IN_GT:
	if(character == '=') { state = READY_DONE; token.type = GTEQ; back_next_char(); }
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
      case INSIGN:
	if(isdigit(character)) { state = INSIGN; }
	else { state = DONE; token.type = SIGN_NUM; back_next_char(); }
	break;
      case IN_PLUS:
	if(isdigit(character)) state = INSIGN;
	else { state = DONE; token.type = PLUS; back_next_char(); }
	break;
      case IN_MINUS:
	if(isdigit(character)) state = INSIGN;
	else { state = DONE; token.type = MINUS; back_next_char(); }
	break;
      case READY_DONE:
	state = DONE; back_next_char();
	break;
      case DONE:
	break;
      case ST_ERR:
	switch(character) {
	  case ' ': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ',': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ';': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '}': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ')': state = DONE; token.type = ERROR; back_next_char(); break;
	  case EOF: state = DONE; token.type = ERROR; back_next_char(); break;
	  default: state = ST_ERR;
	}
	break;
      case NUM_ERR:
	switch(character) {
	  case ' ': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ',': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ';': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '}': state = DONE; token.type = ERROR; back_next_char(); break;
	  case ')': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '+': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '-': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '=': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '>': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '<': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '/': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '*': state = DONE; token.type = ERROR; back_next_char(); break;
	  case '%': state = DONE; token.type = ERROR; back_next_char(); break;
	  default: state = NUM_ERR;
	}
	break;
      case CHAR_ERR:
	if(character == '\'' || character == ';' || character == '}' || character == ')' || character == EOF) { state = DONE; token.type = ERROR; save = 0; }
	else state = CHAR_ERR;
	break;
      case NEQ_ERR:
	if(character == ';' || character == '}' || character == ')' || character == EOF) { state = DONE; token.type = ERROR; back_next_char(); }
	else state = NEQ_ERR;
	break;
      default:
	state = DONE; token.type = ERROR; back_next_char();
	printf("The Unexpected State, Fucking bug from state switch part!\n");
	break;
    }
    if(state == DONE) { 
      if(token.type == ERROR)
	token_string[token_string_index] = (char) character;
      token_string[token_string_index] = '\0';
      if(token.type == ID)
	token.type = reserved_lookup(token_string);
    }
    else {
      if(state != START && (save) && (token_string_index <= MAX_TOKEN_LEN)) {
	token_string[token_string_index++] = (char) character;
      }
    }
  }
  if(token.type == END_FILE)
    strcpy(token.string, "EOF");
  else 
    strcpy(token.string, token_string);
  return token;
}

