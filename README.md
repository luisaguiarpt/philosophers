# philosophers
A 42 project to implement a multithreaded program

In this project we must use POSIX threads to simulate the life of philosophers.

A philosopher must eat, think, sleep and repeat.
The philosophers either manage to eat a set amount of meals and the simulation ends, don't eat for too long and die, or manage to eat in a timely manner and the simulation continues indefinitely.

For this program, we must have one single process and several threads, each representing a philosopher's routine. (The bonus part of this project uses child processes to represent each of the philosophers).

## Concepts
#### Threads

A thread is a unit of processing that is lightweight (when compared to a fork). It uses the same memory as the thread that called it, and most of the same resources.

While this is good to save in CPU usage, it brings up several challanges when it comes to shared memory access.

We must include the `<pthread.h>` header.

To create a thread we use the function:

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, (void *)start_routine, void *arg);
```
Where `thread` is a variable that holds the id of the thread, which will be used in other functions that deal with threads.
`attr` isn't available in the scope of this project.
`start_routine` is the function on which the thread will start execution.
`arg` is a pointer to the argument used in the `start_routine` function.

To be done with a thread, we have the option to use `pthread_detach()` and `pthread_join()`.

The join function will wait for the thread to finish execution (e.g.: return), and retrieve it's return value.

The detach function is more useful when you don't care about the return value of the thread.

Both functions will clean up the resources when the thread finishes executing.

Not using any of these functions results in leaks.

#### Data race

What if you have two threads trying to access the same shared resource at the same time?

A data race occurs when two or more threads access the same memory concurrently, at least one access is a write, and there's no synchronization to prevent it.

And then there's undefined behaviour.

Maybe they both want to read a value, and everything is ok. (only ok if no one is writing)

Maybe they need to read an int and add 1 to it's value and then write it.
- They read x == 3 at the same time, add x + 1 == 4, and they both write 4.
Whereas what you really wanted was 5. This is called a **lost update**.

Maybe you're reading while someone is writing, and the value is changed mid read, so you get garbage.

These are data races, and they are preventable using mutexes.

#### Mutexes

Mutex (**Mut**ual **ex**clusion), is a sort of lock, that allows only one thread to access a piece of shared memory at a time.

I like to think of it as a lock to a door. (lock -> mutex; door -> function; room -> shared memory)

If a thread wants to access this room, the door must be unlocked to begin with, otherwise that means that someone else is inside. If that's the case, you wait (good).
This is the tricky bit, before entering the room, you must first lock the door, and only then can you access it. (The analogy falls apart a bit here, but that's ok).
Then, after you leave the room, you unlock the door again, so other people can go into it.

There is a catch, however. What if there's another door to the room?

In that case, even if the door is locked, someone may be able to enter through the other door, and uh oh, you're caught with your pants down.

That's why mutexes are good, but only if your code doesn't have any backdoors (no pun).

That's why you must make sure that to access `var x` (in shared memory), you can only do it after locking it with a `mutex_for_x`.
This isn't done automatically, you must guarantee that all access to the shared resource (doesn't matter how many doors), is guarded by the same lock (only one).

To summarize: for shared resource x, you must lock it with a mutex in order to access it. You can access it via multiple places, but they must all use the same mutex.
