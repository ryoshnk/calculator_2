//  Copyright 2016 Ryo Shinoki. Released under the MIT license.

#ifndef calculator_main_h
#define calculator_main_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int write_text(const char *formula, const char *name);
FILE* get_file_ptr(const char *fileName);
int read_expression(FILE *file);

#endif
