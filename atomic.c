#include "semaphore_lib_through_while_loop.h"

 
sem_t acnt;
int cnt;
 
void *f()
{
    for(int n = 0; n < 9000; ++n) {
        ++cnt;
        sem_post(&acnt);
        // for this example, relaxed memory order is sufficient, e.g.
        // atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
    }
    
}
 
int main(void)
{

    printf("ghhjkkl\n");  
    pthread_t thr[10];
    for(int n = 0; n < 10; ++n)
        pthread_create(&thr[n], NULL,f,NULL);
    for(int n = 0; n < 10; ++n)
        pthread_join(thr[n], NULL);
 
    printf("The atomic counter is %u\n", acnt.s);
    printf("The non-atomic counter is %u\n", cnt);
    printf("%d\n",acnt.s-cnt);
}