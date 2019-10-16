//example of using library's functions
#include "library/string_library.h"
#include <stdio.h>

void main() {
    my_str_t str;
    if (my_str_create(&str, 20) == 0) {
        printf("String was successfully created.\n");
    }
}