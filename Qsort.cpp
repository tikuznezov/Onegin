#include "onegin.h"

void   Swap(void *a, void *b, size_t element_size)
{
    // printf("Start SWAP\n");
    void *temp = calloc(1, element_size + 1);
    memcpy(temp, a, element_size);
    memcpy(a   , b, element_size);
    memcpy(b   , temp, element_size);
    free(temp);
    // printf("End SWAP\n");
}

size_t Part (void *array, size_t array_length, size_t element_size, int (* Comp)(const void *a, const void *b))
{
    if (array_length <= 1)
        return 0;
    assert(array);

    size_t base_index = (size_t)rand() % array_length;                                                                   // crate random index in array
    void *base = memcpy(calloc(1, element_size), (const void*)((char *)array + element_size*base_index), element_size);  // initialization of base element

    size_t l = 0;
    size_t r = array_length-1;
    // printf("Start PART: len = %zu;   l = %zu, r = %zu\n",array_length, l, r);

    while (l <= r)
    {
        while ((Comp((const void*)((char *)array + l*element_size), (const void*)base) < 0) && (l < array_length))
            l++;
        while ((Comp((const void*)((char *)array + r*element_size), (const void*)base) > 0) && (r > 0))
            r--;
        if (l >= array_length || r == 0) break;
        if (l <= r)
        {
            Swap((void *)((char *)array + r*element_size), (void *)((char *)array + l*element_size), element_size);
            l++;
            r--;
        }
    }
    // printf("End PART\n");
    if (l >= array_length)
        l = array_length-1;
    free(base);
    return l;
}


void   Qsort(void *array, size_t array_length, size_t element_size, int (* Comp)(const void *a, const void *b))
{
    assert(array);

    if (array_length <= 1)
        return;

    else if (array_length == 2)
    {
        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)) > 0)
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);
        return;
    }

    else if (array_length == 3)
    {
        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)) > 0)
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);

        if (Comp((const void*)((char *)array + 1*element_size), (const void*)((char *)array + 2*element_size)) > 0)
            Swap((void*)((char *)array + 1*element_size), (void*)((char *)array + 2*element_size), element_size);

        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)) > 0)
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);
        return;
    }
    else
    {
        // printf("Start SORT\n");
        size_t Rstart = Part(array, array_length, element_size, Comp);

        Qsort((char *)array + Rstart*element_size, array_length - Rstart, element_size, Comp);
        Qsort(array                              ,                Rstart, element_size, Comp);
        // printf("End Sort\n");
    }
}