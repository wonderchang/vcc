#include "global.h"
#include "scanner.h"

//The position of the line
int line_pos;
int token_no = 0;

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

Character get_next_char() {
  line_pos++;
  Character character;
  if(line_buffer[line_pos]) {
    //line_buffer haven't end, get the next char
    character.c = line_buffer[line_pos];
    character.line_no = line_no;
    character.line_pos = line_pos;
    char_no = line_pos;
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
      char_no = line_pos;
      return character;
    }
    else {
      EOF_flag = 1;
      character.c = EOF;
      character.line_no = line_no;
      character.line_pos = line_pos;
      char_no = line_pos;
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

  while(state != DONE) {
    character = get_next_char();
    if(state == START) {
      token.line_no = character.line_no;
      token.line_pos = character.line_pos + 1;
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
	else if(character.c == '/') state = IN_SLASH;
	else if(character.c == '+') { state = READY_DONE; token.type = PLUS; }
	else if(character.c == '-') { state = READY_DONE; token.type = MINUS; }
	else if(character.c == '*') { state = READY_DONE; token.type = TIMES; }
	else if(character.c == '%') { state = READY_DONE; token.type = MODE; }
	else if(character.c == '(') { state = READY_DONE; token.type = LP; }
	else if(character.c == ')') { state = READY_DONE; token.type = RP; }
	else if(character.c == ',') { state = READY_DONE; token.type = COMMA; }
	else if(character.c == ';') { state = READY_DONE; token.type = SEMICO; }
	else if(character.c == '{') { state = READY_DONE; token.type = LB; }
	else if(character.c == '}') { state = READY_DONE; token.type = RB; }
	else if(character.c == EOF) { state = DONE; token.type = END_FILE; }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case INID:
	if(isdigit(character.c)) state = INID;
	else if(isalpha(character.c)) state = INID;
	else { state = DONE; token.type = ID; back_next_char(); }
	break;
      case INNUM:
	if(isdigit(character.c)) state = INNUM;
	else if(!isalpha(character.c)) { state = DONE; token.type = NUMBER; back_next_char(); }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case INSTRING:
	if(character.c == '\"') { state = READY_DONE; token.type = STR_CONST; }
	else state = INSTRING;
	break;
      case BEG_CHAR:
	state = END_CHAR;
	break;
      case END_CHAR:
	if(character.c == '\'') { state = READY_DONE; token.type = CHAR_CONST; }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case IN_EQ:
	if(character.c == '=') { state = DONE; token.type = EQ; back_next_char(); }
	else { state = DONE; token.type = ASSIGN; back_next_char(); }
	break;
      case IN_NEQ:
	if(character.c == '=') { state = DONE; token.type = NEQ; back_next_char(); }
	else { state = DONE; token.type = ERROR; back_next_char(); }
	break;
      case IN_LT:
	if(character.c == '=') { state = DONE; token.type = LTEQ; back_next_char(); }
	else { state = DONE; token.type = LT; back_next_char(); } 
	break;
      case IN_GT:
	if(character.c == '=') { state = DONE; token.type = GTEQ; back_next_char(); }
	else { state = DONE; token.type = GT; back_next_char(); }
	break;
      case IN_SLASH:
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
	if(character.c == '/') { state = READY_DONE; token.type = COMMENT; }
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
	token_string[token_string_index++] = (char) character.c;
      token_string[token_string_index] = '\0';
      if(token.type == ID)
	token.type = reserved_lookup(token_string);
    }
    else {
      if(state != START && (save) && (token_string_index <= MAX_TOKENLEN)) {
	token_string[token_string_index++] = (char) character.c;
      }
    }
  }
  token_no += 1;
  token.id = token_no;
  if(token.type == END_FILE)
    token.string = "EOF";
  else 
    token.string = token_string;
  return token;
}

void print_token(Token token) {
  printf("filename.c:%d:%d, token ID: %d, ", token.line_no, token.line_pos, token.id);
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
