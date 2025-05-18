# TIMER IN LINUX

## DESCRIPTION

```C
#include <sys/timerfd.h>

int timerfd_create(int clockid, int flags);

int timerfd_settime(int fd, int flags,
                    const struct itimerspec *new_value,
                    struct itimerspec *_Nullable old_value);
int timerfd_gettime(int fd, struct itimerspec           *curr_value);
```

These system calls create and operate a timer that delivers timer expiration notifications via a file descriptor. Therefore, those notifications may be monitored by **select()**, **poll()** and **epoll**

## Operating on a timer file descriptor

The file descriptor returned by **timerfd_create()** supports the following additional operations:

- read(): If the timer has expired one or more times since its settings were last modified using **timerfd_settime()** or since last successful **read()**, then the buffer given to **read()** returns the number of expirations that have occurred.
If no timer expirations have occurred at the time of the **read()**, then the call either blocks until the next timer expiration or fails with the error **EAGAIN** if the fd has been made nonblocking mode.

- poll(), select(), epoll(): IN flag.

- ioctl()

- close()

## RETURN VALUE

On success, **timerfd_create()** returns a new file descriptor.  On error, -1 is returned and errno is set to indicate the error.

**timerfd_settime()** and **timerfd_gettime()** return 0 on success; on error they return -1, and set errno to indicate the error.