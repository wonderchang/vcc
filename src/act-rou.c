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
  Token new_token;
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    symbol_table[i] = NULL;
    symbol_table_tail[i] = symbol_table[i];
  }
  strcpy(new_token.string, "_s1");
  new_token.type = STRING;
  st_insert(new_token, STRING, "", 0, 1);
  string_internal_num++;
}

SymbolNodePtr create_symbol(char *name, TokenType data_type, char *value, int mode, int allocation) {
  //Data declaration
  SymbolNodePtr new_symbol_node;
  char symbol_name[MAX_TOKEN_LEN];
  char symbol_value[MAX_TOKEN_LEN];
  int i = 0;
  int index;
  //Allocation the memory for the symbol node
  new_symbol_node = malloc(sizeof(SymbolNode));
  //Initilaize string data
  for(i = 0; i < MAX_TOKEN_LEN; i++) { symbol_name[i] = '\0'; symbol_value[i] = '\0'; }
  i = 0;
  while(name[i] != '\0') { symbol_name[i] = name[i]; i++; }
  i = 0;
  while(value[i] != '\0') { symbol_value[i] = value[i]; i++; }
  //Set the symbol node structure data
  strcpy(new_symbol_node->symbol.name, symbol_name);
  new_symbol_node->symbol.data_type = data_type;
  new_symbol_node->symbol.mode = mode;
  strcpy(new_symbol_node->symbol.value, symbol_value);
  new_symbol_node->symbol.allocation = allocation;
  //return the symbol node
  return new_symbol_node;
}

void st_insert(Token token, TokenType data_type, char *value, int mode, int allocation) { 
  //Create the new symbol node
  SymbolNodePtr new_symbol_node = create_symbol(token.string, data_type, value, mode, allocation);
  //Get the hash key for this symbol node
  int index = hash(new_symbol_node->symbol.name);
  //Insert the symbol node into symbol table
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
    printf("[%d]\n", i);
    while(tmp_symbol != NULL) {
      //printf("%s -->", tmp_symbol->symbol.name);
      print_symbol_info(tmp_symbol);
      tmp_symbol = tmp_symbol->nextPtr;
    }
    printf(" --> NULL\n");
  }
}

void print_symbol_info(SymbolNodePtr current_symbol) {
  printf(" --> ");
  switch(current_symbol->symbol.data_type) {
    case INT: printf("Datatype: int   \t"); break;
    case CHAR: printf("Datatype: char  \t"); break;
    case STRING: printf("Datatype: string\t"); break;
    case BOOL: printf("Datatype: bool  \t"); break;
    default:break;
  }
  printf("Mode: %d \t", current_symbol->symbol.mode);
  printf("Allocation: %d\t", current_symbol->symbol.allocation);
  printf("Symbol: %s\t", current_symbol->symbol.name);
  printf("Value: %s\n", current_symbol->symbol.value);
}



void create_id_val(Token token) {
  //printf("token.string = %s, create_id_value\n", token.string);
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


