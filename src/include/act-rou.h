#define HASH_TABLE_SIZE 3
#define ID_LEN 64

//Structure of symbol data
typedef struct {
  char name[ID_LEN];
  TokenType data_type;
  int mode;
  char *value;
  int allocation;
} Symbol;

struct symbol_node{
  Symbol symbol;
  struct symbol_node *nextPtr;
};

typedef struct symbol_node SymbolNode;
typedef SymbolNode *SymbolNodePtr;

SymbolNodePtr id_list_head;
SymbolNodePtr id_list_tail;

static int hash(char *key);
void st_initialize();
int st_lookup(char *key);

void id_list_initialize();
void insert_var_symbol_table(TokenType data_type, char *id_name);
void insert_id_list();
void print_id_list();
void print_symbol_info();
void insert_symbol_table();
void print_symbol_table();

void create_id_val(Token token);
void create_number(Token token);
void create_char(Token token);
void create_string(Token token);
void create_bool(Token token);

/*

struct node {
  int data;
  struct node nextPtr;
}

typedef struct node Node;
typedef Node NodePtr;


void push(NodePtr *top, int data);
NodePtr pop(NodePtr *top);
void print_stack(NodePtr currentPtr);

*/

