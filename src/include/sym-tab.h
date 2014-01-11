//The size of hash table
#define HASH_TABLE_SIZE 3

//The structure of symbol data
typedef struct {
  char name[MAX_TOKEN_LEN];
  TokenType data_type;
  int mode;
  char value[MAX_TOKEN_LEN];
  int allocation; 
} Symbol; 
struct symbol_node{
  Symbol symbol;
  struct symbol_node *nextPtr;
};
typedef struct symbol_node SymbolNode;
typedef SymbolNode *SymbolNodePtr;

//The symbol table implemented by hash table and link list
extern SymbolNodePtr symbol_table[HASH_TABLE_SIZE];
extern SymbolNodePtr symbol_table_tail[HASH_TABLE_SIZE];

//The hash function
static int hash(char *key);

//Initial the symbol table
void st_initialize();
//Create and return the initailizing symbol
SymbolNodePtr create_symbol(char *name, TokenType data_type, char *value, int mode, int allocation);
//Insert the symbol in to symbol table
void st_insert(Token token, TokenType data_type, char *value, int mode, int allocation);
//Search and retern the symbol in the symbol table
SymbolNodePtr st_lookup(char *key);
//Print the symbol table
void print_symbol_table();
//Print the detail information of symbol element
void print_symbol_info();
