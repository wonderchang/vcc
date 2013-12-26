#include "global.h"
#include "scanner.h"
#include "code-gen.h"

int line_no;
int char_no;
FILE *source;
Token current_token;

void vcc_prologue();
void process_cmd_argu();
void start_up_process();
void clean_up_process();
void vcc_epilogue();

int main(int argc, char *argv[]) {

  line_no = 0;
  source = fopen(argv[1], "r");
  int error_level;

  vcc_prologue();

  process_cmd_argu();

  start_up_process();

  error_level = translate();

  clean_up_process();

  vcc_epilogue();

  fclose(source);

  exit(0);
}

void vcc_prologue() {
  //Display process start-up message
  //record data/time
}

void vcc_epilogue() {
  //Display process terminating message
  //record data/time
  //dislay statistics
}

void process_cmd_argu() {
  //Process the command line arguments
  //Check formats
}

void start_up_process() {
  //Initialize global data 
  //Create symbol table 
  //Initialize symbol table (e.g. reserved words) 
  //open required files
}

void clean_up_process() {
  //produce reference information
  //release symbol table
  //close files
  //other
}

