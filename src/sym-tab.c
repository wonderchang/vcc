#include "./include/main.h"
#include "./include/sym-tab.h"
#include "./include/act-rou.h"
#include "./include/err-han.h"

//The symbol table implemented by hash table and link list (extern)
SymbolNodePtr symbol_table[HASH_TABLE_SIZE];
SymbolNodePtr symbol_table_tail[HASH_TABLE_SIZE];

//The hash function
static int hash(char *key) {
  int tmp = 0;
  int i = 0;
  while (key[i] != '\0') { 
    tmp = (tmp + key[i]) % HASH_TABLE_SIZE;
    ++i;
  }
  return tmp;
}

//Initial the symbol table
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

//Create the symbol and initital the data
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

//Insert the symbol in to symbol table
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

//Search and retern the symbol in the symbol table
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

//Print the symbol table
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

//Print the detail information of symbol element
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


