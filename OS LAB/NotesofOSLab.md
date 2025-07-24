What is fork()?

    fork() is a system call in Unix/Linux used to create a new process.

    When a process calls fork(), it creates a copy of itself (called the child process).

    After fork(), there are two processes running the same program code concurrently: the parent and the child.

Key points about fork():

    Return values of fork():

        In the parent process, fork() returns the PID (process ID) of the child (a positive integer).

        In the child process, fork() returns 0.

        If fork() fails, it returns -1 in the parent process.

    This difference in return values allows processes to know their identity:

        pid == 0 means "I am the child".

        pid > 0 means "I am the parent".

    Both processes continue execution independently from the line after the fork.

Representation of fork() in a process tree:

Example:

Initial process (PID 1000)
       |
      fork()
     /    \
Parent(1000)  Child(2000)

    Before fork(), only one process (1000).

    After fork(), two processes:

        Parent: returns child's PID (2000)

        Child: returns 0

