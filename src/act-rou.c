#include "./include/main.h"
#include "./include/act-rou.h"
#include "./include/err-han.h"

SymbolNodePtr symbol_table[HASH_TABLE_SIZE];
SymbolNodePtr symbol_table_tail[HASH_TABLE_SIZE];
TokenNodePtr operand_stack_top = NULL;
int int_internal_num = 0;
int char_internal_num = 0;
int string_internal_num = 0;
int bool_internal_num = 0;

static int hash(char *key) {
  int tmp = 0;
  int i = 0;
  while (key[i] != '\0') { 
    tmp = (tmp + key[i]) % HASH_TABLE_SIZE;
    ++i;
  }
  return tmp;
}

void st_initialize() {
  int i;
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    symbol_table[i] = NULL;
    symbol_table_tail[i] = symbol_table[i];
  }
}

void st_insert(Token token, TokenType data_type, char *value, int mode, int allocation) { 

  SymbolNodePtr new_symbol_node;

  char id[MAX_TOKEN_LEN];
  char new_value[MAX_TOKEN_LEN];
  int i = 0;
  int index;
  for(i = 0; i < MAX_TOKEN_LEN; i++) { id[i] = '\0'; new_value[i] = '\0'; }
  i = 0;
  while(token.string[i] != '\0') { id[i] = token.string[i]; i++; }
  i = 0;
  while(value[i] != '\0') { new_value[i] = value[i]; i++; }

  new_symbol_node = malloc(sizeof(SymbolNode));
  strcpy(new_symbol_node->symbol.name, id);
  new_symbol_node->symbol.data_type = data_type;
  new_symbol_node->symbol.mode = mode; 
  strcpy(new_symbol_node->symbol.value, new_value);
  new_symbol_node->symbol.allocation = allocation;

  index = hash(new_symbol_node->symbol.name);

  if(symbol_table[index] == NULL) {
    symbol_table[index] = new_symbol_node;
    symbol_table_tail[index] = new_symbol_node;
  }
  else {
    if(st_lookup(new_symbol_node->symbol.name) != NULL) {
      clean_err_msg();
      strcat(err_msg, "The identifier ");
      strcat(err_msg, new_symbol_node->symbol.name);
      strcat(err_msg, " has been declaration before.");
      VC_ERR(err_msg);
    }
    else {
      symbol_table_tail[index]->nextPtr = new_symbol_node;
      symbol_table_tail[index] = new_symbol_node;
    }
  }
}

SymbolNodePtr st_lookup(char *key) {
  int index = hash(key);
  SymbolNodePtr current_symbol = symbol_table[index];
  while(current_symbol != NULL) {
    if(strcmp(key, current_symbol->symbol.name) == 0)
      return current_symbol;
    else
      current_symbol = current_symbol->nextPtr;
  }
  return NULL;
}

void print_symbol_table() {
  int i;
  SymbolNodePtr tmp_symbol;
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    tmp_symbol = symbol_table[i];
    printf("[%d] --> ", i);
    while(tmp_symbol != NULL) {
      //printf("%s -->", tmp_symbol->symbol.name);
      print_symbol_info(tmp_symbol);
      tmp_symbol = tmp_symbol->nextPtr;
    }
    printf("NULL\n");
  }
}

void print_symbol_info(SymbolNodePtr current_symbol) {
  printf("------------------------------\n");
  printf("Address: %p\n", current_symbol);
  printf("(%p) Symbol: %s\n", &(current_symbol->symbol.name), current_symbol->symbol.name);
  switch(current_symbol->symbol.data_type) {
    case INT: printf("(%p) Datatype: %s\n", &(current_symbol->symbol.data_type), "int"); break;
    case CHAR: printf("(%p) Datatype: %s\n", &(current_symbol->symbol.data_type), "char"); break;
    case STRING: printf("(%p) Datatype: %s\n", &(current_symbol->symbol.data_type), "string"); break;
    case BOOL: printf("(%p) Datatype: %s\n", &(current_symbol->symbol.data_type), "bool"); break;
    default:break;
  }
  printf("(%p) Mode: %d\n", &(current_symbol->symbol.mode), current_symbol->symbol.mode);
  printf("(%p) Value: %s\n", &(current_symbol->symbol.value), current_symbol->symbol.value);
  printf("(%p) Allocation: %d\n", &(current_symbol->symbol.allocation), current_symbol->symbol.allocation);
  printf("------------------------------\n");
}



