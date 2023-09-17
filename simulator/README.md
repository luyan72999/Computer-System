Homework(Simulation) P12    -   Lu Yan

1. 100% of time cpu is used.
   Reason: 2 processes are created, each with 5 instructions with 100% chance of using cpu. There is no io events happening, so cpu doesn't wait.

2. It takes 10s to complete both processes. The OS first used cpu to compute 4 instructions in process 0, then switched to process 1 to do io.
   The io event takes 4s, so the cpu waited for 4s.

3. The time to complete both processes reduced to 6s. The switching of order matters because the code below indicates that
   the OS starts with the 0th process in the process list, so the process with io starts first. While waiting for io, the cpu switch to the other process to do compute,
   as the switch option is by default SWITCH_ON_IO
   220 self.curr_proc = 0
   221 self.move_to_running(STATE_READY)

4. The cpu waits for 4s when process 0 is doing io, according to its switching behavior. The time for completing both processes are 9s.
5. The time for completing both processes reduced to 6s. The CPU switches to another while one is waiting for IO.
6. The cpu switches to the next process while the 0th process is doing the first io, after the first io finishes, the cpu moves to the rest of processes in process list.
   System resources are not effectively used.
7. All the waiting time of 3 io events are not wasted.
   Resuming the process once it completes an io might be a good idea because it is more likely to be an io intensive process compared to others.
   It is better to check and start other IOs as soon.
8. IO_RUN_IMMEDIATE and IO_RUN_LATER do not see an significant difference in the overhead of completing 2 processes.
   SWITCH_ON_IO has shorter overhead of completing 2 processes than SWITCH_ON_END most of the time.
