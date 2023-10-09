#include "assembler.h"
#include "stack.h"

int main ()
{
$   char *output_buffer;
$   int n_comands = 0;

$   Assembler ( &n_comands, &output_buffer );


    return 0;
}
FILE* Assembler ( int *n_comands, char** output_buffer )
{
    FILE *comand_f = fopen ( "start.txt", "r" );
    FILE *code_f   = fopen ( "code.txt", "w" );

    Comand_Code CC = {};
    Text_t Text    = {};

    Text.file_size = GetFileSize ( comand_f );

    char *input_buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    fread ( input_buffer, sizeof( input_buffer[0] ), Text.file_size, comand_f );    //return value
    input_buffer[Text.file_size] = '\n';

    *output_buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
$   Split ( &Text, code_f, CC, input_buffer, *output_buffer );

    *n_comands = Text.n_lines;

    for ( int i = 0; i < Text.file_size; ++i ) {
$       printf ( "%c", *output_buffer + i );
    }

$   AsmDtor ( input_buffer, Text.line_array, code_f );

    return code_f;
}

int GetFileSize ( FILE * f )
{
    int prev = ftell ( f );

    fseek ( f, 0, SEEK_END );
    size_t sizet = ftell ( f );
    fseek ( f, prev, SEEK_SET );

    return sizet;
}

int Compare ( FILE *code, Comand_Code cc, Text_t *Text, char *output_buffer, int output_buffer_size, int n_comand )
{
$   for ( int i = 0; i < cc.n_comands; ++i ) {
$       if ( strcmp ( Text->line_array[n_comand].start, cc.arr[i].str ) == 0 ) {
$           //fprintf ( code, "%d ", cc.arr[i].code );
            //fprintf ( code, "%g\n", ptr_elements );
            printf ( "%d\n", output_buffer_size );
$           strcpy ( output_buffer + output_buffer_size , Text->line_array[n_comand].start );

$           output_buffer_size += Text->line_array[n_comand].line_size;
            printf ( "%d\n", output_buffer_size );

$           strcat ( output_buffer + output_buffer_size++, Text->line_array[n_comand].element );

            *( output_buffer + output_buffer_size++) = '\n';
$
$           break;
        }
    }

$   return output_buffer_size; // error code
}

int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f )
{
    free(buffer);
    free(line_array);

    fclose ( comand_f ); //error
}

int Split ( Text_t *Text, FILE *code_f, Comand_Code CC, char *input_buffer, char *output_buffer )
{
    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( input_buffer + i ) == ';' ) {
            ++(Text->n_lines);
            *( input_buffer + i ) = '\0';
        }
    }

    Text->line_array = ( Line_t *)calloc ( Text->n_lines, sizeof ( Line_t) );

    int output_buffer_size = 0;

    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( input_buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( input_buffer[j] == ' ' ) {
                input_buffer[j] = '\0';
                flag = true;
                Text->line_array[i].start = input_buffer + j - len;
                Text->line_array[i].line_size = len + 1;
                //Text->line_array[i].element = ( char_t )atof ( input_buffer + j + 1 );
                Text->line_array[i].element = input_buffer + j + 1;
            }
            else if ( input_buffer[j] != ' ' && flag == false ) {
                ++len;
            }
            ++j;
        }
        //buffer[j] = '\0';
        if ( flag == false ) {
            Text->line_array[i].start = input_buffer + j - len;
        }
        while ( input_buffer[j] != '\n' ) {
            ++j;
        }
        output_buffer_size = Compare ( code_f, CC, Text, output_buffer, output_buffer_size, i );
    }

    return 0;
}
