#define HASH_TABLE_SIZE 3

//Structure of symbol data
typedef struct {
  char name[MAX_TOKEN_LEN];
  TokenType data_type;
  int mode;
  char value[MAX_TOKEN_LEN];
  int allocation; } Symbol; struct symbol_node{
  Symbol symbol;
  struct symbol_node *nextPtr;
};

typedef struct symbol_node SymbolNode;
typedef SymbolNode *SymbolNodePtr;

static int hash(char *key);
void st_initialize();
void st_insert(Token token, TokenType data_type, char *value, int mode, int allocation);
SymbolNodePtr st_lookup(char *key);
SymbolNodePtr create_symbol(char *name, TokenType data_type, char *value, int mode, int allocation);

void id_list_initialize();
void insert_id_list();
void print_id_list();
void print_symbol_info();
void print_symbol_table();

void create_id_val(Token token);
void create_number(Token token);
void create_char(Token token);
void create_string(Token token);
void create_bool(Token token);

struct token_node {
  Token token;
  struct token_node *nextPtr;
};

typedef struct token_node TokenNode;
typedef TokenNode *TokenNodePtr;

void push_operand(Token token);
Token pop_operand();
void print_stack();


