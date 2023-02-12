# Thread-and-Process-Scheduling

# 1.1 Thread Scheduling
Each of the 3 functions (countA, countB, countC) runs a loop from 1 to 2^32 and time(in seconds
and nanoseconds) for each of these functions to complete(using threads) is calculated using the
clock_gettime method.
In the main function, I have created three threads namely threadA, threadB and threadC each of
which have their sched_param parameters. Using these parameters, I have called the
“set_schedparam” methods for each of these threads which sets the respective scheduling policies
(SCHED_OTHER, SCHED_RR, SCHED_FIFO). For SCHED_RR and SCHED_FIFO I have used
the “.sched_priority” method to set the priority of each thread, which falls in the range of 1 to 99.
On running the program, we see that since SCHED_OTHER has default priority, it always takes
more time than SCHED_RR and SCHED_FIFO to complete due to starvation. SCHED_RR and
SCHED_FIFO always give similar time values .

# 1.2 Process scheduling
Here we are compiling a copy of the kernel by running a bash file using 3 processes. We create 3
child processes by running the fork() command in a loop and set the priority of the process in the
child process by using the setpriority() function. By using execvp, we start the compilation process
of the kernel as the bash file is run. After these processes are over we can find out the time taken
by each of these forked processes by using the wait command. After the wait command we can
find the final time taken for each of these processes
