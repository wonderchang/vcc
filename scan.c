#include <stdio.h>

static int getNextChar(void);

#define MAX_LINE_BUFFER_LENGTH 256

FILE *fPtr;
int lineno

static char line_buffer[MAX_LINE_BUFFER_LENGTH];
static int line_position = 0;
static int current_line_buffer_string_size = 0;
static int EOF_flag = 0;

int main(void) {

  fPtr = fopen("test.c", "r");

  getNextChar();
  getNextChar();
  getNextChar();
  getNextChar();
  getNextChar();

  fclose(fPtr);
  return 0;
}

static int getNextChar(void) {
  fgets(line_buffer, MAX_LINE_BUFFER_LENGTH - 1, fPtr);
  printf("\nline = \"%s\"", line_buffer);
}


