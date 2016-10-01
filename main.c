//  Copyright 2016 Ryo Shinoki. Released under the MIT license.

#include "main.h"

const char *FORMULA      = "10+(1-20)+1";
const char *FILE_NAME    = "formula.txt";

int read_term();
int read_factor();
int read_num();

int main(int argc, const char * argv[]) {
  
  write_text(FORMULA, FILE_NAME);
  FILE *file = get_file_ptr(FILE_NAME);
  
  int ret = read_expression(file);
  printf("\n = %d \n",ret);
  return 0;
}

int read_expression(FILE *file) {
  int ret = read_term(file);
  
  for (;;) {
    int asciiChar = getc(file);
    if (!isspace(asciiChar)) {
      if (asciiChar == '+') {
        ret += read_term(file);
        printf(" +");
      }else if (asciiChar == '-') {
        ret -= read_term(file);
        printf(" -");
      } else {
        ungetc(asciiChar, file);                  // push back char to file
        break;
      }
    }
  }
  
  return ret;
}

int read_term(FILE *file) {
  int ret = read_factor(file);
  for (;;) {
    int asciiChar = getc(file);
    if (!isspace(asciiChar)) {
      if (asciiChar=='*') {
        ret *= read_factor(file);
        printf(" *");
      } else if (asciiChar=='/') {
        ret /= read_factor(file);
        printf(" /");
      } else {
        ungetc(asciiChar, file);                   /* push back char to file */
        break;
      }
    }
  }
  
  return ret;
}

int read_factor(FILE *file) {
  int ret = 0;
  
  // loop for skiping spaces
  for (;;) {
    int asciiChar = getc(file);
    
    if (!isspace(asciiChar)) {
      
      // return number if not '('
      if (isdigit(asciiChar)) {
        ungetc(asciiChar, file);                  // push back char to file
        return read_num(file);
        
      } else if (asciiChar == '(') {
        ret = read_expression(file);
        
        // loop for skiping space and ')' in factor
        for (;;) {
          int _asciiChar = getc(file);
          if (!isspace(_asciiChar)) {
            if (_asciiChar == ')') {
              return ret;                         // return if find ')'
            } else {
              fprintf(stderr,"Unexpectred charcter '%c' in read_factor \n", asciiChar);
              return 0;
            }
          }
        }                                         // End loop for skiping space and ')' in factor
      } else {
        fprintf(stderr, "Unexpectred charcter '%c' in read_factor \n", asciiChar);
        return 0;
      }
    }
  }                                               // End loop for skiping spaces
  return ret;
}

int read_num(FILE *file) {
  int ret = 0;
  for (;;) {
    int asciiChar = getc(file);
    if (!isspace(asciiChar)) {
      if (isdigit(asciiChar)) {
        int integerChar = 0;
        do {
          integerChar = integerChar * 10 + asciiChar - '0';
          asciiChar = getc(file);
        } while (isdigit(asciiChar));
        ret = integerChar;
        printf(" %d",ret);
        ungetc(asciiChar, file);                  // push back char to file
        break;
      } else {
        fprintf(stderr, "Unexpectred charcter '%c' in read_num \n", asciiChar);
        return 0;
      }
    }
  }
  return ret;
}