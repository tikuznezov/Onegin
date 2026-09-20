#ifndef _onegin
#define _onegin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h>


const size_t POINTER_ARRAY_LENGTH = 400;

const size_t MAX_STR_LENGTH       = 100;


//! Задает красный цвет текста
#define PRED printf("\x1b[31m");
//! Задает синий цвет текста
#define PBLUE printf("\033[34m");
//! Задает фиолетовый цвет текста
#define PRINT_VIOLET printf("\033[35m");
//! Задает желтый цвет текста
#define PYELLOW printf("\x1b[33m");
//! Задает зеленый цвет текста
#define PGREEN printf("\x1b[32m");
//! Задает белый цвет текста на черном фоне (по умолчанию)
#define DEF_COL printf("\x1b[0m");
//! Задает черный текст на белом фоне
#define BLACKonWHITE printf("\x1b[30;47m");

// return count of read lines
size_t ReadFromFile(char ***array, char *file_name);

// display strings array
int PrintStrArray(char **array, size_t array_length,const char *comment);

// sorting from a->z
int CompareStrUp(const void *a, const void *b);

void PrintCharArray(char *array, size_t array_length);

void PrintStr(const char *a);

int CompareInt(const void *a, const void *b);

int CompareStrDown(const void *a, const void *b);

#endif