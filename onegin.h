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


const size_t POINTER_ARRAY_LENGTH = 8000;

const size_t MAX_STR_LENGTH       = 100;

struct StrPointers
{
    char *beg;
    char *end;
    size_t str_num;
};

// COMP
struct File 
{
    size_t str_count;
    size_t size;
    char *begin;
    StrPointers *str_pointers;
};



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



// display strings array
int PrintStrPointers(StrPointers *array, size_t array_length,const char *comment);

int PrintStrArray(char **a, size_t array_length,const char *comment);

void PrintCharArray(char *array, size_t array_length);

int PrintStrPointersToFile(StrPointers *text, size_t count_of_strings, FILE *file, const char *description);

int PrintStrArrayToFile(char *text, size_t count_of_strings, FILE *file, const char *description);

int PrintStrArray(char **a, size_t array_length,const char *comment);

void PrintStr(const char *a);

// sort from a->z
int  CompareStrUp(const void *a, const void *b);

// reverse sort from a->z
int  CompareStrDown(const void *a, const void *b);

// random sort
int  RandComp(const void *a, const void *b);

// sort from -inf to +inf
int  IntCompUp(const void *a, const void *b);


// COMP
/// @brief Read file to buffer and get file info (struct File)
/// @param file_name name of file
/// @return buffer with file data, array with begin of file strings, other file info
File ReadFromFile(char *file_name);

/// @brief Get file size by system call
/// @param file_name name of file
/// @param statistics struct with file info
/// @return enum TYPE_OF_ERROR (dev)
int FileSize(char *file_name, struct stat *statistics);

/// @brief Read file and record strings addresses to array
/// @param file struct with file data
/// @return enum TYPE_OF_ERROR (dev)
int SepToStr(File *file);


/// @brief Function to read file to buffer
/// @param file_name - name of read file
/// @param file - struct to record read file 
/// @return
int ReadFile(char *file_name, File *file);

int FreeFile(File *file);

#endif