*This project has been created as part of the 42 curriculum by ldias-da*


## Description

This is the Philosophers project from the 42 School curriculum. The project implements a multi-threaded solution to the classic Dining Philosophers problem using POSIX threads and mutexes in C.
The simulation creates a configurable number of philosophers sitting around a table with forks between them. Each philosopher must alternately eat, think, and sleep while avoiding deadlock and starvation. The program demonstrates proper synchronization mechanisms and thread management.


## Instructions


#### Compilation
`make`


#### Usage:  
`./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`


#### Parameters:

* `number_of_philosophers`: Number of philosophers and forks
* `time_to_die`: Time in milliseconds before a philosopher dies if they haven't eaten
* `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
* `time_to_sleep`: Time in milliseconds a philosopher sleeps after eating
* `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops once each philosopher has eaten this many times


## Resources


#### References
* POSIX Threads Documentation: https://man7.org/linux/man-pages/man7/pthreads.7.html
* Mutex Programming: https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html
* The Dining Philosophers Problem: Classic concurrent programming problem demonstrating synchronization and deadlock prevention
* Memory Management: The project uses dynamic memory allocation for philosopher and fork structures
* Time Management: Uses gettimeofday() for precise timing measurements during simulation

#### AI Usage
AI was used to clarify specific POSIX threads behaviour, and help understand how the OS scheduler influences the behaviour of threads execution.
