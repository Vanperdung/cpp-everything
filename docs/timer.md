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

## timerfd_settime()

This function is used to start or stop the timer referred to by the file descriptor fd.

The **new_value** argument specifies the initial expiration and interval for the timer. The **itimerspec** structure used for this argument is described in [itimerspec](https://man7.org/linux/man-pages/man3/itimerspec.3type.html).

**new_value.it_value** specifies the initial expiraiton of the timer in seconds and nanoseconds. Setting either field of **new_value.it_value** to a nonzero value starts the timer. Otherwise; setting both fields of **new_value.it_value** to a zero value stops the timer.

Setting one or both fields of **new_value.it_interval** to nonzero values specifies the period, in seconds and nanoseconds, for repeated timer expirations after the initial expiration. If both fields of **new_value.it_interval** are zero, the timer expires just once, at the time specified by **new_value.it_value**.

The **flags** argument is a bit mask that can include the following values:

- TFD_TIMER_ABSTIME: should be used.

- TFD_TIMER_CANCEL_ON_SET: