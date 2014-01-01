#include "./include/main.h"
#include "./include/scan.h"
#include "./include/code-gen.h"

int line_no;
int line_pos;
FILE *src_f;
char *src_name;
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
  src_name = argv[1];

  vcc_prologue();
  process_cmd_argu();
  start_up_process();
  translate();
  clean_up_process();
  vcc_epilogue();

  return 0;
}

void vcc_prologue() {
  //Display process start-up message
  //record data/time
  printf("\nVenilla-C Compiler version 1.0\n");
  printf("-Implement by student Wonder Chang.\n");
  printf("-Compiler course from NCKU EE.\n");
  printf("-Teacher: Jing Chen.\n");
  printf("\nStart to compile. The input file: %s\n", src_name);
}

void vcc_epilogue() {
  //Display process terminating message
  //record data/time
  //dislay statistics
  printf("\nCompile completed.\n");
}

void process_cmd_argu() {
  //Process the command line arguments
  //Check formats
  if(src_name != NULL) {
    src_f = fopen(src_name, "r");
    obj_f = fopen("test.asm", "w");
    err_f = fopen("test.err", "w");
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
  printf("\nStart up process.\n");
}

void clean_up_process() {
  //produce reference information
  //release symbol table
  //close files
  //other
  fclose(src_f);
  fclose(obj_f);
  fclose(err_f);
  printf("\nClean up process.\n");
}

