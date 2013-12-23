#include <stdio.h>

int main(int argc, char *argv[]) {

  vcc_prologue();
  process_cmd_argu();
  start_up_process();
  translate();
  clean_up_process();
  vcc_epilogue();

  return 0;
}

void vcc_prologue() {
  /*
   * Display process start-up message
   * record data/time
   * other
   */
}

void vcc_epilogue() {
  /*
   * Display process terminating message
   * record data/time
   * dislay statistics
   * other
   */
}

void process_cmd_argu() {
  /*
   * Process the command line arguments
   * Check formats
   */
}

void start_up_process() {
  /*
   * Initialize global data
   * Create symbol table
   * Initialize symbol table (e.g. reserved words)
   * open required files
   * other
   */
}

void clean_up_process() {
  /*
   * produce reference information
   * release symbol table
   * close files
   * other
   */
}

void translate() {
  current_token = get_token();
  if(current_token != EOF) {
    code("prog_hdr");
    do{
      current_token = get_token();
    }while(current_token != EOF);
    code("prog_end");
  }
}
