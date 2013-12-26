#include "global.h"

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
  fprintf(obj_f, "_L%s4d:\n", L);
}

void emit_prologue() {
  fprintf(obj_f, "TITLE\t%s\n", PROG_FILE);
  fprintf(obj_f, "INCLUDE Irvine32.inc\n");
  fprintf(obj_f, ".STACK\t2048\n");
  fprintf(obj_f, ".CODE\n");
  fprintf(obj_f, "_main\tPROC\n");
}

void emit_epilogue() {
  fprintf(obj_c, "\texit\n");
  fprintf(obj_c, "_main\tENDP\n");
  emit_data_segment();
  fprintf(obj_c, "\tEND\t_main\n");
}

void emit_comments() {
  fprintf(obj_f, "; %s\n", comment);
}

void emit_data_segment(char *comment) {
  fprintf(obj_f, ".DATA\n");
}

void emit_data_object() {
}

