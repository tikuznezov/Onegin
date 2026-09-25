#include "onegin.h"
#include "fileread.cpp"
#include "Qsort.cpp"

int main(int argc, char *argv[]) 
{
    char  input_file_name[MAX_STR_LENGTH] = "";
    char output_file_name[MAX_STR_LENGTH] = "";

    // COMP
    if (argc >= 2)
    {
        strncpy(input_file_name, argv[1], MAX_STR_LENGTH-1);
    }
    else
    {
        printf("Input file name: ");
        if (scanf("%s", input_file_name) != 1)
            return 1;
    }
    if (argc >= 3)
    {
        strncpy(output_file_name, argv[2], MAX_STR_LENGTH-1);
    }
    else
    {
        printf("Input output file name: ");
        if (scanf("%s", output_file_name) != 1)
            return 1;
    }

    File onegin = ReadSringsFromFile(input_file_name);
    FILE *output = fopen(output_file_name, "w");
    if (output == NULL)
    {
        perror("Не удалось создать файл для вывода");
        return 1;
    }


    // read data
    // PGREEN printf("file reading completed\n"); DEF_COL
    // PrintStrArray(onegin.str_pointers.end, onegin.str_count, "original");
    // PGREEN printf("count of lines = %zu;\n\n", onegin.str_count); DEF_COL

    // sort by alphabet
    Qsort(onegin.str_pointers, onegin.str_count, sizeof(StrPointers), CompareStrUp);
    PrintStrPointersToFile(onegin.str_pointers, onegin.str_count, output, "alphabet sort (a-z) (UP)");
    // PrintStrPointers(onegin.str_pointers, onegin.str_count, "UP");


    // reverse sort by alphabet
    Qsort(onegin.str_pointers, onegin.str_count, sizeof(StrPointers), CompareStrDown);
    PrintStrPointersToFile(onegin.str_pointers, onegin.str_count, output, "reverse alphabet sort (a-z) (DOWN)");
    // PrintStrPointers(onegin.str_pointers, onegin.str_count, "DOWN");

    // original
    PrintStrArrayToFile(onegin.begin, onegin.size, output, "Original text");

    fclose(output);
    FreeFile(&onegin);
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
    printf("<---\n");
    DEF_COL
}

int PrintStrPointers(StrPointers *text, size_t array_length,const char *comment)
{
    assert(text);
    assert(comment);

    PrintStr(comment);
    PYELLOW printf("----------------------------------------------------------------\n"); DEF_COL
    for (size_t i = 0; i < array_length; i++)
    {
        putc('*', stdout);
        putc('\t', stdout);
        putc('"', stdout);

        size_t str_index = 0;
        while ((text[i].beg[str_index] != '\0') && (text[i].beg[str_index] != '\n'))
        {
            putc(text[i].beg[str_index], stdout);
            str_index++;
        }

        putc('"', stdout);
        putc('\n', stdout);
    }
    PYELLOW printf("----------------------------------------------------------------\n"); DEF_COL

    return 0;
}

int PrintStrPointersToFile(StrPointers *text, size_t count_of_strings, FILE *file, const char *description)
{
    assert(text);

    fputs((const char *) description, file);
    fprintf(file, "\n___________________________________________________________________\n");
    fprintf(file, "\n\n");

    for (size_t str_n = 0; str_n < count_of_strings; str_n++)
    {
        fprintf(file, "%5zu -> %5zu:    \"", text[str_n].str_num, str_n+1);
        size_t i = 0;
        while ((text[str_n].beg[i] != '\0') && (text[str_n].beg[i] != '\n'))
            fputc(text[str_n].beg[i++], file);
            fputc('\"', file);
            fputc('\n', file);
    }

    fprintf(file, "-------------------------------------------------------------------\n\n\n\n");

    return 0;
}

int CompareStrUp(const void *a, const void *b)
{
    assert(a);
    assert(b);

    // printf("Comp start\n");
    const char *pstr1 = ((const StrPointers *)a)->beg;
    const char *pstr2 = ((const StrPointers *)b)->beg;
    // printf("Get elements\n a = %p \n b = %p\n", pstr1, pstr2);
    // printf("Get elements\n a[0] = %c \n b[0] = %c\n", *pstr1, *pstr2);
    // PrintStr(pstr1);
    // PrintStr(pstr2);

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

int CompareStrDown(const void *a, const void *b)
{
    // printf("Сортировка вниз\n");
    assert(a);
    assert(b);

    const char *pstr1 = ((const StrPointers *)a)->end;
    const char *pstr2 = ((const StrPointers *)b)->end;

    if ((*pstr1 == '\0') || (*pstr1 == '\n') || (*pstr2 == '\0') || (*pstr2 == '\n'))
        return tolower(*pstr1) - tolower(*pstr2);

    // printf("Start main while \n");
    // PrintStr(pstr1);
    // PrintStr(pstr2);
    // printf("Start main while \n");
    while ((*pstr1 != '\0') && (*pstr1 != '\n') && (*pstr2 != '\0') && (*pstr2 != '\n'))
    {
        while (!isalpha(*pstr1) && (*pstr1 != '\n') && (*pstr1 != '\0'))
        {
            // printf("Start pstr1 while \n");
            pstr1--;
        }
        while (!isalpha(*pstr2) && (*pstr2 != '\n') && (*pstr2 != '\0'))
        {
            // printf("Start pstr2 while \n");
            pstr2--;
        }

        // printf("Start IFs \n");
        // printf("char1 = '%c', char2 = '%c'\n", *pstr1, *pstr2);
        if (tolower(*pstr1) != tolower(*pstr2))
        {
            break;
        }
        else if ((*pstr1 != '\0') && (*pstr1 != '\n') && (*pstr2 != '\0') && (*pstr2 != '\n'))
        {
            pstr1--;
            pstr2--;
        }
        else 
            break;
    }

    // printf("End of sort down\n");
    return tolower(*pstr1) - tolower(*pstr2);
}

int RandComp(const void *, const void *)
{
    srand((unsigned) time(NULL));
    return ((int)(rand()) % 10) - 5;
}

int IntCompUp(const void *a, const void *b)
{
    assert(a);
    assert(b);
    return *(const int *)a - *(const int *)b;
}

int PrintStrArray(char **a, size_t array_length,const char *comment)
{
    assert(a);
    assert(comment);

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

int PrintStrArrayToFile(char *text, size_t array_length, FILE *file, const char *description)
{
    assert(text);

    fprintf(file, "___________________________________________________________________\n");
    fputs((const char *) description, file);
    fprintf(file, "\n\n");

    size_t index = 0;
    size_t str_num = 0;

    while (index < array_length)
    {
        fprintf(file, "%5zu:\t\"", ++str_num);
        while ((text[index] != '\n') && (text[index] != '\0'))
        {
            fputc(text[index++], file);
        }
        fputc('"', file);
        fputc('\n', file);
        index++;
    }

    fprintf(file, "-------------------------------------------------------------------\n\n\n\n");

    return 0;
}
