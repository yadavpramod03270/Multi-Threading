# Counting Semaphore

1) In Counting Semaphore there are multiple signals instead of only one signal like Binary Semaphore.  

2) But in Counting semaphore it has multiple identical keys , like if you have 5 keys so at the time 5 thread can perform their work  Symultaneously.  

3) The Signal value can be 1 2 3 ........N, this is the big defference between binary and counting , it doesnt say "available " or "block".  

4) we were use binary semaphore to protect critical section but use counting semaphore to manage the pool of things (like : 4 database connection or 10 parking lot)  

---

# Real World Analogy:

Suppose we have a coffee shop and their capacity is for 5 table ,  

So at a time only 5 people can enter in the shop  for coffee ,  
and other people have to wait untill the table free.  

So counter start with 5, and each time when a person sit (acquire()) the counter will decrease and if the counter hit 0,  
then new costomers must have to wait, and if any person leave (release()) And then counter goes up , and next person in queue can take sit.   
