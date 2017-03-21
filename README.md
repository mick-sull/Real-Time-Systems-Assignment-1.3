# Real-Time-Systems-Assignment-1.3

For the assignment 1.3 of Real Time System we have to create a startup process that will fork four
processes. The startup process forks each of the child process to initiate them. This is a diagram
showing the processes. When startup forks the four process it will save the PID of each processes
fork. Once all processes are forked, P1 will send a signal to P2, P2 will then send a signal to P3, P3
will send a signal to P4. P4 will then send a signal to P1, P2 and P3. Each process has access to he
memory created in the startup containing all the PID of the process. This is used to send the signals
to each process.
