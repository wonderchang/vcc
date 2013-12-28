#include "main.h"
#include "scanner.h"
#include "code-gen.h"

int line_no;
int line_pos;
FILE *src_f;
FILE *obj_f;
FILE *err_f;

void vcc_prologue();
void process_cmd_argu();
void start_up_process();
void clean_up_process();
void vcc_epilogue();

int main(int argc, char *argv[]) {

  line_no = 0;
  line_pos = 0;

  vcc_prologue();
  process_cmd_argu(argv[1]);
  start_up_process();
  translate();
  clean_up_process();
  vcc_epilogue();

  return 0;
}

void vcc_prologue() {
  //Display process start-up message
  //record data/time
  printf("\nVenilla-C Compiler\n");
  printf("Start to compile.\n");
}

void vcc_epilogue() {
  //Display process terminating message
  //record data/time
  //dislay statistics
  printf("Compile completed.\n\n");
}

void process_cmd_argu(char *filename) {
  //Process the command line arguments
  //Check formats
  if(filename != NULL) {
    src_f = fopen(filename, "r");
    obj_f = fopen("output", "w");
    err_f = fopen("error", "w");
  }
  else {
    printf("Comman line error: Require the input file in the argument\n");
    exit(1);
  }
}

void start_up_process() {
  //Initialize global data 
  //Create symbol table 
  //Initialize symbol table (e.g. reserved words) 
  //open required files
  printf("Start up process.\n");
}

void clean_up_process() {
  //produce reference information
  //release symbol table
  //close files
  //other
  fclose(src_f);
  fclose(obj_f);
  fclose(err_f);
  printf("Clean up process.\n");
}

