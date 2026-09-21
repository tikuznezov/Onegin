#include "onegin.h"
#include "Qsort.cpp"


int main() 
{
    char **onegin_text = NULL;
    char file_name[MAX_STR_LENGTH] = "test.txt";

    File onegin = ReadFromFile(&onegin_text, file_name);
    size_t count_of_lines = onegin.str_count;
    PGREEN printf("file reading completed\n"); DEF_COL
    PrintStrArray(onegin_text, count_of_lines, "original");
    PGREEN printf("count of lines = %zu;\n\n", count_of_lines); DEF_COL

    // сортировка с начала
    Qsort(onegin_text, count_of_lines, sizeof(onegin_text[0]), CompareStrUp);
    PrintStrArray(onegin_text, count_of_lines, "sorted UP");

    // сортировка с конца
    qsort(onegin_text, count_of_lines, sizeof(onegin_text[0]), CompareStrDown);
    PrintStrArray(onegin_text, count_of_lines, "sorted DOWN");

    // печать оригинала
    Qsort(onegin_text, count_of_lines, sizeof(onegin_text[0]), IntCompUp);
    PrintStrArray(onegin_text, count_of_lines, "oroginal");

    // Тут для проверки
        // Qsort(onegin_text, count_of_lines, sizeof(onegin_text[0]), RandComp);
        // PrintStrArray(onegin_text, count_of_lines, "Random");

        // Qsort(onegin_text, count_of_lines, sizeof(onegin_text[0]), CompareStrUp);
        // PrintStrArray(onegin_text, count_of_lines, "sorted UP");

    return 0;
}


void PrintCharArray(char *a, size_t array_length)
{
    for (size_t i = 0; i < array_length; i++)
        putc(a[i], stdout);
    printf("\n");
}

void PrintStr(const char *a)
{
    PYELLOW
    printf("\n--->");
    size_t i = 0;
    while ((a[i] != '\0') && (a[i] != '\n'))
        putc(a[i++], stdout);
    printf(":\n");
    DEF_COL
}

File ReadFromFile(char ***a, char *file_name)
{
    // create file struct
    File file = {};
    
    // read file to struct
    ReadFile(file_name, &file);

    // separate to single strings
    SepToStr(&file);

    // TODO README

    // PrintCharArray(buffer, buffer_size);

    // COMP функ для чтения без разбиения на строчки возврат структуры с размером, указателем на буфер и массивом указателей на строки

    // PrintStrArray(pointer_array, 4);
    *a = file.str_pointers;
    return file;
}

