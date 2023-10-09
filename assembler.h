#ifndef ASM
#define ASM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comand_code.h"

//typedef float char_t;

#ifndef DEBUG
#define $ printf ( "%d\n", __LINE__ );
#else
#define $
#endif

struct Line_t {
    char *start  = nullptr;
    char* element = 0;
    int line_size = 0;
};

struct Text_t {
    int file_size = 0;
    Line_t * line_array;
    int n_lines = 0;
};

FILE* Assembler ( int *n_comands, char** output_buffer );
int Compare ( FILE *code, Comand_Code cc, Text_t *Text, char *output_buffer, int output_buffer_size );
int GetFileSize ( FILE * f );
int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f );
int Split ( Text_t *Text, FILE *code_f, Comand_Code CC, char *input_buffer, char *output_buffer );

#endif // ASM
