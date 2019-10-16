//example of using library's functions and program than use library's functions.
#include "library/string_library.h"
#include <stdio.h>
#include <ctype.h>

void prog_two() {
    FILE *file = fopen("..\\file_to_read.txt", "r");
    FILE *file_write = fopen("..\\file_to_write.txt", "w");

    my_str_t string1;
    my_str_create(&string1, 99);
    my_str_t string2;
    my_str_create(&string2, 99);

    my_str_read_file(&string1, file);

    int in_word = 0;

    for (size_t i = 0; i < my_str_size(&string1); i++) {
        if (!isspace(my_str_getc(&string1, i))) {
            in_word = 1;
            if (!ispunct(my_str_getc(&string1, i))) {
                if (isupper(my_str_getc(&string1, i))) {
                    my_str_pushback(&string2, tolower(my_str_getc(&string1, i)));
                } else {
                    my_str_pushback(&string2, my_str_getc(&string1, i));
                }
            }
        } else {
            if (in_word == 1) {
                my_str_pushback(&string2, my_str_getc(&string1, i));
                in_word = 0;
            }
        }
    }

    my_str_write_file(&string2, file_write);

    fclose(file);
    fclose(file_write);
    my_str_free(&string1);
    my_str_free(&string2);
}
void main() {

    prog_two();

    my_str_t str;
    if (my_str_create(&str, 20) == 0) {
        printf("String was successfully created.\n");
    }
}