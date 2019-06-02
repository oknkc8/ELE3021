#define NULL 0
#define PGSIZE 4096

int thread_create(thread_t *thread, void *(*start_routine)(void*), void *arg);
int thread_exit(void *retval);
int thread_join(thread_t thread, void **retval);