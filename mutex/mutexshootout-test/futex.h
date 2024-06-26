#pragma once

#if USE_LINUX

#include <limits.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <atomic>

/* Atomically check if '*futex == value', and if so, go to sleep */
static inline void futex_wait(std::atomic<int> *futex, int value)
{
    syscall(SYS_futex, futex, FUTEX_WAIT_PRIVATE, value, NULL);
}

/* Wake up 'limit' threads currently waiting on 'futex' */
static inline void futex_wake(std::atomic<int> *futex, int limit)
{
    syscall(SYS_futex, futex, FUTEX_WAKE_PRIVATE, limit);
}

/* Wake up 'limit' waiters, and re-queue the rest onto a different futex */
static inline void futex_requeue(std::atomic<int> *futex,
                                 int limit,
                                 std::atomic<int> *other)
{
    syscall(SYS_futex, futex, FUTEX_REQUEUE_PRIVATE, limit, INT_MAX, other);
}

#ifndef FUTEX_LOCK_PI2_PRIVATE
#define FUTEX_LOCK_PI2		13
#define FUTEX_LOCK_PI2_PRIVATE	(FUTEX_LOCK_PI2 | FUTEX_PRIVATE_FLAG)
#endif

static inline void futex_lock_pi(std::atomic<int> *futex, struct timespec *timeout)
{
    /* Note: val is ignored for FUTEX_LOCK_PI, just fill a dummy value. */
    int val = 0;
    syscall(SYS_futex, futex, FUTEX_LOCK_PI2_PRIVATE, val, timeout);
}

static inline void futex_unlock_pi(std::atomic<int> *futex)
{
    syscall(SYS_futex, futex, FUTEX_UNLOCK_PI_PRIVATE);
}
#endif
