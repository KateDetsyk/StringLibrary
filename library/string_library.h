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

int my_str_putc(my_str_t* str, size_t index, char c);

int my_str_reserve(my_str_t* str, size_t buf_size);

int my_str_pushback(my_str_t* str, char c);

int my_str_popback(my_str_t* str);

void my_str_clear(my_str_t* str);

int my_str_shrink_to_fit(my_str_t* str);

int my_str_resize(my_str_t* str, size_t new_size, char sym);


int my_str_read_file(my_str_t* str, FILE* file);

int my_str_read(my_str_t* str);

int my_str_write_file(const my_str_t* str, FILE* file);
#endif
