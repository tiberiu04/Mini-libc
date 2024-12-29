// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st) {
    // Doing the syscall
	int ret = syscall(__NR_fstat, fd, st);

    if (ret < 0) {
        // It didn't work
        errno = -ret;
        return -1;
    }

    return ret;
}
