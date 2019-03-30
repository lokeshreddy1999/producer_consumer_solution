# producer_consumer_solution
complete solution(deadlock free) using semaphore  producer_consumer_solution

Problem Statement  
We have a buffer of fixed size. 
 1)A producer can produce an item and can place in the buffer.
 2)A consumer can pick items and can consume them
 We need to ensure that when a producer is placing an item in the buffer, then 
 at the same time consumer should not consume any item. In this problem, buffer is the critical section.

Before let me expain what i have done 
I used threads as the main agents to do the the required functions(producing and consuming)
I selected threads so that my program will run for many threads at the same time(i.e.PARALLEL PROCESS)
Then I implmented semphores on my OWN semaphore (in two ways)

First way:which uses only  while loop but disadvantage is Busy Waiting(wastes cpu cycles)  
  
Secondway Way:which uses queue datastucture to store block() threads

see the files semphores library files to get full code.
Here i implemented 3 main semaphores functions  
1) sem_init_(for inilization of any semapores)
2) sem_wait (act as w(s) signal)
3) sem_post (act as v(s) signal) 

here i implemented the same function name and syntax ( such as type of parameteres and no_of para) as there in inbuilt.
i implemented in that way because i want to test with inbuilt semaphore code(i.e. i will just import my semaphore library 
instead to see whether is it giving simillar seqeuence of threads with the solution obtained by inbuilt semapore library)  
this is the good way for testingtypedef struct


struct for  first way
{ 
 atomic_int s;// atomic varible to protect through control section  
 pthread_mutex_t lock1; // lock for sem wait   
 
}



struct for the second way {
   atomic_int s;  // semaphore varible
   queue Q;           // queue for storing blocked threads
   pthread_mutex_t lock1; 
   pthread_mutex_t lock2;
   pthread_mutex_t excusion_between_signal_ans_wait ;
}




prerequisite : c language,idea about semaphores
 
The solution i have written for this problem is deadlock free 

Initialization of semaphores 

Solution( same thing as implemented):

mutex = 1
Full = 0 // Initially, all slots are empty. 
Empty = n // All slots are empty initially.


void* producer
{
produce an item

wait(empty);
wait(mutex);

put in buffer

signal(mutex);
signal(full);

}


void* consumer {

wait(full);
wait(mutex);

 remove item from buffer

signal(mutex);
signal(empty);

 consumes item

}


apart from this code in semaphore implemtation i used linked list bascially it is the queue formed by linked list  
