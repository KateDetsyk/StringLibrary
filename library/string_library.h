#include <fcntl.h>

#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

typedef struct {size_t capacity_m;
                size_t size_m;
                char*  data;  } my_str_t;

int my_str_create(my_str_t* str, size_t buf_size);

void my_str_free(my_str_t* str);

int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size);

size_t my_str_size(const my_str_t* str);

size_t my_str_capacity(const my_str_t* str);

int my_str_empty(const my_str_t* str);

int my_str_getc(const my_str_t* str, size_t index);

#endif