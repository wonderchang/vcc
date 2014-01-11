#include "./include/main.h"
#include "./act-rou.h"
#include "./include/reg-boo.h"

#define REG_NUM 6

typedef enum {
  EAX, EBX, ECX, EDX, ESI, EDI
}RegisterType;

SymbolNodePtr register_book[REG_NUM];

void reg_allocate();
void reg_free(RegisterType reg);
void reg_bookkeeping(RegisterType reg, SymbolNodePtr symbol);

void reg_allocate() {
}

void reg_free(RegisterType reg) {
}

