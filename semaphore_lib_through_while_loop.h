#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h> 

typedef struct
{ 
 atomic_int s;
 pthread_mutex_t lock1;
 pthread_mutex_t lock2;
} sem_t;
 


void sem_init( sem_t* temp,int pshared,unsigned int val)
 {
    temp->s=val;
 }


 void sem_wait(sem_t* temp)
 {
     pthread_mutex_lock(&temp->lock1);
      while(temp->s<=0)
      {

      }
      temp->s--;
     pthread_mutex_unlock(&temp->lock1);


 }

 void sem_post(sem_t* temp)
 {
   // pthread_mutex_lock(&temp->lock2);
    temp->s++;  
   // pthread_mutex_unlock(&temp->lock2);
 }









