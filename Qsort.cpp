#include "onegin.h"

void   Swap(void *a, void *b, size_t element_size)
{
    void *temp = calloc(1, element_size + 1);
    memcpy(temp, a, element_size);
    memcpy(a   , b, element_size);
    memcpy(b   , temp, element_size);
}

size_t Part (void *array, size_t array_length, size_t element_size, int (* Comp)(const void *a, const void *b))
{
    assert(array);
    if (array_length <= 1)
        return NULL;


    size_t base_index = (size_t)rand() % array_length;                                                           // crate random index in array
    void *base = memcpy(calloc(1, element_size), (const void*)((char *)array + element_size*base_index), element_size);  // initialization of base element

    size_t l = 0;
    size_t r = array_length-1;

    while ((l < r) && (l < array_length) && (l >= 0) &&  (r < array_length) && (r >= 0))
    {
        if (!Comp((const void*)((char *)array + l*element_size), (const void*)base))
        {
            l++;
        }
        else
        {
            while ((Comp((const void*)((char *)array + r*element_size), base)) && (r >= 0) && (r < array_length) && (l < r))
            {
                r--;
            }

            Swap((void *)((char *)array + r*element_size), (void *)((char *)array + l*element_size), element_size);
        }
    }

    if ((l == 0) && Comp((const void*)((char *)array + l*element_size), base))
    {
        for (size_t i = 1; i < array_length; i++)
            if (Comp((const void*)((char *)array + l*element_size), base))
                return l;
        return (size_t)-1;
    }

    free(base);
    return l;
}

void   Qsort(void *array, size_t array_length, size_t element_size, int (* Comp)(const void *a, const void *b))
{
    assert(array);

    if (array_length == 1)
        return;

    else if (array_length == 2)
    {
        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)))
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);
        return;
    }

    else if (array_length == 3)
    {
        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)))
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);

        if (Comp((const void*)((char *)array + 1*element_size), (const void*)((char *)array + 2*element_size)))
            Swap((void*)((char *)array + 1*element_size), (void*)((char *)array + 2*element_size), element_size);

        if (Comp((const void*)((char *)array + 0*element_size), (const void*)((char *)array + 1*element_size)))
            Swap((void*)((char *)array + 0*element_size), (void*)((char *)array + 1*element_size), element_size);
        return;
    }
    else if (array_length > 0)
    {
        size_t right_pointer = Part(array, array_length, element_size, Comp);

        if (right_pointer == (size_t)-1)
            return;

        else if (right_pointer > 0)
        {
            Qsort(array, right_pointer, element_size, Comp);
        }

        size_t Rlen = array_length - right_pointer;
        void  *Raddress = (void *)((char *)array + element_size * right_pointer);
        Qsort(array, Rlen, element_size, Comp);; // Сам опорный элемент гарантированно стоит на нужном месте, так что его пропускаем
    }
}