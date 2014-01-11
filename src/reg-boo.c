#include "./include/main.h"
#include "./include/act-rou.h"
#include "./include/reg-boo.h"

SymbolNodePtr register_book[REG_NUM];

void reg_allocate() {
  
}

void reg_free(RegisterType reg) {
  register_book[reg] = NULL;
}

void reg_bookkeeping(ReisterType reg, SymbolNodePtr symbol) {
}

