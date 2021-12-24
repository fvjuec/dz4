#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

int main(void) {
    int i, j, str;
    str = i = j = 0;
    int a = 0;
    int b = 0;

    FILE * text = fopen("matrix.txt", "r"); // открываем файл

    if (!text) {  // проверяем открылся ли
        printf("the file cannot open\n");
        return 2; 
    }

    rewind(text); // Ставим указатель внутри файла на первое место
    char c;
    bool flag = true;
    for (c = getc(text); flag; c = getc(text)) {
        if(c == '\n' || c == EOF) {
            if(a == str && a != 0) {
                a = str;
                str = 0;
            }
            else if(a != str && a != 0) { // сравнение кол-ва символов в строке с кол-вом в предыдущей строке
                    printf("incorrect matrix\n");
                    return -1;
            }
            else if(a == 0) {
                a = str;
                str = 0;
            }
            if(c == EOF){
                flag = false;
            }
            b++;  // подсчет кол-ва строк
        } 
        else {
            str = str + 1; //подсчет символов в строке
        }
    }

    if(a != b) { //проверка явл ли матрица квадратом
        printf("matrix is not square");
        return -1;
    }

    char** arr = (char**)malloc(a * sizeof(char*));
    for (int i = 0; i < a; i++)
        arr[i] = (char*)malloc(a * sizeof(char*));
    rewind(text);

    //заполняем массив из файла
    char buffer;
    while (!feof(text)) {
        buffer = fgetc(text);
        arr[i][j] = buffer;
        j++;
        if (buffer == '\n') {
            i++;
            j = 0;
        }
    }
    fclose(text);

    //проверка на симметричность матрицы
	for (i = 0; i < a; i++)
		for (j = 0; j < a; j++)
            if(arr[i][j] != arr[j][i]){
                printf("wrong matrix\n");
                return -1;
            }    

    //подсчет петлей
    int f = 0;
    for (int i = 0; i < a; i++) {
            if(arr[i][i] == '1') {
                f = f + 1;
            }
    }
    printf ("\n%d loops\n", f);

    FILE *graph = fopen("graph.txt", "w");

    fprintf(graph, "graph G {\n");

    for (int i = 0; i < a; i++) {
        for (int j = 0; j <= i; j++) {
            if (arr[i][j] == '1') {
                fprintf(graph, "%d -- %d\n", (1 + i), (1 + j));
            }
        }
    }
    fprintf(graph, "}");

    fclose(graph);
    system("dot -Tpng graph.txt -og.png");

    for (int i = 0; i < a; i++)
        free(arr[i]);
 
    free(arr);

    return 0;
}  