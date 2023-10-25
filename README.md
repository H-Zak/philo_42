
# Philosopher

Just a quick resume of the subject (You will found the subject pdf just after):

**Objective :** don't let the philosophers die

- each philosopher is a thread, and each fork is a mutex
- they do in order: eat - sleep - think (they don't really think, they wait until they have their forks to eat)
- to eat, they must have two forks, knowing that there's only one fork per philosopher
- if one of them dies, the simulation stops and death must be displayed within 10 milliseconds at most
- write each change of philosopher status

**./philo arg1 arg2 arg3 arg4 arg5**

**arg1 =** number_of_philosophers (number of philosophers and number of forks)

**arg2 =** time_to_die (if he hasn't eaten for time_to_die milliseconds he dies)

**arg3 =** time_to_eat (time to eat with two forks in milliseconds)

**arg4 =** time_to_sleep (time to sleep in milliseconds)

**arg5 =** number_of_times_each_philosopher_must_eat (number of times each philosopher must eat, arg optional)



## Subject 

[Subject](https://cdn.intra.42.fr/pdf/pdf/103389/en.subject.pdf)


## Run Locally

Clone the project

```bash
  git clone https://github.com/Zheylkoss/philo_42.git
```

Go to the project directory

```bash
  cd philo_42
```

Launch it 

```bash
  make && ./philo [number_of_philosophers] [time_to_die (in milliseconds)] [time_to_eat (in milliseconds)] [time_to_sleep (in milliseconds)] [number_of_times_each_philosopher_must_eat (optional argument)]
```


##  Tests exemple

| Test |  expected result |
|-----------|-----------|
| ./philo 1 200 200 200  | philo 1 only takes a fork and dies after 200 ms   |
|./philo 2 800 200 200   | nobody dies   |
| ./philo 5 800 200 200 | nobody dies  |
| ./philo 5 800 200 200 7   | simulation stops when each philo has eaten 7 times   |
| ./philo 4 410 200 200   | nobody dies  |
| ./philo 4 310 200 200   | one philo dies   |
|./philo 4 500 200 1.2   | invalid argument   |
| ./philo 4 0 200 200   | invalid argument   |
| ./philo 4 -500 200 200  | invalid argument   |
| ./philo 4 500 200 2147483647  | a philo dies after 500 ms  |
| ./philo 4 2147483647 200 200  |nobody dies  |
| ./philo 4 214748364732 200 200  | invalid argument  |
| ./philo 4 200 210 200  | a philo dies, death must be displayed before 210 ms |


