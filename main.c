#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 9

void file_output(char *file_name);
void input_sudoku(FILE *file, char *file_name);
int solve_of_sudoku(FILE *file, int i, int j);
int cheking_element();
void output_sudoku(FILE * file, char *file_name);

int sudoku[MAX_ELEM][MAX_ELEM];

int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        return 0;
    }
    FILE *file;
    file = NULL;
    input_sudoku(file, "condition.txt");
    if (!(solve_of_sudoku(file, 0, 0))) {
        puts("----- Wrong information in file ! ------");
    }
    else {
        output_sudoku(file, "solution.txt");
    }
    return 0;
}

void input_sudoku(FILE * file, char *file_name)
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

int solve_of_sudoku(FILE *file, int i, int j)
{
    int elem = 1;
    while (1) {
        if (sudoku[i][j] != 0) {
            if ((i + 1) >= MAX_ELEM && (j + 1) >= MAX_ELEM) {
                return 1;
            }
            if ((j + 1) >= MAX_ELEM) {
                i++;
                j = 0;
            }
            else {
                j++;
            }
        }
        else {
            break;
        }
    }
    while (1) {
        while (1) {
            sudoku[i][j] = elem;
            elem++;
            if (cheking_element() == 0) {
                break;
            }
            if (elem >= 10) {
                sudoku[i][j] = 0;
                return 1;
            }
        }
        if (solve_of_sudoku(file, i, (j + 1)) == 0) {
            return 1;
        }
    }
}

int cheking_element()
{
    int wrong = 0;
    int i, j, i1, j1;
    int mas[9] = { 0, };
    for (i = 0; i < 9 && !wrong; ++i) {
        for (j = 0; j < 9 && !wrong; ++j) {
            if (sudoku[i][j] == 0) {
                continue;
            }
            if (mas[sudoku[i][j] - 1] == 0) {
                mas[sudoku[i][j] - 1] = 1;
            }
            else {
                wrong = 1;
            }
        }
        for (j = 0; j < 9 && !wrong; ++j) {
            for (i = 0; i < 9 && !wrong; ++i) {
                if (sudoku[i][j] == 0) {
                    continue;
                }
                if (mas[sudoku[i][j] - 1] == 0) {
                    mas[sudoku[i][j] - 1] = 1;
                }
                else {
                    wrong = 1;
                }
            }
            for (i = 0; i < 9 && !wrong; i += 3) {
                for (j = 0; j < 9 && !wrong; j += 3) {
                    for (i1 = i; i1 < i + 3 && !wrong; ++i1) {
                        for (j1 = j; j1 < j + 3 && !wrong; ++j1) {
                            if (sudoku[i1][j1] == 0) {
                                continue;
                            }
                            if (mas[sudoku[i1][j1] - 1] == 0) {
                                mas[sudoku[i1][j1] - 1] = 1;
                            }
                            else {
                                wrong = 1;
                            }
                        }
                    }
                }
            }
            if (!wrong) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    return 1;
}

void output_sudoku(FILE * file, char *file_name)
{
    int i, j;
    file = fopen(file_name, "w+");
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
    for (i = 0; i < MAX_ELEM; i++) {
        for (j = 0; j < MAX_ELEM; j++) {
            fprintf(file, "%d ", sudoku[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
