*This project has been created as part of the 42 curriculum by <fatigarc>.*

# Philosophers

## Description

**Philosophers** is a 42 project designed to introduce the fundamental concepts of concurrency and synchronization in C. The core objective of this project is to understand how to properly manage and protect shared resources in a concurrent environment.

The project is based on the classical Dining Philosophers problem, which illustrates synchronization issues in concurrent systems.

In this simulation:

* A number of philosophers sit around a table.
* Each philosopher alternates between **eating**, **sleeping**, and **thinking**.
* To eat, a philosopher must take two forks (one on the left and one on the right).
* If a philosopher does not start eating within `time_to_die`, they die.
* The simulation stops when a philosopher dies.

This repository implements **only the mandatory part**, using **threads (pthreads) and mutexes**.


## Learning Objectives

* Understand how **threads (pthreads)** work.
* Manage shared resources using **mutexes**.
* Avoid **data races**.
* Avoid **deadlocks**.
* Properly manage memory (no leaks).
* Implement a simulation with precise time control.



## Classic Concurrency Problems

###  Deadlock

A **deadlock** occurs when two or more threads are permanently blocked because each one is waiting for a resource held by another.

Example in this project:
If every philosopher takes the left fork first and then waits for the right fork, it is possible that:

* Each philosopher holds one fork.
* All philosophers wait for the second fork.
* None of them can proceed.

Solution applied:
Deadlock is prevented by enforcing an **order in fork acquisition**, ensuring that not all threads lock resources in the same order.



### Race Condition (Data Race)

A **race condition** occurs when two or more threads access or modify the same variable simultaneously without proper protection (without a mutex).

This may lead to:

* Unpredictable behavior.
* Incorrect reads.
* Inconsistent states.

Solution applied:
Shared variables are protected using **mutexes**, ensuring mutual exclusion in critical sections.



## ⚙️ Compilation

Inside the `philo/` directory:

```bash
make
```

Available rules:

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

Compiled with:

```
-Wall -Wextra -Werror
```



## ▶️ Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```



## Testing & Validation

To ensure correctness, the following tools were used:

### Memory Leak Detection

```bash
valgrind --leak-check=full ./philo 5 800 200 200
```

### Data Race Detection

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

Additional testing included:

* Single philosopher (edge case).
* Very small timing values.
* Long sleeping times.
* Long-running simulations.
* Different numbers of philosophers.


## Technical Decisions

* Each philosopher is represented as an independent **thread**.
* Each fork is protected by a **mutex**.
* An additional mutex is used to protect printing to the terminal.
* Time management is implemented using `gettimeofday`.
* Deadlocks are prevented by enforcing an ordered fork acquisition strategy.
* A monitoring routine checks whether a philosopher dies.



## Resources

* The Dining Philosophers Problem – Neso Academy
* Introduction to Threads – Neso Academy
* Dining Philosophers Problem: Simplified – Zaynab Zakiyah
* What is a Mutex in C? (pthread_mutex) – CodeVault
* What are Race Conditions? – CodeVault
* Short Intro to Threads (Pthreads) – CodeVault
* Deadlocks in C – CodeVault
* Semaphores – Neso Academy



## AI Usage

AI was used for:

* Clarifying theoretical concepts such as **deadlock** and **data races**.
* Generating pseudocode for certain parts (e.g., monitoring logic).
* Generating the initial structure of this README and assisting with the translation.
* Providing ideas and examples for testing the project.

All code was fully understood, reviewed, and validated.



## Project Structure

philo/
│── Makefile
│── philo.c
│── init.c
│── parser.c
│── philo_threads.c
│── actions.c
│── utils.c

