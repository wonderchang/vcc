#include "main.h"
#include "scanner.h"
#include "translator.h"
#include "code-gen.h"

Token current_token;
int error_level;

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
  return error_level;
}


void program() {
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
  if(current_token.type != LB)
    VC_ERR("{ missing");
  code(PROG_HDR);
  VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, NULL, NULL);
  if(current_token.type != END_FILE)
    DCL_LIST();
  VC_MATCH(RB);
  code(PROG_END);
}

void DCL_LIST() {
  //DCL_LIST -> (CONST_DCL | VAR_DCL) DCL_LIST
  while(current_token.type == CONST || is_datatype_except_const(current_token)){
    if(current_token == CONST)
      CONST_DCL();
    else
      VAR_DCL();
    if(current_token != SEMICO)
      VC_ERR("; missing");
    VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, NULL, NULL);
  }
}

void CONST_DCL() {
  //CONST_DCL -> const CONST_STMT (,CONST_STMT)
  current_token = get_token();
  VC_CHECK(ID, SEMICO, CONST, INT, CHAR, STRING, BOOL, RB, END_FILE);
  CONST_STMT();
  current_token = get_token();
  while(current_token == COMMA) {
    CONST_STMT();
    current_token = get_token();
  }
}

void CONST_STMT() {
  //CONST_STMT -> ID = ID | ID = LITERAL
  VC_CHECK(ID, SEMICO, CONST, INT, CHAR, STRING, BOOL, RB, END_FILE);
  Token data_type_token = get_token();
  current_token = get_token();
  if(current_token.type != ASSIGN)
    VC_ERR("Error token, require =");
  current_token = get_token();
  if(current_token.type == ID)
    create_id_val(current_token);
  else
    LITERAL(current_token);
  insert(data_type_token, current_token);
}

void LITERAL(Token token) {
  switch(token.type) {
    case NUMBER: create_number(token.string) break;
    case STRING_CONST: create_string(token.string) break;
    case CHAR_CONST: create_char(token.string) break;
    case BOOL_VAL: create_bool(token.string) break;
    default: VC_ERR("Fucking Program Error, Unexpected condition"); break;
  }
}

void VAR_DCL() {
  Token data_type_token = current_token;
  current_token = get_token();
  //VC_CHECK(ID, SEMICO, CONST, INT, CHAR, STRING, BOOL, RB, END_FILE);
  if(current_token.type == ID) {
    id_list_initialize(id_list);
    id_list_append(id_list, current_token);
  }
  else
    VC_ERR("Unexpected token. Require an identifier");
  current_token = get_token();

  while(current_token == COMMA) {
    VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, NULL, NULL);
    if(is_datatype_except_const(current_token)) {
      current_token = get_token();
      if(current_token == ID)
	id_list_append(id_list, current_token);
      else
	VC_ERR("Unexpected token. Require an identifier");
    }
    else
      VC_ERR("Unexpected data type");
    current_token = get_token();
  }
  if(current_token.type != SEMICO)
    VC_ERR("; expected");
}

int is_datatype_except_const(Token token) {
  if(token.type == INT || token.type == CHAR || token.type == STRING || token.type == BOOL)
    return 1;
  else 
    return 0;
}

void VC_ERR(char *err_message) {
  if(err_message != NULL)
    printf("%d:%d, Error: %s\n", line_no, line_pos, err_message);
}

void VC_MATCH(Token token) {
  if(current_token.type == token.type)
    current_token = get_token();
  else
    VCC_ERR("token expected");
}

void VC_CHECK(Token op, Token op1, Token o2, Token o3, Token o4, Token o5, Token op6, Token op7, Token op8) {
  while(current_token.type != op && current_token.type != op1 && current_token.type != op2 && current_token.type != op3 && current_token.type != op4 && current_token.type != op5 && crrrent_token != op6 && current_token.type != op7 current_token.type != op8) {
    current_token = get_token();
    VC_ERR("Unexpected token");
  }
}

