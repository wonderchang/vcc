void code(Token operand1, Token op, Token operand2);
void emit(char *opcode, char *op1, char *op2);
void emit_label(int L);
void emit_prologue();
void emit_epilogue();
void emit_comments();
void emit_data_segment();
void emit_data_object();

void emit_assign();
void emit_plus();
void emit_minus();
void emit_times();
void emit_divide();
void emit_mode();
void emit_gt();
void emit_gte();
void emit_lt();
void emit_lte();
void emit_eq();
void emit_neq();
void emit_read();
void emit_print();
void emit_println();



