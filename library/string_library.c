#include "string_library.h"
#include <stdlib.h>

//typedef struct {size_t capacity_m;     possible size
//                size_t size_m;         current string size
//                char*  data;  } my_str_t; data-вказівник на блок памяті
size_t len(const char *cstr);

int my_str_create(my_str_t* str, size_t buf_size){
    if (!str) {
        return -1;
    }
    //STAND OUT MEMORY
    str->data = malloc(buf_size+1);
    //check if memory stand out
    if (str->data != NULL) {
        str->capacity_m = buf_size + 1;
        str->size_m = 0;
        str->data[0] = '\0'; //last elem must be \0
        return 0;
    }
    return 0;
}

//! Звільняє пам'ять, знищуючи стрічку.
//! Аналог деструктора інших мов.
void my_str_free(my_str_t* str){
    str->data = NULL;
    str->size_m = 0;
    str->capacity_m = 0;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір, buf_size == 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою, не змінювати стрічку.
//! Пам'ять виділяється динамічно. Не слід викликати my_str_create(),
//! більше підійде my_str_resize() або my_str_reserve().
//! Коди завершення:
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    if (!str) {
        return -1;
    }
    if (buf_size == 0){
        str->capacity_m = len(cstr);
        //////////
    }else if(buf_size < len(cstr)){
        return -1;
    }
    return 0;
}

size_t len(const char *cstr) {
    size_t i = 0;
    while (cstr[i] != '\0'){
        i++;
    }
    return i;
}

//! Повертає розмір стрічки.
//! Для нульового вказівника -- 0.
size_t my_str_size(const my_str_t* str){
    return str->size_m;
}

//! Повертає розмір буфера.
//! Для нульового вказівника -- 0.
size_t my_str_capacity(const my_str_t* str){
    return str->capacity_m;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str){
    return my_str_size(str) == 0;
}

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки,
//! включаючи переданий нульовий вказівник.
//! Тому, власне, int а не char
int my_str_getc(const my_str_t* str, size_t index){
    for (int i = 0; i < str->size_m-1; i++){
        if (i == index){
            return str->data[i];
        }
    }
    return -1;
}