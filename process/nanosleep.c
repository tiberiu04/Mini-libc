#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <internal/syscall.h>

unsigned int nanosleep(const struct timespec *req, struct timespec *rem) {
    // Doing the syscall
    int return_value = syscall(__NR_nanosleep, req, rem);

    if (return_value < 0) {
        errno = -return_value;
        return -1;
    }

    return 0;
}
