#include "./include/main.h"
#include "./include/err-han.h"
#include "./include/cod-gen.h"
#include "./include/sym-tab.h"
#include "./include/act-rou.h"

void code(Token operand2, Token op, Token operand1) {
  switch(op.type) {
    case ASSIGN: emit_assign(op, operand1, operand2); break;
    case PLUS: emit_plus(op, operand1, operand2); break;
    case MINUS: emit_minus(op, operand1, operand2); break;
    case TIMES: emit_times(op, operand1, operand2); break;
    case DIVIDE: emit_divide(op, operand1, operand2); break;
    case MODE: emit_mode(op, operand1, operand2); break;
    case GT: emit_gt(op, operand1, operand2); break;
    case GTEQ: emit_gte(op, operand1, operand2); break;
    case LT: emit_lt(op, operand1, operand2); break;
    case LTEQ: emit_lte(op, operand1, operand2); break;
    case EQ: emit_eq(op, operand1, operand2); break;
    case NEQ: emit_neq(op, operand1, operand2); break;
    case READ: emit_read(); break;
    case PRINT: emit_print(); break;
    case PRINTLN: emit_println(); break;
    default: VC_ERR("Fucking program error. Unexpected condition"); break;
  }
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


void emit_assign(Token op, Token op1, Token op2){ 
  printf("emit_assign, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_plus(Token op, Token op1, Token op2){ 
  printf("emit_plus, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_minus(Token op, Token op1, Token op2){ 
  printf("emit_minus, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_times(Token op, Token op1, Token op2){ 
  printf("emit_times, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_divide(Token op, Token op1, Token op2){ 
  printf("emit_divide, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_mode(Token op, Token op1, Token op2){ 
  printf("emit_mode, %s %s %s\n", op1.string, op.string, op2.string); 
}
void emit_gt(Token op, Token op1, Token op2){ printf("emit_gt\n"); }
void emit_gte(Token op, Token op1, Token op2){ printf("emit_gte\n"); }
void emit_lt(Token op, Token op1, Token op2){ printf("emit_lt\n"); }
void emit_lte(Token op, Token op1, Token op2){ printf("emit_lte\n"); }
void emit_eq(Token op, Token op1, Token op2){ printf("emit_eq\n"); }
void emit_neq(Token op, Token op1, Token op2){ printf("emit_neq\n"); }
void emit_read(){ printf("emit_read\n"); }
void emit_print(){ printf("emit_print\n"); }
void emit_println(){ printf("emit_println\n"); }


