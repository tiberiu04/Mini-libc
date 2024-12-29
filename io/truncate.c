// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length) {
    int return_value = syscall(__NR_truncate, path, length);
	if (return_value < 0) {
		errno = -return_value;
		return -1;
	}

    return return_value;
}
