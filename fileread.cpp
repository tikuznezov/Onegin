// COMP
#include "onegin.h"


File ReadSringsFromFile(char *file_name)
{
    // create file struct
    File file = {};

    // read file to struct
    ReadFile(file_name, &file);

    // separate to single strings
    SepToStr(&file);

    return file;
}

// COMP Function to get file size
int FileSize(char *file_name, File *file)
{
    assert(file_name);
    assert(file);
    struct stat statistics = {};
    if (stat(file_name, &statistics) == 0) 
    {
        file->size = (size_t)statistics.st_size;
        printf("Размер файла: %ld байт\n", (long)statistics.st_size);
    } 
    else 
    {
        perror("Ошибка при вызове stat");
        exit(1);
    }
    return 0;
}

// COMP функ для чтения без разбиения на строчки возврат структуры с размером, указателем на буфер и массивом указателей на строки
// COMP Function to separate file to strings
int SepToStr(File *file)
{
    assert(file);
    // create strings addresses buffer
    file->str_pointers = (StrPointers *)calloc(file->str_count + 1, sizeof(StrPointers));
    assert(file->str_pointers);
    // printf("pointer a is initialized\n");

    // separate to strings
    size_t current_buffer_index = 0;
    size_t current_st_pointer_index = 0;
    size_t current_ed_pointer_index = 0;

    // first string is begin of file
    file->str_pointers[current_st_pointer_index].beg = file->begin;

    size_t str_num = 1;
    file->str_pointers[current_st_pointer_index++].str_num = str_num;
    // go to next index[]



    while ((current_buffer_index < file->size) && (current_st_pointer_index < file->str_count + 1))
    {
        if (file->begin[current_buffer_index] == '\n' || file->begin[current_buffer_index] == '\0')
        {
            file->str_pointers[current_ed_pointer_index++].end = &(file->begin)[current_buffer_index-1];
            str_num++;
            file->str_pointers[current_st_pointer_index].str_num = str_num;
            file->str_pointers[current_st_pointer_index++].beg = &(file->begin)[++current_buffer_index];
        }
        else
            current_buffer_index++;
    }

    file->str_pointers[current_ed_pointer_index].end = &((file->begin)[current_buffer_index]);

    return 0;
}

// COMP Function to read file to buffer
int ReadFile(char *file_name, File *file)
{
    assert(file_name);
    assert(file);
    // read file and get descriptor
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("File reading error"); // текстовое описание последней системной ошибки
        exit(1);
    }

    // get file size
    FileSize(file_name, file);
    // printf("buffer size = %zu\n", file.size);

    // create text buffer
    file->begin = (char *)calloc(file->size + 2, 1) + 1;
    assert(file->begin);
    file->begin[-1] = '\0';

    // read to text buffer
    ssize_t count_of_read_bytes = read(fd, (void *)file->begin, file->size);
    if (count_of_read_bytes == -1)
    {
        perror("Ошибка чтения данных файла\n");
        exit(1);
    }

    // get str_count
    size_t current_buf_index = 0;
    file->str_count = 0;
    while (current_buf_index < file->size)
    {
        if (((file->begin)[current_buf_index] == '\0') || ((file->begin)[current_buf_index] == '\n'))
        {
            file->str_count++;
        } 
        current_buf_index++;
    }

    close(fd);
    return 0;
}

// COMP освобождение памяти
int FreeFile(File *file)
{
    free(file->begin - 1);
    free(file->str_pointers);

    file->begin = NULL;
    file->str_pointers = NULL;
    return 0;
}