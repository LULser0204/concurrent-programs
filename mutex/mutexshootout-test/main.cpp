#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <thread>
#include <random>
#include <cctype>
#include <pthread.h>
#include <time.h>

#include <algorithm> //for sort

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "atomic.h"
#include "cond.h"
#include "futex.h"
#include "mutex.h"
#include "spinlock.h"
#include "stopwatch.hpp"

#include "hashing.hpp"
#include "lru_cache.hpp"

#include "alt_mutex.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/null_mutex.hpp>

#ifdef USE_SKINNY_MUTEX
#include "skinny_mutex/skinny_mutex.h"
#endif

#define MEASURE_TIME  100

#define THREAD_MAX 4
#define LOCK_MAX (THREAD_MAX + 1)
#define THREAD_ITERS \
    50  // The times for a thread that tries to acquire the next lock
#define TOTAL_ITERS (THREAD_MAX * THREAD_ITERS)

long long ns_time() 
{
    struct timespec tt;
    clock_gettime(CLOCK_MONOTONIC, &tt);
    return tt.tv_sec * 1e9 + tt.tv_nsec;
}

struct common {
    /* As https://github.com/jserv/skinny-mutex/blob/master/perf.c#L116 explain:
     *
     * Here the numbers of mutex is the number of threads add one, and those are
     * arranged in a ring. Each thread will hold a lock first, and also tries to
     * acquire the next lock in the ring. When it acquires the next lock, it
     * drops the previous lock. Then it tries to acquire the next next lock, and
     * so on.
     *
     * The effect is that at every moment, only one thread is able to acquire
     * two locks and so make progress; in doing so, it releases a lock allowing
     * another thread to make progress and then promptly gets blocked.*/
    mutex_t mutexes[LOCK_MAX];

    pthread_mutex_t ready_mutex;
    pthread_cond_t ready_cond;
    int ready_count;
};

/* Every thread will have its own 'thread_ctx' structure.
 * It contains a 'common' structure which references to
 * some share information between any other threads, and
 * the remaining structure members are independent for each
 * thread. */
struct thread_ctx {
    struct common *common_ctx;
    pthread_mutex_t start_mutex;
    int id;

    long long start;
    long long stop;
};



void* thread_func(void *arg) 
{
    struct thread_ctx *ctx = (struct thread_ctx *) arg;
    struct common *common_thread = ctx->common_ctx;
    int i = ctx->id;


    /* Lock our first mutex */
    mutex_lock(&common_thread->mutexes[i]);
    
    /* Every thread will signal the main thread. So after main thread get
     * enough numbers of signal, it knows that everyones are on the starting
     * line. */
    pthread_mutex_lock(&common_thread->ready_mutex);
    if (++common_thread->ready_count == THREAD_MAX)
        pthread_cond_signal(&common_thread->ready_cond);
    pthread_mutex_unlock(&common_thread->ready_mutex);

    /* Line up to start */
    pthread_mutex_lock(&ctx->start_mutex);
    pthread_mutex_unlock(&ctx->start_mutex);

    ctx->start = ns_time();

    /* Core routine here */
    for (int loop = 1; loop < THREAD_ITERS; loop++) {
        int next = (i + 1) % LOCK_MAX;
        mutex_lock(&common_thread->mutexes[next]);
        mutex_unlock(&common_thread->mutexes[i]);
        i = next;
    }

    ctx->stop = ns_time();
    
    
    mutex_unlock(&common_thread->mutexes[i]);
    return NULL;
}

void init_common(common *common_init) 
{
    for (int i = 0; i < LOCK_MAX; i++)
        mutex_init(&common_init->mutexes[i], NULL);
        
    pthread_mutex_init(&common_init->ready_mutex, NULL);
    pthread_cond_init(&common_init->ready_cond, NULL);
    common_init->ready_count = 0;
}

void init_ctx(thread_ctx *ctx, common *common_init_ctx, int id) 
{
    ctx->common_ctx = common_init_ctx;
    ctx->id = id;
    
    pthread_mutex_init(&ctx->start_mutex, NULL);
}

