#include "./include/main.h"
#include "./include/act-rou.h"
#include "./include/sym-tab.h"
#include "./include/err-han.h"

//Record the internal number name (extern)
int int_internal_num = 0;
int char_internal_num = 0;
int string_internal_num = 0;
int bool_internal_num = 0;

//The linked list stack top pointer, which only used in push_operand() and pop_operand
static TokenNodePtr operand_stack_top = NULL;

void create_id_val(Token token) {
  SymbolNodePtr current_symbol = st_lookup(token.string);
  if(current_symbol) {
    st_insert(pop_operand(), current_symbol->symbol.data_type, current_symbol->symbol.value, current_symbol->symbol.mode, current_symbol->symbol.allocation);
  }
  else {
    clean_err_msg();
    strcat(err_msg, "Use of undeclared identifier \'");
    strcat(err_msg, token.string);
    strcat(err_msg, "\'.");
    VC_ERR(err_msg);
  }
}
void create_number(Token token) {
  char value[MAX_TOKEN_LEN];
  strcpy(value, token.string);
  st_insert(pop_operand(), INT, value, 0, 4);
}
void create_char(Token token) {
  char value[MAX_TOKEN_LEN];
  strcpy(value, token.string);
  st_insert(pop_operand(), CHAR, value, 0, 1);
}
void create_string(Token token) {
  //Data declaration
  Token new_token;
  char value[MAX_TOKEN_LEN];
  char internal_name[6];
  char num_string[4];
  int i;
  for(i = 0; i < 6; i++) internal_name[i] = '\0';
  for(i = 0; i < 4; i++) num_string[i] = '\0';
  //Increment internal string variable number
  string_internal_num++;
  //Convert the number to string and store
  sprintf(num_string, "%d", string_internal_num);
  strcat(internal_name, "_s");
  strcat(internal_name, num_string);
  //Copy the string value
  strcpy(value, token.string);
  //Set the new token value
  strcpy(new_token.string, internal_name);
  new_token.type = STRING;
  //Insert the internal variable
  st_insert(new_token, STRING, value, 0, 1);
  //Insert the external varaible
  st_insert(pop_operand(), STRING, internal_name, 0, 4);
}

void create_bool(Token token) {
  //printf("token.string = %s, create_boolean\n", token.string);
  if(token.type == TRUE) 
    st_insert(pop_operand(), BOOL, "1", 0, 1);
  else
    st_insert(pop_operand(), BOOL, "0", 0, 1);
}

void push_operand(Token token) {
  char token_string[MAX_TOKEN_LEN];
  TokenNodePtr new_token_node;
  new_token_node = malloc(sizeof(TokenNodePtr));
  if(new_token_node != NULL) { 
    strcpy(token_string, token.string);
    new_token_node->token.type = token.type;
    strcpy(new_token_node->token.string, token_string);
    new_token_node->nextPtr = operand_stack_top;
    operand_stack_top = new_token_node;
  }
  else
    printf("%s not inserted. No memory available.\n", new_token_node->token.string);
}

Token pop_operand() {
  TokenNodePtr tmp_token;
  if(operand_stack_top == NULL)
    printf("The stack is empty, cannot pop\n");
  else {
    tmp_token = operand_stack_top;
    operand_stack_top = tmp_token->nextPtr;
  }
  return tmp_token->token;
}

void print_stack() {
  TokenNodePtr now_token = operand_stack_top;
  if(now_token == NULL)
    printf("Stack is empty.\n\n");
  else {
    printf("The list is:\n");
    while(now_token != NULL) {
      printf("%s -->", now_token->token.string);
      now_token = now_token->nextPtr;
    }
    printf("NULL\n\n");
  }
}


