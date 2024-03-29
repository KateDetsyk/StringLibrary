#include <fcntl.h>
#include <stdio.h>

#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

typedef struct {size_t capacity_m;
                size_t size_m;
                char*  data;  } my_str_t;

static size_t len(const char *cstr);
static void change_size_m(my_str_t* str);


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

size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from);

int my_str_cmp(const my_str_t* str1, const my_str_t* str2);

int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2);

size_t my_str_find_c(const my_str_t* str, char tofind, size_t from);

size_t my_str_find_if(const my_str_t* str, int (*predicat)(int));

int my_str_read_file(my_str_t* str, FILE* file);

int my_str_read(my_str_t* str);

int my_str_write_file(const my_str_t* str, FILE* file);

int my_str_write(const my_str_t* str, FILE* file);

int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter);
#endif
