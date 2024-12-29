#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <internal/syscall.h>

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;
    rem.tv_sec = 0;
    rem.tv_nsec = 0;

    int res = nanosleep(&req, &rem);

    return (res == 0) ? 0 : rem.tv_sec;
}
