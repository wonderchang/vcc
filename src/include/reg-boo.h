#define REG_NUM 6

typedef enum {
  EAX, EBX, ECX, EDX, ESI, EDI
}RegisterType;

void reg_allocate();
void reg_free(RegisterType reg);
void reg_bookkeeping(RegisterType reg, SymbolNodePtr symbol);
