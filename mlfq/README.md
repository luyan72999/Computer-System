This simulator employs a round-robin scheduling policy with multilevel feedback queues. \n
4 of 5 rules in text book are implemented:
Rule 1: If Priority(A) > Priority(B) run A.
Rule 2: If Priority(A) == Priority(B), run them in Round-Robin.
Rule 3: When a job enters the system, it is placed at the highest priority.
Rule 5: After some time period S, move all of the jobs in the system to the topmost queue.

How to play with cpu scheduler simulator
You can adjust the parameters of the queues and running processes by reading the following instructions.

Note: this simulator have 3 drawbacks and will be improved soon:
(1) cannot specify job start time, which means it can only assume all processes enter the same time
(2) cannot simulate io
(3) the bottom queue still have the method demote() so when creating the bottom queue, so its allotment must be specified a very big number.

How to tune queues:
From line 135-144, queues are created with allotment, quantum, level, and its container mlfq, you can use your own values to tune the queues.
Syntax: Queue(allotment, quantum, level, mlfq)
Here you can create as many queues you want, but the top queue should be called q0 have have level 0.
e.g Queue* q0 = new Queue(your number,your number, 0, mlfq);
And the other queues have levels 1,2,3,4....
Note the bottom queue must have a very long allotment:
e.g. Queue* q4 = new Queue(10000000,your number, your number,mlfq);

How to add processes: 
From line 146-159, processes are created with pid and length:
Syntax : Process(pid,p_length)
Here you can add, reduce the number of processes, and specify your own pid and length of process.

Adjust VOO-DOO (boost) time:
You can modify the VOO_DOO constant at line 8.

After specifying all your paramenters above, you can just compile and run, every process and its final completion time, response time will be printed.
