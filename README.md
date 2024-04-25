<div align='center'> <h1>Philosophers</h1> </div>
<p align='center'>I never thought philosophy would be so deadly</p>
<p align='center'>Dining philosophers problem's solution for 42 cursus project</p>

## <h1 align='center'>Index</h1>
1. [General idea](#General_idea)
2. [Race Conditions and Mutexes](#RaceConditions&mutexes)
	- [Race Condition](#RaceConditions)
	- [Mutexes](#Mutexes)
3. [Step to Step Guide](#Guide)
	- [Step 1: Checking the input](#step1)
	- [Step 2: Creating the structures](#step2)
	- [Step 3: Initialization and allocation](#step3)
	- [Step 4: Structuring the philo's routine, the supervisor and the monitor](#step4)
	- [Step 5: Clearing the memory](#step5)
4. [Utils Functions](#utilsfunc)
	- [clear data](#clear_data)
	- [ft_exit](#ft_exit)
	- [error](#error)
	- [get time](#get_time)
	- [ft usleep](#ft_usleep)


<div align='center'><h1><a name='General_idea'>General idea</a></h1></div>
The mandatory part of this project asks us to solve the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and implement a multithreading solution. To better understand the solution, it's recommended to read about threads and multithreading. Another recommendation is to read the subject before starting the project. Now, let's dive into the general idea applied in this project.

Imagine a round table with 'N' philosophers sitting around it, each bringing a fork and placing it to their right. Each philosopher can perform three actions: eat, think, or sleep. However, to eat, a philosopher must pick up two adjacent forks. The challenge lies in organizing the eating actions of the philosophers without hardcoding them to eat separately. Instead, philosophers must organize themselves using mutexes.

<div align='center'><h1><a name='RaceConditions&mutexes'>Race Conditions & Mutex</a></h1></div>

<h3><a name='RaceConditions'>Race conditions</a></h3>
A [race condition](https://stackoverflow.com/questions/34510/what-is-a-race-condition) occurs when one or more threads try to access and modify the same variable simultaneously, potentially leading to errors in the final value of that variable. Let's illustrate this with an example:

```c
#include <pthread.h>
#include <stdio.h>

int cont = 0;

void *routine()
{
  int i;
  for (i = 0; i < 1000000; i++)
      cont++;
  return NULL;
}

int main()
{
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, &routine, NULL);
  pthread_create(&tid2, NULL, &routine, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("cont: %d\n", cont);
}
In this example, two threads increment a variable cont by 1,000,000. However, due to race conditions, the final value of cont may not be 2,000,000 as expected.

<h3><a name='Mutexes'>Mutexes</a></h3>
Mutexes are locks used to prevent data racing. When a mutex is locked, any thread attempting to lock it will be paused until the mutex is unlocked. In the above example, we could prevent the race condition by adding a lock before incrementing the variable.
c
Copy code
#include <pthread.h>
#include <stdio.h>

int cont = 0;
pthread_mutex_t lock;

void *routine()
{
  int i;
  for (i = 0; i < 1000000; i++) {
    pthread_mutex_lock(&lock);
    cont++;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main()
{
  pthread_t tid1, tid2;

  pthread_mutex_init(&lock, NULL);
  pthread_create(&tid1, NULL, &routine, NULL);
  pthread_create(&tid2, NULL, &routine, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_mutex_destroy(&lock);
  printf("cont: %d\n", cont);
}
```
Remember to initialize and destroy mutexes properly using pthread_mutex_init and pthread_mutex_destroy.

<div align='center'><h1><a name='guide'>Step to step guide</a></h1></div>
<h3><a name='step1'>Step 1: Checking the input</a></h3>
Validate the input parameters, ensuring they are within acceptable ranges.
<h3><a name='step2'>Step 2: Creating the structures</a></h3>
Define structures for storing general data and philosopher-specific data. Make sure to include a pointer to the general data structure within the philosopher structure.
<h3><a name='step3'>Step 3: Initialization and allocation</a></h3>
Allocate memory for the structures, initialize mutexes, and start threads.
<h3><a name='step4'>Step 4: Structuring the philo's routine, the supervisor and the monitor</a></h3>
Structure the philosopher's routine, supervisor, and monitor threads. Ensure synchronization using mutexes and proper handling of conditions like eating, sleeping, and thinking.
<h3><a name='step5'>Step 5: Clearing the memory</a></h3>
Clean up by joining threads, destroying mutexes, and freeing allocated memory.
<div align='center'><h3><a name='utilsfunc'>Utils Functions</a></h3></div>
Here are some utility functions you might need for the project:
<ul>
<li><h3><a name='clear_data'>clear_data</a></h3></li>
Function to clear all allocated memory.
<li><h3><a name='ft_exit'>ft_exit</a></h3></li>
Function to exit the program, clearing all resources.
<li><h3><a name='error'>error</a></h3></li>
Function to handle errors and exit the program.
<li><h3><a name='get_time'>get_time</a></h3></li>
Function to get the current time in milliseconds.
<li><h3><a name='ft_usleep'>ft_usleep</a></h3></li>
Reimplementation of the `usleep` function for more precise timing.
</ul>
