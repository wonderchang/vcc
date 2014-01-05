#define ERR_MSG_LEN 256
extern char err_msg[ERR_MSG_LEN];
extern int err_count;
void VC_ERR(char *err_message);
void VC_MATCH(TokenType token_type);
void VC_CHECK(TokenType op, TokenType op1, TokenType op2, TokenType op3, TokenType op4, TokenType op5, TokenType op6, TokenType op7, TokenType op8);
void remove_output_file();
void clean_err_msg();
