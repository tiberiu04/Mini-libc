// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd) {
	int return_value = syscall(__NR_close, fd);

    if (return_value < 0) {
        errno = -return_value;
        return -1;
    }
    return return_value;
}