int PrintStrArray(char **a, size_t array_length,const char *comment)
{
    PrintStr(comment);
    PYELLOW printf("----------------------------------------------------------------\n"); DEF_COL
    for (size_t i = 0; i < array_length; i++)
    {
        putc('*', stdout);
        putc('\t', stdout);
        putc('"', stdout);

        size_t str_index = 0;
        while ((a[i][str_index] != '\0') && (a[i][str_index] != '\n'))
        {
            putc(a[i][str_index], stdout);
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
    assert(a);
    assert(b);

    const char *pstr1 = *(const char * const*)a;
    const char *pstr2 = *(const char * const*)b;
    unsigned int count_of_cmp = 0;

    while ((count_of_cmp < MAX_STR_LENGTH) && (*pstr1 != '\n') && (*pstr1 != '\0'))
    {
        while (!isalpha(*pstr1) && (*pstr1 != '\n') && (*pstr1 != '\0'))
            pstr1++;
        while (!isalpha(*pstr2) && (*pstr2 != '\n') && (*pstr2 != '\0'))
            pstr2++;

        if (tolower(*pstr1) == tolower(*pstr2))
        {
            pstr1++;
            pstr2++;
            count_of_cmp++;
        }
        else break;
    }
    return tolower(*pstr1) - tolower(*pstr2);
}

int CompareInt(const void *a, const void *b)
{
    const char *pstr1 = *(const char * const*)a;
    const char *pstr2 = *(const char * const*)b;
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

int CompareStrDown(const void *a, const void *b)
{
    // static int step = 0;
    // step++;
    // printf("Start comp -> ");
    assert(a);
    assert(b);

    const char *pstr1 = *(const char * const*)a;
    const char *pstr2 = *(const char * const*)b;
    size_t len1 = 0;
    size_t len2 = 0;

    if (*pstr1 == '\n' && *pstr2 == '\n')
    {
        // printf("end comp %6d\n", step);
        return 0;
    }
    else if (*pstr1 == '\n')
    {
        // printf("end comp %6d\n", step);
        return -1;
    }
    else if (*pstr2 == '\n')
    {
        // printf("end comp %6d\n", step);
        return 1;
    }

    while ((*pstr1 != '\n') && (*pstr1 != '\0'))
    {
        pstr1++;
        len1++;
    }
    while ((*pstr2 != '\n') && (*pstr2 != '\0'))
    {
        pstr2++;
        len2++;
    }

    if (len1 > 0 && len2 > 0)
    {
        pstr1--;
        pstr2--;
        len1--;
        len2--;
    }


    while ((len1 > 0) && (len2 > 0) && (*pstr1 != '\n') && (*pstr1 != '\0')&& (*pstr2 != '\n') && (*pstr2 != '\0'))
    {
        // if (len1 <= 0) printf("main -> pstr1 < 0\n");
        // if (len2 <= 0) printf("main -> pstr2 < 0\n");

        while (!isalpha(*pstr1) && (*pstr1 != '\n') && (*pstr1 != '\0') && (len1 > 0))
        {
            // if (len1 <= 0) printf("while1 -> pstr1 < 0\n");
            // if (len2 <= 0) printf("while1 -> pstr2 < 0\n");
            pstr1--;
            len1--;
        }

        while (!isalpha(*pstr2) && (*pstr2 != '\n') && (*pstr2 != '\0') && (len2 > 0))
        {
            // if (len1 <= 0) printf("while2 -> pstr1 < 0\n");
            // if (len2 <= 0) printf("while2 -> pstr2 < 0\n");
            pstr2--;
            len2--;
        }

        if ((tolower(*pstr1) == tolower(*pstr2)) && (len1 > 0) && (len2 > 0))
        {
            // if (len1 <= 0){printf("equal -> pstr1 < 0\n"); PrintStr(pstr1);}
            // if (len2 <= 0){printf("equal -> pstr2 < 0\n"); PrintStr(pstr2);}
            pstr1--;
            pstr2--;
            len1--;
            len2--;
        }
        else break;
    }
    // printf("end comp %6d\n", step);
    return tolower(*pstr1) - tolower(*pstr2);
}

int RandComp(const void *, const void *)
{
    srand((unsigned) time(NULL));
    return ((int)(rand()) % 10) - 5;
}

int IntCompUp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

// COMP Function to get file size
int FileSize(char *file_name, struct stat *statistics)
{
    if (stat(file_name, statistics) == 0) 
    {
        printf("Размер файла: %ld байт\n", (long)statistics->st_size);
    } 
    else 
    {
        perror("Ошибка при вызове stat");
        return 1;
    }
    return 0;
}

// COMP Function to separate file to strings
File *SepToStr(File *file)
{
    // create strings addresses buffer
    file->str_pointers = (char **)calloc(POINTER_ARRAY_LENGTH, sizeof(char *));
    // printf("pointer a is initialized\n");

    // separate to strings
    size_t current_buffer_index = 0;
    size_t current_pointer_index = 0;
    file->str_count = 0;

    // first string is begin of file
    file->str_pointers[current_pointer_index++] = file->begin;
    // go to next index
    file->str_count++;

    while ((current_buffer_index < file->size) && (current_pointer_index < POINTER_ARRAY_LENGTH))
    {
        if (file->begin[current_buffer_index] == '\n')
        {
            file->str_count++;
            file->str_pointers[current_pointer_index++] = &(file->begin)[++current_buffer_index];
        }
        else
            current_buffer_index++;
    }

    return file;
}

// COMP Function to read file to buffer
int ReadFile(char *file_name, File *file)
{
    // read file and get descriptor
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Ошибка чтения файла"); // текстовое описание последней системной ошибки
        return 1;
    }

    // get file size
    struct stat statistics = {};
    FileSize(file_name, &statistics);
    file->size = (size_t)statistics.st_size;
    // printf("buffer size = %zu\n", file.size);


    // create text buffer
    file->begin = (char *)calloc(file->size + 1, 1);

    // read to text buffer
    long count_of_read_bytes = read(fd, (void *)file->begin, file->size);
    if (count_of_read_bytes == -1)
        perror("Ошибка чтения файла\n");

    close(fd);
    return 0;
}