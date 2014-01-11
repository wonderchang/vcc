#include "./include/main.h"
#include "./include/err-han.h"
#include "./include/cod-gen.h"
#include "./include/act-rou.h"

void code(ProgramState program_state) {
  switch(program_state) {
    case PROG_HDR: emit_prologue(); break;
    case PROG_END: emit_epilogue(); break;
    case ASSIGN_OP: emit_assign(); break;
    case PLUS_OP: emit_plus(); break;
    case MINUS_OP: emit_minus(); break;
    case TIMES_OP: emit_times(); break;
    case DIVIDE_OP: emit_divide(); break;
    case MODE_OP: emit_mode(); break;
    case GT_OP: emit_gt(); break;
    case GTE_OP: emit_gte(); break;
    case LT_OP: emit_lt(); break;
    case LTE_OP: emit_lte(); break;
    case EQ_OP: emit_eq(); break;
    case NEQ_OP: emit_neq(); break;
    case READ_OP: emit_read(); break;
    case PRINT_OP: emit_print(); break;
    case PRINTLN_OP: emit_println(); break;
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
  //fprintf(obj_f, "\tint 80h\n");
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
  int i;
  SymbolNodePtr current_symbol;
  fprintf(obj_f, "section .data\n");
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    if(symbol_table[i] != NULL) {
      current_symbol = symbol_table[i];
      while(current_symbol != NULL) {
	emit_data_object(current_symbol);
	current_symbol = current_symbol->nextPtr;
      }
    }
  }
  
}

void emit_data_object(SymbolNodePtr symbol) {
  fprintf(obj_f, "\t%s", symbol->symbol.name);
  switch(symbol->symbol.allocation) {
    case 1: fprintf(obj_f, "\t%s", "db"); break;
    case 2: fprintf(obj_f, "\t%s", "dw"); break;
    case 4: fprintf(obj_f, "\t%s", "dd"); break;
    default: printf("Program Error: Fucking bug error in emit_data_object."); break;
  }
  if(symbol->symbol.data_type == CHAR)
    fprintf(obj_f, "\t\'%s\'\n", symbol->symbol.value);
  else if(symbol->symbol.data_type == STRING) 
    if(symbol->symbol.value[0] == '_' && symbol->symbol.value[1] == 's')
      fprintf(obj_f, "\t%s\n", symbol->symbol.value);
    else 
      fprintf(obj_f, "\t\"%s\"\n", symbol->symbol.value);
  else 
    fprintf(obj_f, "\t%s\n", symbol->symbol.value);
}


void emit_assign(){}
void emit_plus(){}
void emit_minus(){}
void emit_times(){}
void emit_divide(){}
void emit_mode(){}
void emit_gt(){}
void emit_gte(){}
void emit_lt(){}
void emit_lte(){}
void emit_eq(){}
void emit_neq(){}
void emit_read(){}
void emit_print(){}
void emit_println(){}


