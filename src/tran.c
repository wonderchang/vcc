#include "./include/main.h"
#include "./include/scan.h"
#include "./include/tran.h"
#include "./include/util.h"
#include "./include/err-han.h"
#include "./include/cod-gen.h"
#include "./include/act-rou.h"


int translate() {
  current_token = get_token();
  if(current_token.type != END_FILE) {
    program(current_token);
    if(current_token.type != END_FILE) {
      VC_ERR("Extra chars after program ending");
    }
  }
  else {
    VC_ERR("The file is empty");
  }
  return 0;
}


void program() {
  while(current_token.type == COMMENT) 
    current_token = get_token();
  if(current_token.type != MAIN) 
    VC_ERR("main expected");
  pro_hdr(current_token);
  pro_body(current_token);
}

void pro_hdr() {
  while(current_token.type == COMMENT)
    current_token = get_token();
  VC_MATCH(MAIN);
  VC_MATCH(LP);
  VC_MATCH(RP);
}

void pro_body() {
  VC_MATCH(LB);
  code(PROG_HDR);
  VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, END_FILE, END_FILE);
  if(current_token.type != END_FILE)
    DCL_LIST();
  printf("DCL_LIST is over\n");
  if(current_token.type != RB)
    STMT_LIST();
  VC_MATCH(RB);
  code(PROG_END);
}

void DCL_LIST() {
  //DCL_LIST -> (CONST_DCL | VAR_DCL) DCL_LIST
  while(current_token.type == CONST || is_datatype(current_token.type)){
    if(current_token.type == CONST)
      CONST_DCL();
    else
      VAR_DCL();
    if(current_token.type != SEMICO)
      VC_ERR("; missing");
    current_token = get_token();
    //VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, END_FILE, END_FILE);
  }
}

void CONST_DCL() {
  //CONST_DCL -> const CONST_STMT (,CONST_STMT)
  current_token = get_token();
  CONST_STMT();
  current_token = get_token();
  VC_CHECK(COMMA, SEMICO, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
  while(current_token.type == COMMA) {
    current_token = get_token();
    CONST_STMT();
    current_token = get_token();
    VC_CHECK(COMMA, SEMICO, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
    if(current_token.type != COMMA)
      if(current_token.type != SEMICO) 
	VC_ERR("Token \',\' expected");
  }
}

void CONST_STMT() {
  //CONST_STMT -> ID = ID | ID = literal
  VC_CHECK(ID, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
  if(current_token.type == ID) {
    push_operand(current_token);
    current_token = get_token();
    if(current_token.type != ASSIGN)
      VC_ERR("Token \'=\' expected");
    current_token = get_token();
    switch(current_token.type) {
      case ID: create_id_val(current_token); break;
      case NUMBER: create_number(current_token); break;
      case STR_CONST: create_string(current_token); break;
      case CHAR_CONST: create_char(current_token); break;
      case TRUE: create_bool(current_token); break;
      case FALSE: create_bool(current_token); break;
      default: VC_ERR("constant value expected"); break;
    }
  }
  else
    VC_ERR("identifier expected");
}

void VAR_DCL() {
  //VAR_DCL -> DATA_TYPE ID_LIST
  TokenType data_type = current_token.type;
  int mode = 1;
  char *value;
  int allocation;
  if(is_datatype(data_type)) {
    switch(data_type) {
      case INT: value = "0"; allocation = 4; break;
      case CHAR: value = " "; allocation = 1; break;
      case STRING: value = "_s1"; allocation = 4; break;
      case BOOL: value = "0"; allocation = 1; break;
      default:
	printf("Program Error. Fucking bug in VAR_DCL.\n");
	break;
    }
    current_token = get_token();
    if(current_token.type == ID)
      st_insert(current_token, data_type, value, mode, allocation);
    else
      VC_ERR("identifier expected");
    current_token = get_token();
    VC_CHECK(COMMA, SEMICO, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
    if(current_token.type != COMMA)
      if(current_token.type != SEMICO) 
	VC_ERR(", expected");
    while(current_token.type == COMMA) {
      current_token = get_token();
      if(current_token.type == ID)
        st_insert(current_token, data_type, value, mode, allocation);
      else
	VC_ERR("identifier expected");
      current_token = get_token();
    }
  }
  else 
    VC_ERR("data type declaration expected");
}

void STMT_LIST() {
  while(current_token.type != RB) {
    STATEMENT(current_token);
    if(current_token.type == SEMICO)
      current_token = get_token();
  }
}

void STATEMENT(Token token) {
  switch(token.type) {
    case ID: ASSIGN_STMT(token); break;
    case READ: READ_STMT(token); break;
    case PRINT: PRINT_STMT(token); break;
    case PRINTLN: PRINT_STMT(token); break;
    case IF: IF_STMT(token); break;
    case WHILE: WHILE_STMT(token); break;
    default: break;
  }
}

void ASSIGN_STMT(Token token) {
  if(token.type != ID)
    printf("ASSIGN_STMT's should be starting in ID token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}

void READ_STMT(Token token) {
  if(token.type != READ)
    printf("READ_STMT's should be starting in READ token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}

void PRINT_STMT(Token token) {
  if(token.type != PRINT)
    printf("PRINT_STMT's should be starting in PRINT token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}

void PRINTLN_STMT(Token token) {
  if(token.type != PRINTLN)
    printf("PRINTLN_STMT's should be starting in PRINTLN token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}

void IF_STMT(Token token) {
  if(token.type != IF)
    printf("IF_STMT's should be starting in IF token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}

void WHILE_STMT(Token token) {
  if(token.type != WHILE)
    printf("WHILE_STMT's should be starting in WHILE token\n");
  else {
    while(current_token.type != SEMICO) 
      current_token = get_token();
  }
}