void free_common(common *common_free) 
{
    for (int i = 0; i < LOCK_MAX; i++)
        mutex_destroy(&common_free->mutexes[i]);
        
    pthread_mutex_destroy(&common_free->ready_mutex);
    pthread_cond_destroy(&common_free->ready_cond);
}

void free_ctx(thread_ctx *ctx) 
{
    pthread_mutex_destroy(&ctx->start_mutex);
}

template<typename Mutex>
long long contention_test() {
    struct common common_t;
    struct thread_ctx ctx[THREAD_MAX];
    pthread_t threads[THREAD_MAX];

    init_common(&common_t);

    for (int i = 0; i < THREAD_MAX; i++) {
        init_ctx(&ctx[i], &common_t, i);
        
        /* Lock before creating the thread, so we can run their main routine
         * after every thread are created. */
        pthread_mutex_lock(&ctx[i].start_mutex);
        pthread_create(&threads[i], NULL, thread_func, &ctx[i]);
    }

    /* Wait until every thread signal the main thread */
    pthread_mutex_lock(&common_t.ready_mutex);
    while (common_t.ready_count < THREAD_MAX)
        pthread_cond_wait(&common_t.ready_cond, &common_t.ready_mutex);
    pthread_mutex_unlock(&common_t.ready_mutex);

    /* Great! Let's release the lock so every thread can start the
     * core routine. */
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_mutex_unlock(&ctx[i].start_mutex);

    for (int i = 0; i < THREAD_MAX; i++) {
        pthread_join(threads[i], NULL);
        free_ctx(&ctx[i]);
    }

    free_common(&common_t);

    /* Let's check the time range to finish TOTAL_ITERS times of
     * lock contention. */
    long long start = ctx[0].start;
    long long stop = ctx[0].stop;
    for (int i = 1; i < THREAD_MAX; i++) {
        start = std::min(ctx[i].start, start);
        stop = std::max(ctx[i].stop, stop);
    }

    return stop - start;
}

/*     this is for skinny-mutex                     */
#ifdef USE_SKINNY_MUTEX
template<>
long long contention_test<skinny_mutex_t>() {
    struct common {
        skinny_mutex_t mutexes[LOCK_MAX];
        
        skinny_mutex_t ready_mutex;
        pthread_cond_t ready_cond;
        int ready_count;
    };

    struct thread_ctx {
        common *common_t;
        skinny_mutex_t start_mutex;
        int id;
        
        long long start;
        long long stop;
    };

    struct common common_t;
    struct thread_ctx ctx[THREAD_MAX];
    pthread_t threads[THREAD_MAX];

    /*  init_common(&common)   */
    for (int i = 0; i < LOCK_MAX; i++)
        skinny_mutex_init(&common_t.mutexes[i]);
        
    skinny_mutex_init(&common_t.ready_mutex);
    pthread_cond_init(&common_t.ready_cond, NULL);
    common_t.ready_count = 0;

    for (int i = 0; i < THREAD_MAX; i++) {
        
        /* init_ctx(&ctx[i], &common, i) */
        ctx[i].common_t = &common_t;
        ctx[i].id = i;
        
        skinny_mutex_init(&ctx[i].start_mutex);
        
        skinny_mutex_lock(&ctx[i].start_mutex);
        
        /* pthread_create(&threads[i], NULL, thread_func, &ctx[i]); */
        pthread_create(&threads[i], NULL, [](void *arg) -> void* {
            struct thread_ctx *ctx = (struct thread_ctx *) arg;
            struct common *common_t = ctx->common_t;
            int i = ctx->id;

            skinny_mutex_lock(&common_t->mutexes[i]);
            
            skinny_mutex_lock(&common_t->ready_mutex);
            if (++common_t->ready_count == THREAD_MAX)
                pthread_cond_signal(&common_t->ready_cond);
            skinny_mutex_unlock(&common_t->ready_mutex);

            skinny_mutex_lock(&ctx->start_mutex);
            skinny_mutex_unlock(&ctx->start_mutex);

            ctx->start = ns_time();

            for (int loop = 1; loop < THREAD_ITERS; loop++) {
                int next = (i + 1) % LOCK_MAX;
                skinny_mutex_lock(&common_t->mutexes[next]);
                skinny_mutex_unlock(&common_t->mutexes[i]);
                i = next;
            }

            ctx->stop = ns_time();
            
            skinny_mutex_unlock(&common_t->mutexes[i]);

            return NULL;
        }, &ctx[i]);
    }

    skinny_mutex_lock(&common_t.ready_mutex);
    while (common_t.ready_count < THREAD_MAX)
        skinny_mutex_cond_wait(&common_t.ready_cond, &common_t.ready_mutex);
    skinny_mutex_unlock(&common_t.ready_mutex);

    for (int i = 0; i < THREAD_MAX; i++)
        skinny_mutex_unlock(&ctx[i].start_mutex);

    for (int i = 0; i < THREAD_MAX; i++) {
        pthread_join(threads[i], NULL);
        
        /*      free_ctx(&ctx[i]);               */
        skinny_mutex_destroy(&ctx[i].start_mutex);
    }

    /*        free_common(&common);       */
    for (int i = 0; i < LOCK_MAX; i++)
        skinny_mutex_destroy(&common_t.mutexes[i]);
        
    skinny_mutex_destroy(&common_t.ready_mutex);
    pthread_cond_destroy(&common_t.ready_cond);

    long long start = ctx[0].start;
    long long stop = ctx[0].stop;
    for (int i = 1; i < THREAD_MAX; i++) {
        start = std::min(ctx[i].start, start);
        stop = std::max(ctx[i].stop, stop);
    }

    return stop - start;
}
#endif

