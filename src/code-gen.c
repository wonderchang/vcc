#include "./include/main.h"
#include "./include/code-gen.h"

void code(ProgramState program_state) {
  switch(program_state) {
    case PROG_HDR: emit_prologue(); break;
    case PROG_END: emit_epilogue(); break;
    default: VC_ERR("Fucking program error. Unexpected condition"); break;
  }
}

void emit(char *opcode, char *op1, char *op2) {
  fprintf(obj_f, "\t%s", opcode);
  fprintf(obj_f, "\t%s", op1);
  if(op2 != NULL) 
    fprintf(obj_f, ", %s", op2);
  fprintf(obj_f, "\n");
}

void emit_label(int L) {
  fprintf(obj_f, "_L%d4d:\n", L);
}

void emit_prologue() {
  fprintf(obj_f, "section\t.text\n");
  fprintf(obj_f, "global\t_start\n");
  fprintf(obj_f, "_start:\n");
  emit_comments("\tThe main program begin");
  fprintf(obj_f, "\tint 80h\n");
}

void emit_epilogue() {
  emit_comments("\tExit program");
  fprintf(obj_f, "\tmov eax, 1\n");
  fprintf(obj_f, "\tmov ebx, 0\n");
  fprintf(obj_f, "\tint 80h\n\n");

  emit_comments("Data segment");
  emit_data_segment();
}

void emit_comments(char *comment) {
  fprintf(obj_f, "; %s\n", comment);
}

void emit_data_segment() {
  fprintf(obj_f, "section .data\n");
}

void emit_data_object() {
}

