//The max length of the buffer that the longest line it can read
#define MAX_BUFLEN 256
//The max length of the token string
#define MAX_TOKENLEN 4096

//Function prototype
int get_next_char();
void back_next_char();
Token get_token();
void print_token(Token token);
void print_token_type(TokenType token_type);

