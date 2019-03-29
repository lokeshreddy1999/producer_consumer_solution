#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h> 

typedef struct 
{
  pthread_cond_t* val;
  struct node* next;
}node; // struct for each element in qeueue of a semaphore

typedef struct 
{
  node* head;
  node* tail;
  pthread_mutex_t mutex_for_queue_operations;
  int len;

}queue; // struct for the queue in the semaphore 

void push(queue* q ,pthread_cond_t* g) 
{
   pthread_mutex_lock(&q->mutex_for_queue_operations);
    node* temp=( node*)malloc(sizeof(node));
    temp->val=g;
    if(q->head==NULL)
    {
    	q->head=temp;
    	q->tail=temp;
    	q->len=0; 
    	 
    }
    else
    {
    
    	q->tail->next=temp;
    	q->tail=temp;

    }
    q->len++;  

  pthread_mutex_unlock(&q->mutex_for_queue_operations);
}


pthread_cond_t* pop(queue* q)
{
   pthread_mutex_lock(&q->mutex_for_queue_operations);
	 if(q->len<=0)
	 {
    pthread_mutex_unlock(&q->mutex_for_queue_operations);
	 	return NULL;
	 }
	 else
	 {
    pthread_cond_t* to_give=q->head->val;	     
	 	if(q->len==1)
	 	{
	 		q->head=NULL;
	 		q->tail=NULL;
	 		q->len=0;
	 	}
	 	else
	 	{
	 		q->len--;
      q->head=q->head->next;
	 	}
    pthread_mutex_unlock(&q->mutex_for_queue_operations);
	  
   	return to_give;
	 } 
   
	 return NULL;
}


typedef struct
{
   atomic_int s;  // semaphore varible
   queue Q;           // queue for storing blocked threads
   pthread_mutex_t lock1; 
   pthread_mutex_t lock2;
  
   
   
} sem_t; // semaphore struct 
 


void sem_init( sem_t* temp,int pshared,unsigned int val) // for semaphore inilization
 {
    temp->s=val; // assign value
   // thread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
 }


 void sem_wait(sem_t* temp) //  same AS wait(S)
 {
 	pthread_mutex_lock(&temp->lock1); // saving from other threads   
    temp->s--;
    if(temp->s<0)
    {
      pthread_cond_t* cond_temp=(pthread_cond_t*)malloc(sizeof(pthread_cond_t));
      push(&temp->Q,cond_temp); 
      pthread_cond_wait(cond_temp,&temp->lock1); //block(temp) blocking temp thread 

            
    } 

    pthread_mutex_unlock(&temp->lock1);

  
}

 void sem_post(sem_t* temp)
 {
  pthread_mutex_lock(&temp->lock2); // saving from other threads

    temp->s++;    
    if(temp->s<=0)
    {
      
    	pthread_cond_t* cond=pop(&temp->Q);
    	if(cond!=NULL)
      {
      pthread_cond_signal(cond);   // wake up (selected thread)
      }

    }
  pthread_mutex_unlock(&temp->lock2);

 }









