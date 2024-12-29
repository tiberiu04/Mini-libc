// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    // Doing the syscall required for mmap
    long return_value = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (return_value < 0) {
        // It did not work
        errno = -return_value;
        return (void *)-1;
    }

    return (void *)return_value;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags) {
    // Doing the syscall
    void *new = (void *) syscall(__NR_mremap, old_address, old_size, new_size, flags);
    // Checking if it worked
    if (new == MAP_FAILED)
        return MAP_FAILED;

    return new;
}

int munmap(void *addr, size_t length) {
    // Doing the syscall required for munmap with the specific arguments
    int return_value = syscall(__NR_munmap, addr, length);

    if (return_value < 0) {
        errno = -return_value;
        return -1;
    }

    return 0;
}
