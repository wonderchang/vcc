#include "./include/main.h"
#include "./include/scan.h"
#include "./include/tran.h"
#include "./include/util.h"
#include "./include/act-rou.h"
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

  /* Data initialization */
  src_name = argv[1];
  // - Set the output file name
  for(int i = 0; src_name[i] != '\0'; i++) {
    obj_name[i] = src_name[i];
    err_name[i] = src_name[i];
    lst_name[i] = src_name[i];
  }

  /* Start to process */
  vcc_prologue();
  process_cmd_argu();
  start_up_process();
  translate();
  clean_up_process();
  vcc_epilogue();

  printf("\n");
  return 0;
}

//Display process start-up message
void vcc_prologue() {
  printf("\nVenilla-C Compiler version 1.0  Implemented by Wonder Chang.\n");
  printf("\nCompile the input file: %s\n", src_name);
}

//Process the command line arguments
void process_cmd_argu() {
  int filename_length = calculate_string_length(src_name);
  if(src_name != NULL) { 
    if(filename_length <= FILE_NAME_LEN - 4) {
      src_f = fopen(src_name, "r");
      strcat(obj_name, ".asm");
      strcat(err_name, ".err");
      strcat(lst_name, ".lst");
      obj_f = fopen(obj_name, "w");
      err_f = fopen(err_name, "w");
      lst_f = fopen(lst_name, "w");
    }
    else {
      printf("Error: The compile filename is too long. Only %d characters.\n\n", FILE_NAME_LEN);
      remove_output_file();
      exit(1);
    }
  }
  else {
    printf("Error: Require the input file in the argument command line\n\n");
    remove_output_file();
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

