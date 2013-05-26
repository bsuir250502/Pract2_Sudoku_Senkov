#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 9
#define INPUT "condition.txt"
#define OUTPUT "solution.txt"

void file_output(char *file_name);
void sudoku_filling(FILE * file, char *file_name);
int solve_of_sudoku(FILE *file, int height, int length);
void sudoku_output();
int check_elem_of_sudoku();
int check_line();
int check_colum();
int check_3_3();
void copy_sudoku_to_file(FILE *file, char *file_name);

int sudoku[MAX_ELEM][MAX_ELEM];

int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        return 0;
    }
    FILE *file;
    file = NULL;
    int fail = 0;
    sudoku_filling(file, INPUT);
    puts("\n  -------- Condition: -------\n");
    sudoku_output();
    fail = solve_of_sudoku(file, 0, 0);
    if (fail) {
        puts("   ----- Wrong information in file ! ------");
    }
    else {
        copy_sudoku_to_file(file, OUTPUT);
        puts("  -------- Solution: --------\n");
        sudoku_output();
    }
    return 0;
}

void sudoku_filling(FILE * file, char *file_name)
{
    int i, j;
    file = fopen(file_name, "r");
    for (i = 0; i < MAX_ELEM; i++) {
        for (j = 0; j < MAX_ELEM; j++) {
            fscanf(file, "%d", &sudoku[i][j]);
        }
    }
    fclose(file);
}

void sudoku_output()
{
    int i, j;
    for (i = 0; i < MAX_ELEM; i++) {
        for (j = 0; j < MAX_ELEM; j++) {
            if (j == 2 || j == 5 || j == 8) {
                printf("%3d ", sudoku[i][j]);
            }
            else {
                printf("%3d", sudoku[i][j]);
            }
        }
        puts("");
        if (i == 2 || i == 5 || i == 8) {
            puts("");
        }
    }
}

int solve_of_sudoku(FILE *file, int height, int length)
{
    int  element = 1;

    while (1) {
         if ((length + 1) >= MAX_ELEM && height >= MAX_ELEM) {
            return 0;
        }
        if (length >= MAX_ELEM) {
            length = 0;
            height++;
        }
        if(sudoku[height][length] != 0) {
            length++;
        }
        else {
            break;
        }
    }

    do {
        while (1) {
            if(element <= MAX_ELEM) {
                sudoku[height][length] = element;
                element ++;
                if (!check_elem_of_sudoku()) {
                    break;
                }
            }
            if (element >= MAX_ELEM + 1) {
                sudoku[height][length] = 0;
                return 1;
            }
        }
        if (!solve_of_sudoku(file, height, (length + 1 ))) {
            return 0;
        }
    } while(1);
}

int check_elem_of_sudoku()
{
    if(!check_line()) {
        if(!check_colum()) {
            if(!check_3_3()) {
                return 0;
            }
            else {
                return 1;
            }        
        }
        return 1;
    }
    return 1;    
}

int  check_line()
{
    int numbers, i, j, repeates = 0;
    for(numbers = 1; numbers <= 9 ; numbers++) {
        for(i = 0; i < MAX_ELEM; i++) {
            for(j = 0; j < MAX_ELEM; j++) {
                if(sudoku[i][j] == numbers) {
                    repeates++;
                }
            }
            if(repeates > 1) {
                return 1;
            }
            repeates = 0;
        }
    }
    return 0;
}

int check_colum()
{
    int numbers, i, j, repeates = 0;
    for(numbers = 1; numbers <= 9; numbers++) {
        for(j = 0; j < MAX_ELEM; j++) {
            for(i = 0; i < MAX_ELEM; i++) {
                if(sudoku[i][j] == numbers) {
                    repeates++;
                }
            }
            if(repeates > 1){
                return 1;
            }
            repeates = 0;
        }
    }
    return 0;
}

int check_3_3()
{
    int numbers, i, j, i1, j1, repeates = 0;
    for(numbers = 1; numbers <= 9; numbers++) {
        for(i = 0; i < MAX_ELEM; i += 3) {
            for(j = 0; j < MAX_ELEM; j += 3) {
                for(i1 = i; i1 < i+3 ; ++i1) {
                    for(j1 = j; j1 < j+3 ; ++j1) {
                        if(sudoku[i1][j1] == numbers) {
                            repeates ++;
                        }
                    }
                }
                if(repeates > 1) {
                    return 1;
                }
                repeates = 0;                   
            }          
        }
    }
    return 0;
}

void copy_sudoku_to_file(FILE * file, char *file_name)
{
    int i, j;
    file = fopen(file_name, "w+");
    for (i = 0; i < MAX_ELEM; i++) {
        for (j = 0; j < MAX_ELEM; j++) {
            fprintf(file, "%d ", sudoku[i][j]);
        }
        fprintf(file, "\n");
    }           
    fclose(file);
}