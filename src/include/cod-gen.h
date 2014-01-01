void code(ProgramState program_state);
void emit(char *opcode, char *op1, char *op2);
void emit_label(int L);
void emit_prologue();
void emit_epilogue();
void emit_comments();
void emit_data_segment();
void emit_data_object();
