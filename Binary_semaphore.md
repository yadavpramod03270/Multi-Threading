# Binary Semaphore

->Binary Semaphore is a Synchronization Primitive , it is used For Event  Signaling  in c++20.  
->It is used when one thread needs to wait untill Another thread Says: Hey, Data id ready , Or Initialization is done.  

---

## States of Binary Semaphore

->It has two stages: 0 and  1,  

- 1 means : signal is available and Now you can use it  
- 0 means: signal is not available and you have to waait untill the it become 1.  

---

## Working

if Signal is 1 you can acquire the Critical section using  semaphore.acquire().  
and after compleing the work you   have to call the sem.release() , and it will notify the waiting thread that  

..hey i have complted my work , now you can start your's.  

---

# Use It when:

1) Need Simple Event like Signaling   
2) One thread wait for another thread to reach a point   

---

# Dont Use When:

1)You need to protect shared state  
2)The wake up depend on a predicate like "queue is not empty ", for shared predicate use condition variable   

---

# Things To keep in mind:

1)You can not Aquire the binary semaphore twice in the same thread without a release it and if you try to do it, your program will Deadlock(Hang Forever)  
