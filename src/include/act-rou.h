
//Record the internal number name
extern int int_internal_num;
extern int char_internal_num;
extern int string_internal_num;
extern int bool_internal_num;

//Create the varaible declaration
void create_id_val(Token token);
void create_number(Token token);
void create_char(Token token);
void create_string(Token token);
void create_bool(Token token);

//Token stack data structure
struct token_node {
  Token token;
  struct token_node *nextPtr;
};
typedef struct token_node TokenNode;
typedef TokenNode *TokenNodePtr;

//Push token as operand into stack
void push_operand(Token token);
//Pop and return token as operand out token
Token pop_operand();
//Print the stack element
void print_stack();