void create_id_val(Token token) {
  //printf("token.string = %s, create_id_value\n", token.string);
  SymbolNodePtr current_symbol = st_lookup(token.string);
  if(current_symbol) {
    st_insert(pop_operand(), current_symbol->symbol.data_type, current_symbol->symbol.value, current_symbol->symbol.mode, current_symbol->symbol.allocation);
  }
  else {
    clean_err_msg();
    strcat(err_msg, "The varaible \'");
    strcat(err_msg, token.string);
    strcat(err_msg, "\' have not been declaraed before.");
    VC_ERR(err_msg);
  }
}
void create_number(Token token) {
  //printf("token.string = %s, create_number\n", token.string);
  char value[MAX_TOKEN_LEN];
  strcpy(value, token.string);
  st_insert(pop_operand(), INT, value, 0, 4);
}
void create_char(Token token) {
  //printf("token.string = %s, create_char\n", token.string);
  char value[MAX_TOKEN_LEN];
  strcpy(value, token.string);
  st_insert(pop_operand(), CHAR, value, 0, 1);
}
void create_string(Token token) {
  //printf("token.string = %s, create_string\n", token.string);
  char value[MAX_TOKEN_LEN];
  char internal_name[6];
  char num_string[4];
  string_internal_num++;
  sprintf(num_string, "%d", string_internal_num);
  strcat(internal_name, "_s");
  strcat(internal_name, num_string);
  strcpy(value, token.string);
  st_insert_internal(internal_name, STRING, value);
  st_insert(pop_operand(), STRING, internal_name, 0, 4);
}
void create_bool(Token token) {
  //printf("token.string = %s, create_boolean\n", token.string);
  if(token.type == TRUE) 
    st_insert(pop_operand(), BOOL, "1", 0, 1);
  else
    st_insert(pop_operand(), BOOL, "0", 0, 1);
}

void st_insert_internal(char *internal_name, TokenType data_type, char *value) {
  SymbolNodePtr new_symbol_node;
  char id[MAX_TOKEN_LEN];
  char new_value[MAX_TOKEN_LEN];
  int i = 0;
  int index;
  for(i = 0; i < MAX_TOKEN_LEN; i++) { id[i] = '\0'; new_value[i] = '\0'; }
  i = 0;
  while(internal_name[i] != '\0') { id[i] = internal_name[i]; i++; }
  i = 0;
  while(value[i] != '\0') { new_value[i] = value[i]; i++; }

  new_symbol_node = malloc(sizeof(SymbolNode));
  strcpy(new_symbol_node->symbol.name, internal_name);
  new_symbol_node->symbol.data_type = data_type;
  strcpy(new_symbol_node->symbol.value, new_value);
  new_symbol_node->symbol.mode = 0;
  new_symbol_node->symbol.allocation = 1;

  index = hash(internal_name);
  symbol_table_tail[index]->nextPtr = new_symbol_node;
  symbol_table_tail[index] = new_symbol_node;

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
    //printf("Push %s into the stack.\n", new_token_node->token.string);
  }
  else
    printf("%s not inserted. No memory available.\n", new_token_node->token.string);
  //print_stack();
}

Token pop_operand() {
  
  TokenNodePtr tmp_token;
  if(operand_stack_top == NULL)
    printf("The stack is empty, cannot pop\n");
  else {
    tmp_token = operand_stack_top;
    operand_stack_top = tmp_token->nextPtr;
  }
  //print_stack();
  return tmp_token->token;
}

void print_stack() {
  TokenNodePtr now_token = operand_stack_top;
  if(now_token == NULL)
    printf("Stack is empty.\n\n");
  else {
    printf("The list is:\n");
    while(now_token != NULL) {
      //printf("operand_stack_top = %p\n", operand_stack_top);
      //printf("now_token = %p\n", now_token);
      printf("%s -->", now_token->token.string);
      now_token = now_token->nextPtr;
    }
    printf("NULL\n\n");
  }
}


