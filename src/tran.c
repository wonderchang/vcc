#include "./include/main.h"
#include "./include/scan.h"
#include "./include/tran.h"
#include "./include/util.h"
#include "./include/err-han.h"
#include "./include/cod-gen.h"

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
  VC_MATCH(RB);
  code(PROG_END);
}

void DCL_LIST() {
  //DCL_LIST -> (CONST_DCL | VAR_DCL) DCL_LIST
  while(current_token.type == CONST || is_datatype_except_const(current_token)){
    if(current_token.type == CONST)
      CONST_DCL();
    else
      VAR_DCL();
    if(current_token.type != SEMICO)
      VC_ERR("; missing");
    current_token = get_token();
    VC_CHECK(CONST, INT, CHAR, STRING, BOOL, RB, END_FILE, END_FILE, END_FILE);
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
  }
}

void CONST_STMT() {
  //CONST_STMT -> ID = ID | ID = literal
  VC_CHECK(ID, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
  if(current_token.type == ID) {
    current_token = get_token();
    printf("constant ID / ");
    if(current_token.type != ASSIGN)
      VC_ERR("= expected");
    current_token = get_token();
    if(current_token.type == ID)
      printf("constant ID\n");//create_id_val(current_token);
    else
      literal(current_token);
    //printf("insert\n");
    //insert(data_type_token, current_token);
  }
  else
    VC_ERR("identifier expected");
}

void VAR_DCL() {
  TokenType data_type = current_token.type;
  current_token = get_token();
  if(current_token.type != ID)
    VC_ERR("identifier expected");
  current_token = get_token();
  VC_CHECK(COMMA, SEMICO, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE, END_FILE);
  if(current_token.type != COMMA)
    if(current_token.type != SEMICO) 
      VC_ERR(", expected");
  while(current_token.type == COMMA) {
    current_token = get_token();
    if(current_token.type != ID)
      VC_ERR("identifier expected");
    current_token = get_token();
  }
}

void literal(Token token) {
  switch(token.type) {
    case NUMBER: printf("literal number\n"); /*create_number(token.string)*/ break;
    case STR_CONST: printf("literal string\n"); /*create_string(token.string)*/ break;
    case CHAR_CONST: printf("literal char\n"); /*create_char(token.string)*/ break;
    case TRUE: printf("literal bool ture\n");/* create_bool(token.string)*/ break;
    case FALSE: printf("literal bool false\n");/* create_bool(token.string)*/ break;
    default: VC_ERR("constant value expected"); break;
  }
}




