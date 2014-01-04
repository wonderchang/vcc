#include "./include/main.h"
#include "./include/act-rou.h"
#include "./include/err-han.h"

SymbolNodePtr symbol_table[HASH_TABLE_SIZE];
SymbolNodePtr symbol_table_tail[HASH_TABLE_SIZE];

void insert_var_symbol_table(TokenType data_type, char *id_name) {
  char id[ID_LEN];
  int i = 0;
  int index;
  SymbolNodePtr new_symbol_node;
  SymbolNodePtr current_symbol;
  for(i = 0; i < ID_LEN; i++)
    id[i] = '\0';
  i = 0;
  while(id_name[i] != '\0') {
    id[i] = id_name[i];
    i++;
  }
  new_symbol_node = malloc(sizeof(SymbolNode));
  strcpy(new_symbol_node->symbol.name, id);
  new_symbol_node->symbol.data_type = data_type;
  new_symbol_node->symbol.mode = 1;
  switch(data_type) {
    case INT:
      new_symbol_node->symbol.value = "0";
      new_symbol_node->symbol.allocation = 4;
      break;
    case CHAR:
      new_symbol_node->symbol.value = " ";
      new_symbol_node->symbol.allocation = 1;
      break;
    case STRING:
      new_symbol_node->symbol.value = "";
      new_symbol_node->symbol.allocation = 4;
      break;
    case BOOL:
      new_symbol_node->symbol.value = "0";
      new_symbol_node->symbol.allocation = 1;
      break;
    default:
      printf("Program Error. Fucking bug in id_list_append functino\n");
      break;
  }
  index = hash(new_symbol_node->symbol.name);
  if(symbol_table[index] == NULL) {
    symbol_table[index] = new_symbol_node;
    symbol_table_tail[index] = new_symbol_node;
  }
  else {
    if(st_lookup(new_symbol_node->symbol.name)) {
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

int st_lookup(char *key) {
  int index = hash(key);
  SymbolNodePtr current_symbol = symbol_table[index];
  while(current_symbol != NULL) {
    if(strcmp(key, current_symbol->symbol.name) == 0)
      return 1;
    else
      current_symbol = current_symbol->nextPtr;
  }
  return 0;
}




void print_symbol_table() {
  int i;
  SymbolNodePtr tmp_symbol;
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    tmp_symbol = symbol_table[i];
    printf("[%d] --> ", i);
    while(tmp_symbol != NULL) {
      printf("%s -->", tmp_symbol->symbol.name);
      tmp_symbol = tmp_symbol->nextPtr;
    }
    printf("NULL\n");
  }
}

void print_symbol_info() {
  SymbolNodePtr current_symbol = id_list_head;
  printf("------------------------------\n");
  printf("Address: %p\n", current_symbol);
  printf("(%p) Symbol: %s\n", &(current_symbol->symbol.name), current_symbol->symbol.name);
  printf("(%p) Datatype: %d\n", &(current_symbol->symbol.data_type), current_symbol->symbol.data_type);
  printf("(%p) Mode: %d\n", &(current_symbol->symbol.mode), current_symbol->symbol.mode);
  printf("(%p) Value: %s\n", &(current_symbol->symbol.value), current_symbol->symbol.value);
  printf("(%p) Allocation: %d\n", &(current_symbol->symbol.allocation), current_symbol->symbol.allocation);
  printf("------------------------------\n");
}



void create_id_val(Token token) {
}
void create_number(Token token) {
}
void create_char(Token token) {
}
void create_string(Token token) {
}
void create_bool(Token token) {
}


/*
void push_operand(NodePtr *top, int data) {
  NodePtr new_node_ptr;
  new_node_ptr = malloc(sizeof(Node));
  if(new_node_ptr != NULL) { 
    new_node_ptr->data = data;
    new_node_ptr->nextPtr = *top;
    *top = new_node_ptr;
    printf("Push %d into the stack.\n", data);
  }
  else
    printf("%d not inserted. No memory available.\n", data);
  print_stack(*top);
}

NodePtr pop_operand(NodePtr *top) {
  
  NodePtr tmp_node_ptr;
  if(top == NULL)
    printf("The stack is empty, cannot pop\n");
  else {
    tmp_node_ptr = *top;
    *top = tmp_node_ptr->nextPtr;
  }
  print_stack(*top);
  return tmp_node_ptr;
}

void print_stack(NodePtr currentPtr) {
  if(currentPtr == NULL)
    printf("Stack is empty.\n\n");
  else {
    printf("The list is:\n");
    while(currentPtr != NULL) {
      printf("%d -->", currentPtr->data);
      currentPtr = currentPtr->nextPtr;
    }
    printf("NULL\n\n");
  }
}

*/

