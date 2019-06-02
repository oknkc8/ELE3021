#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "pthread.h"
//#define NULL 0
//#define PGSIZE 4096

int thread_create(thread_t *thread, void *(*start_routine)(void*), void *arg){
    void *stack = (void*)malloc(PGSIZE*2);
    
    if((int)stack <= 0){
        printf(1, "E: failed to malloc new stack in thread_create\n");
        return -1;
    }
    if((int)stack % PGSIZE){
        stack += PGSIZE - ((int)stack % PGSIZE);
    }

    *thread = tcopy((int)start_routine, arg, stack);

    return 0;
}

int thread_exit(void *retval){
    texit(retval);
    return 0;
}

int thread_join(thread_t thread, void **retval){
    void *stack;
    tjoin(thread, &stack, retval);
    free(stack);
    return 0;
}
/*
int
sys_thread_create(void)
{
  int thread, start_routine, arg;

  if(argint(0, &thread) < 0)
    return -1;
  if(argint(1, &start_routine) < 0)
    return -1;
  if(argint(2, &arg) < 0)
    return -1;

  return thread_create((thread_t*)thread, (void*)start_routine, (void*)arg);
  
}

int
sys_thread_exit(void)
{
  int retval;

  if(argint(0, &retval) < 0)
    return -1;

  return thread_exit((void*)retval);
}

int
sys_thread_join(void)
{
  int thread, retval;

  if(argint(0, &thread) < 0)
    return -1;
  if(argint(1, &retval) < 0)
    return -1;

  return thread_join((thread_t)thread, (void**)retval);
}*/