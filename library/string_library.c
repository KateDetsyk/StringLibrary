#include "string_library.h"
#include <stdlib.h>

//typedef struct {size_t capacity_m;     possible size
//                size_t size_m;         current string size
//                char*  data;  } my_str_t; data-вказівник на блок памяті
static size_t len(const char *cstr);
static void change_size_m(my_str_t* str);

static size_t len(const char *cstr) {
    size_t i = 0;
    while (cstr[i] != '\0'){
        i++;
    }
    return i;
}

static void change_size_m(my_str_t* str) {
    size_t index = 0;
    str->size_m = 0;
    while (str->data[index] != '\0') {
        str->size_m++;
        index++;
    }
}

int my_str_create(my_str_t* str, size_t buf_size){
    //STAND OUT MEMORY
    str->data = malloc(buf_size+1);
    //check if memory stand out
    if (str->data != NULL) {
        str->capacity_m = buf_size + 1;
        str->size_m = 0;
        str->data[0] = '\0'; //last elem must be \0
        return 0;
    }
    return -1;
}

//! Звільняє пам'ять, знищуючи стрічку.
//! Аналог деструктора інших мов.
void my_str_free(my_str_t* str){
    str->data = NULL;
    str->size_m = 0;
    str->capacity_m = 0;
}


//!============================================================================
//! Інформація про стрічку
//!============================================================================

//! Повертає розмір стрічки.
//! Для нульового вказівника -- 0.
size_t my_str_size(const my_str_t* str){
    if (str != NULL) {
        return str->size_m;
    }
    return 0;
}

//! Повертає розмір буфера.
//! Для нульового вказівника -- 0.
size_t my_str_capacity(const my_str_t* str){
    if (str != NULL) {
        return str->capacity_m-1;
    }
    return 0;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str){
    return my_str_size(str) == 0;
}

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки,
//! включаючи переданий нульовий вказівник.
//! Тому, власне, int а не char
int my_str_getc(const my_str_t* str, size_t index){
    if (!str) {
        return -1;
    }
    if (index >= str->size_m){
        return -1;
    }
    return str->data[index];
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
int my_str_putc(my_str_t* str, size_t index, char c){
    if (!str) {
        return -1;
    }
    if (index >= str->size_m) {
        return -1;
    }
    str->data[index] = c;
    return 0;
}

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================
//! Якщо буфер недостатній -- ці функції збільшують його,
//! викликом my_str_reserve().
//! Розумним є буфер кожного разу збільшувати в 1.8-2 рази.
//! ==========================================================================

//! Збільшує буфер стрічки, із збереженням вмісту,
//! якщо новий розмір більший за попередній,
//! не робить нічого, якщо менший або рівний.
//! (Як показує практика, це -- корисний підхід).
//! Для збільшення виділяє новий буфер, копіює вміст
//! стрічки (size_m символів -- немає сенсу копіювати
//! решту буфера) із старого буфера та звільняє його.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_reserve(my_str_t* str, size_t buf_size){
    if (buf_size > str->capacity_m) {
        char* pointer = malloc(buf_size+1);
        size_t sm = str->size_m;
        if (pointer == NULL) {
            return -2;
        }
        for (size_t i = 0; i < str->size_m; i++){
            pointer[i] = str->data[i];
        }
        my_str_free(str);
        str->capacity_m = buf_size;
        str->size_m = sm;
        str->data = pointer;
        return 0;
    }
}

//! Додає символ в кінець.
//! Повертає 0, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- помилка виділення додаткової пам'яті.
int my_str_pushback(my_str_t* str, char c){
    if (!str){
        return -1;
    }
    if (str->size_m >= str->capacity_m-1) {
        my_str_reserve(str, str->capacity_m*2);
    }
    str->data[str->size_m] = c;
    str->size_m++;
    str->data[str->size_m] = '\0';
    return 0;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір, buf_size == 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою, не змінювати стрічку.
//! Пам'ять виділяється динамічно. Не слід викликати my_str_create(),
//! більше підійде my_str_resize() або my_str_reserve().
//! Коди завершення:
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    if (buf_size == 0){
        buf_size = len(cstr);
    } else if (buf_size < len(cstr)){
        return -1;
    }
    my_str_free(str);
    my_str_reserve(str, buf_size);
    for (size_t i = 0; i < len(cstr); i++) {
        my_str_pushback(str, cstr[i]);
    }
    return 0;
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- якщо стрічка порожня.
int my_str_popback(my_str_t* str){
    if (!str) {
        return -1;
    }
    if (str->size_m > 0) {
        char last = str->data[str->size_m-1];
        str->data[str->size_m-1] = '\0';
        str->size_m--;
        return last;
    }
    return -2;
}

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
//! Уточнення (чомусь ця ф-ція викликала багато непорозумінь):
//! стрічка продовжує існувати, буфер той самий, того ж розміру, що був,
//! лише містить 0 символів -- єдине, що вона робить, це size_m = 0.
void my_str_clear(my_str_t* str){
    str->size_m = 0;
    str->data[0] = '\0';
}

//! Робить буфер розміром, рівний необхідному:
//! так, щоб capacity_m == size_t. Єдиний "офіційний"
//! спосіб зменшити фактичний розмір буфера.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_shrink_to_fit(my_str_t* str){
    char* pointer = malloc(str->size_m+1);
    size_t sm = str->size_m;
    if (pointer == NULL) {
        return -2;
    }
    for (size_t i = 0; i < str->size_m; i++){
        pointer[i] = str->data[i];
    }
    str->size_m = sm;
    str->capacity_m = str->size_m;
    str->data = pointer;
    return 0;
}

