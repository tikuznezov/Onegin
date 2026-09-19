#include "onegin.h"

#include "Qsort.cpp"



// TODO comparator
// TODO qsort to strings
// TODO read srt from file to dynamic memory
// TODO display sorting and sorted strings


int main() 
{
    char **a = NULL;
    char file_name[100] = "ggd.txt";
    size_t count_of_lines = ReadFromFile(&a, file_name);
    PGREEN printf("file reading completed\n"); DEF_COL
    PrintStrArray(a, count_of_lines, "original");
    PGREEN printf("count of lines = %zu;\n", count_of_lines); DEF_COL

    Qsort(a, count_of_lines, sizeof(a[0]), CompareStrUp);
    PrintStrArray(a, count_of_lines, "sorted");
    return 0;
}


void PrintCharArray(char *array, size_t array_length)
{
    for (int i = 0; i < array_length; i++)
        putc(array[i], stdout);
    printf("\n");
}

void PrintStr(const char *a)
{
    PYELLOW
    printf("\n--->  ");
    size_t i = 0;
    while (a[i] != '\0')
        putc(a[i++], stdout);
    printf(":\n");
    DEF_COL
}

size_t ReadFromFile(char ***array, char *file_name)
{
    int file = open(file_name, O_RDONLY);
    if (file == -1)
    {
        perror("Ошибка чтения файла"); // текстовое описание последней системной ошибки
        return 1;
    }

    struct stat statistics = {};
    if (stat(file_name, &statistics) == 0) {
        printf("Размер файла: %ld байт\n", (long)statistics.st_size);
    } else {
        perror("Ошибка при вызове stat");
        return 1;
    }

    char **pointer_array = (char **)calloc(POINTER_ARRAY_LENGTH, sizeof(char *));

    printf("pointer array is initialized\n");

    size_t count_of_read_lines = 0;

    size_t buffer_size = (size_t)statistics.st_size;
    printf("buffer size = %zu\n", buffer_size);

    char *buffer = (char *)calloc(buffer_size + 1, 1);

    int count_of_read_bytes = read(file, (void *)buffer, buffer_size);
    // PrintCharArray(buffer, buffer_size);

    size_t current_buffer_index = 0;
    size_t current_pointer_index = 0;

    pointer_array[current_pointer_index++] = buffer;
    count_of_read_lines++;

    while ((current_buffer_index < buffer_size) && (current_pointer_index < POINTER_ARRAY_LENGTH))
    {
        if (buffer[current_buffer_index] == '\n')
        {
            count_of_read_lines++;
            pointer_array[current_pointer_index++] = &buffer[++current_buffer_index];
        }
        else
            current_buffer_index++;
    }


    // PrintStrArray(pointer_array, 4);
    *array = pointer_array;
    return count_of_read_lines;
}

int PrintStrArray(char **array, size_t array_length,const char *comment)
{
    PrintStr(comment);
    PYELLOW printf("----------------------------------------------------------------\n"); DEF_COL
    for (size_t i = 0; i < array_length; i++)
    {
        putc('*', stdout);
        putc('\t', stdout);
        putc('"', stdout);

        size_t str_index = 0;
        while ((array[i][str_index] != '\0') && (array[i][str_index] != '\n'))
        {
            putc(array[i][str_index], stdout);
            str_index++;
        }

        putc('"', stdout);
        putc('\n', stdout);
    }
    PYELLOW printf("----------------------------------------------------------------\n"); DEF_COL

    return 0;
}

int CompareStrUp(const void *a, const void *b)
{
    // printf("called COMP\n");
    // PrintStrArray((char **) a, 1);
    // PrintStrArray((char **) b, 1);
    int res = strcmp(*(const char **)a, *(const char **)b);
    // printf("res = %d\n", res);
    // printf(")\n");
    // getchar();
    return res;
}

int CompareInt(const void *a, const void *b)
{
    char *pstr1 = *(char **)a;
    char *pstr2 = *(char **)b;
    printf("a = %c, b = %c\n", *pstr1, *pstr2);

    while ((*pstr1 == *pstr2) && (*pstr1 != '\n'))
    {
        pstr1++;
        pstr2++;
    }

    if ((*pstr1 == '\0') || (*pstr1 != '\n'))
        return 0;
    else
    {
        int res = *pstr1 - *(pstr2-1);
        if (res > 0) return 1;
        else return 0;
    }
}

// int CompareStrDown(const void *a, const void *b)
// {
//     assert(a);
//     assert(b);
//     char *str1 = (char *)a;
//     char *str2 = (char *)b;
//     char *pstr1 = str1;
//     char *pstr2 = str2;
//
//     while ((*pstr1 != '\0') && (*pstr1 != '\n') && (*pstr1 != EOF))
//         pstr1++;
//     while ((*pstr2 != '\0') && (*pstr2 != '\n') && (*pstr2 != EOF))
//         pstr2++;
//
//     unsigned int count_of_cmp = 0;
//
//     while ((*pstr1 == *pstr2) && (count_of_cmp<MAX_STR_LENGTH))
//     {
//         pstr1--;
//         pstr2--;
//         count_of_cmp++;
//         if ((*pstr1 == '\0') || (*pstr2 == '\0' ))
//             break;
//     }
//
//     if ((*pstr1 == '\0') && (*pstr2 == '\0'))
//         return 0;
//     else
//         return *pstr1 - *(pstr2-1);
// }
