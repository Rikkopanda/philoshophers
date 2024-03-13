
This 42 school project is about the dining philosophers problem, it is a well known problem in computer science used to illustrate common issues in concurrent programming,
that is what we are exploring with this project. We'll learn about multithreading, data races, deadlocks and more.

More elaborate explanation:
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
![Screenshot from 2024-03-13 10-07-11](https://github.com/Rikkopanda/philoshophers/assets/101322592/5d458112-06cc-43e4-8445-dfaad395c081)



Each philosopher is a thread.
Each fork is a mutex lock.
The progam will be given a set of numbers as parameters for example:
5 800 200 200 7

5 — The number of philosophers

800 — The time a philosopher will die if he doesn’t eat

200 — The time it takes a philosopher to eat

200 — The time it takes a philosopher to sleep

7 — Number of times all the philosophers need to eat before terminating the program **


Philosophers can either eat, sleep or think, there are as much forks on the table as there are philosophers and each philosopher needs
to have picked up 2 forks(lock the mutex) in order to eat. If they don't eat for a given maximum time since the last meal, they die.

Mutex locks are usually used to protect a commonly used data among theads as not read/write it at the same time and thus causing data races.
the danger of using these locks is creating deadlocks which we also want to avoid.
Below is a picture given to visualize what happens.

![20210503214018](https://github.com/Rikkopanda/philoshophers/assets/101322592/830f4b78-d0f4-4dfe-9696-5426093055cb)

The bonus part is a seperate program with the same goal, except it's now using semaphores(similar to locks) and
multiple processes instead of threads. Also conceptually now all the forks are in the middle since are 
semapore can behave as a counter that can be incremented and decremented untill zero(locked).


