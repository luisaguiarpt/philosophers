# philosophers
A 42 project to implement a multithreaded program

In this project we must use POSIX threads to simulate the life of philosophers.

A philosopher must eat, think, sleep and repeat.
The philosophers either manage to eat a set amount of meals and the simulation ends, don't eat for too long and die, or manage to eat in a timely manner and the simulation continues indefinitely.

For this program, we must have one single process and several threads, each representing a philosopher's routine. (The bonus part of this project uses child processes to represent each of the philosophers).

## Concepts
* Mutexes

Mutex (**Mut**ual **ex**clusion), is a sort of lock, that allows only one thread to access a piece of shared at a time.

I like to think of it as a lock to a door. (lock -> mutex; door -> function; room -> shared memory)

If a thread wants to access this room, the door must be unlocked, and once it goes into the room, it has to lock it, until it's done with it, leaving it as it was, unlocked.

There is a catch, however. What if there's another door to the room?

In that case, even if the door is locked, someone may be able to enter through the other door, and uh oh, you're caught with your pants down.

That's why mutexes are good, but only if your code doesn't have any backdoors (no pun).

That's why: `var x` (in shared memory) is accessible only after locking it with a `mutex_for_x`.
