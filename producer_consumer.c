#include "semaphore_lib_through_while_loop.h" 
 
#define SIZE 5 //give the size of buffer
#define NUMB_THREADS 6 // specify the no of thread

 
typedef int buffer_t; // define type of buffer
buffer_t buffer[SIZE];  
int buffer_index; // it will points to last element in buffer
 


sem_t buffer_mutex;//(actually mutex but implemeted as binary semaphore.control section to protect while producer produces / consumer consumes)
sem_t full_sem; //  stop producer if buffer is full
sem_t empty_sem; // stop consumer if buffer is empty 
 
 
void insertbuffer(buffer_t value)  
{
    if (buffer_index < SIZE) 
    {
       
        buffer[buffer_index++] = value;
    } 
    else 
    {
        printf("Buffer overflow\n");
    }
}
 
buffer_t dequeuebuffer() 
{
    if (buffer_index > 0) 
    {
        return buffer[--buffer_index]; 
    } 
    else 
    {
        printf("Buffer underflow\n");
    }
    return 0;
}
 
 
void *producer(void *thread_n) 
{
    

    int thread_numb = *(int *)thread_n;
    printf("entered producer %d\n",thread_numb);
    buffer_t value;
    int i=0;
    
        sleep(rand() % 10);
        value = rand() % 100;
        sem_wait(&full_sem); 
        sem_wait(&buffer_mutex);
        insertbuffer(value);
        sem_post(&buffer_mutex);
        sem_post(&empty_sem); 
        printf("Producer %d added %d to buffer\n", thread_numb, value);
        
}
 
void *consumer(void *thread_n) 
{
    int thread_numb = *(int *)thread_n;
    printf("entered consumer %d\n",thread_numb);
    buffer_t value;
    int i=0;
      
        sem_wait(&empty_sem);
        sem_wait(&buffer_mutex);
        value = dequeuebuffer(value);
        sem_post(&buffer_mutex);
        sem_post(&full_sem); 
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
   
    
}
 
int main(int argc, int **argv) 
{
    
    buffer_index = 0;
 
    sem_init(&buffer_mutex, // sem_t *sem
             0, // int pshared. 0 = shared between threads of process,  1 = shared between processes
             1);// value of the semaphore
    sem_init(&full_sem,0,SIZE);
    sem_init(&empty_sem,0,0);
    
    pthread_t thread_producer[NUMB_THREADS];// threads for producer   
    pthread_t thread_consumer[NUMB_THREADS];// threads for producer
    int thread_numb[NUMB_THREADS];
    
    for (int i = 0; i < NUMB_THREADS;i++) 
    {
        thread_numb[i] = i;
        pthread_create(thread_producer + i,NULL,producer,thread_numb + i);
        pthread_create(thread_consumer + i,NULL,consumer,thread_numb + i);
    }
     
    for (int i = 0; i < NUMB_THREADS; i++)
    {
         pthread_join(thread_producer[i], NULL);
         pthread_join(thread_consumer[i], NULL);
    }

    return 0;
}