//! Якщо new_size менший за поточний розмір -- просто
//! відкидає зайві символи (зменшуючи size_m). Якщо
//! більший -- збільшує фактичний розмір стрічки,
//! встановлюючи нові символи рівними sym.
//! За потреби, збільшує буфер.
//! Сподіваюся, різниця між розміром буфера та фактичним
//! розміром стрічки зрозуміла?
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_resize(my_str_t* str, size_t new_size, char sym) {
    if (new_size < str->size_m) {
        str->size_m = new_size;
        str->data[str->size_m] = '\0';
        return 0;
    }
    if (new_size > str->capacity_m) {
        my_str_reserve(str, new_size);
    }
    for (size_t i = str->size_m+1; i < str->capacity_m; i++) {
        str->data[i] = sym;
    }
    return 0;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from) {
    size_t index = -1;
    for (size_t i = from; i < str->size_m; i++) {
        for (size_t j = 0; j < tofind->size_m; j++) {
            if (my_str_getc(str, i+j) != my_str_getc(tofind, j)) {
                break;
            }
            index = i;
        }
    }
    return index;
}

//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(const my_str_t* str1, const my_str_t* str2) {
    if (str1->size_m < str2->size_m) {
        return -1;
    } else if (str2->size_m < str1->size_m) {
        return 1;
    } else if (str1->size_m == str2->size_m) {
        for (size_t i = 0; i < str1->size_m; i++) {
            if (my_str_getc(str1, i) < my_str_getc(str2, i)) {
                return -1;
            } else if (my_str_getc(str2, i) < my_str_getc(str1, i)) {
                return 1;
            }
        }
    }
    return 0;
}

//! Порівняти стрічку із С-стрічкою, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2) {
    if (str1->size_m < len(cstr2)) {
        return -1;
    } else if (len(cstr2) < str1->size_m) {
        return 1;
    } else if (len(cstr2) == str1->size_m) {
        for (size_t i = 0; i < str1->size_m; i++) {
            if (my_str_getc(str1, i) < cstr2[i]) {
                return -1;
            } else if (cstr2[i] < my_str_getc(str1, i)) {
                return 1;
            }
        }
    }
    return 0;
}

//! Знайти перший символ в стрічці, повернути його номер
//! або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from) {
    for (size_t i = from; i < str->size_m; i++) {
        if (my_str_getc(str, i) == tofind) {
            return i;
        }
    }
    return -1;
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або (size_t)(-1), якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(int)) {
    for (size_t i = 0; i < str->size_m; i++){
        if (predicat(my_str_getc(str, i))){
            return my_str_getc(str, i);
        }
    }
    return -1;
}

//! Прочитати стрічку із файлу. Читає цілий файл.
//! Не давайте читанню вийти за межі буфера! За потреби --
//! збільшуйте буфер.
//! Рекомендую скористатися fgets().
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file(my_str_t* str, FILE* file) {
    if (!file) {
        return -1;
    }
    int c;
    while ((c = fgetc(file)) && c != EOF) {
        //pushback will stand out more memory if not enough
        my_str_pushback(str, c);
    }
    return 0;
}

//! Аналог my_str_read_file, із stdin.
int my_str_read(my_str_t* str) {
    my_str_read_file(str, stdin);
    return 0;
}


//! Записати стрічку в файл:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write_file(const my_str_t* str, FILE* file) {
    if (file != NULL) {
        fputs (str->data, file);
        return 0;
    }
    return -1;
}

//! Записати стрічку на консоль:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write(const my_str_t* str, FILE* file) {
    my_str_write_file(str, stdout);
    return 0;
}

//! На відміну від my_str_read_file(), яка читає до кінця файлу,
//! читає по вказаний delimiter, за потреби
//! збільшує стрічку.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter) {
    int c;
    while ((c = fgetc(file)) != delimiter && c != EOF) {
        //pushback will stand out more memory if not enough
        my_str_pushback(str, c);
    }
    return 0;
}