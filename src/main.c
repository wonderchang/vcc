#include "./include/main.h"
#include "./include/scan.h"
#include "./include/tran.h"
#include "./include/util.h"
#include "./include/act-rou.h"
#include "./include/sym-tab.h"
#include "./include/err-han.h"
#include "./include/dbg-aid.h"
#include "./include/cod-gen.h"


//Record which line is processing now
int token_line_no;
//Record the first letter position of the token in the line which is processing now
int token_line_pos;
//The current token that processing now
Token current_token;

//The input file name, or say the program we want to compile
char *src_name;
//The input file pointer
FILE *src_f;

//There are 3 output file that we want and set it file pointer:
//1. Object code file pointer
FILE *obj_f;
char obj_name[FILE_NAME_LEN];
//2. Error Report file pointer
FILE *err_f;
char err_name[FILE_NAME_LEN];
//3. Source listing file pointer
FILE *lst_f;
char lst_name[FILE_NAME_LEN];

int main(int argc, char *argv[]) {

  //Data initialization
  src_name = argv[1];

  //Start to process
  vcc_prologue();
  process_cmd_argu();
  start_up_process();
  translate();
  clean_up_process();
  vcc_epilogue();

  return 0;
}

//Display process start-up message
//record data/time
void vcc_prologue() {
  printf("\nVenilla-C Compiler version 1.0\n");
  printf("- Implement by Wonder Chang.\n");
  printf("- Compiler course from NCKU EE.\n");
  printf("- Teacher: Jing Chen.\n");
  printf("\nStart to compile. The input file: %s\n", src_name);
}

//Process the command line arguments
//Check formats
void process_cmd_argu() {
  if(src_name != NULL) {
    src_f = fopen(src_name, "r");
    for(int i = 0; src_name[i] != '\0'; i++) {
      obj_name[i] = src_name[i];
      err_name[i] = src_name[i];
      lst_name[i] = src_name[i];
    }
    strcat(obj_name, ".asm");
    strcat(err_name, ".err");
    strcat(lst_name, ".lst");
    obj_f = fopen(obj_name, "w");
    err_f = fopen(err_name, "w");
    lst_f = fopen(lst_name, "w");
  }
  else {
    printf("Comman line error: Require the input file in the argument\n");
    exit(1);
  }
}

//Initialize global data 
//Create symbol table 
//Initialize symbol table (e.g. reserved words) 
//open required files
void start_up_process() {
}

//produce reference information
//release symbol table
//close files
//other
void clean_up_process() {
  fclose(src_f);
  fclose(obj_f);
  fclose(err_f);
}

//Display process terminating message
//record data/time
//dislay statistics
void vcc_epilogue() {
}

