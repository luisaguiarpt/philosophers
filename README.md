# philosophers
A 42 project to implement a multithreaded program

In this project we must use POSIX threads to simulate the life of philosophers.

A philosopher must eat, think, sleep and repeat.
The philosophers either manage to eat a set amount of meals and the simulation ends, don't eat for too long and die, or manage to eat in a timely manner and the simulation continues indefinitely.

For this program, we must have one single process and several threads, each representing a philosopher's routine. (The bonus part of this project uses child processes to represent each of the philosophers).

