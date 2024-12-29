#include <../include/stdio.h>
#include <unistd.h>
#include <string.h>

int puts(const char *str) {
    write(1, str, strlen(str));
    write(1, "\n", 1);

    return strlen(str);
}