int main(int argc, char *argv[]) {
    if (argc != 3) {
#if _WIN32
        std::cerr << "Usage: " << argv[0] << " threadCount skinny|std|boost|cs0|cs4k|srw\n";
#else
        std::cerr << "Usage: " << argv[0] << " threadCount skinny|std|boost\n";
#endif
        return 1;
    }

    char *end;
    size_t thread_count = std::strtoul(argv[1], &end, 10);
    if (thread_count == 0 || thread_count > 1000) {
        std::cerr << "Invalid thread count.\n";
        return 1;
    }

    std::string mutex_arg{argv[2]};
    std::transform(mutex_arg.begin(), mutex_arg.end(), mutex_arg.begin(), ::tolower);

    long long times[MEASURE_TIME];
    long long total_time = 0;

    if (mutex_arg == "std") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<std::mutex>();
            total_time += times[i];
        }
    } else if (mutex_arg == "boost") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<boost::mutex>();
            total_time += times[i];
        }
    }
#if _WIN32
    else if (mutex_arg == "cs0") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<shootout::cs_mutex<0>>();
            total_time += times[i];
        }
    } else if (mutex_arg == "cs4k") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<shootout::cs_mutex<4000>>();
            total_time += times[i];
        }
    } else if (mutex_arg == "srw") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<shootout::srw_mutex>();
            total_time += times[i];
        }
    }
#endif
    else if (mutex_arg == "nolocks") {
        if (thread_count == 1) {
            for (size_t i = 0; i < MEASURE_TIME; i++) {
                times[i] = contention_test<boost::null_mutex>();
                total_time += times[i];
            }
        } else {
            std::cerr << "Only one thread allowed for non-locking.\n";
            return 1;
        }
    } else if (mutex_arg == "pthread") {
        for (size_t i = 0; i < MEASURE_TIME; i++) {
            times[i] = contention_test<skinny_mutex_t>();
            total_time += times[i];
        }
    } else {
        std::cerr << "Unknown mutex type.\n";
        return 1;
    }

    std::sort(times, times + MEASURE_TIME);
    for (int i = 0; i < MEASURE_TIME; i++) {
        std::cout << times[i] << ", ";
    }
    std::cout << std::endl;

    return 0;
}

