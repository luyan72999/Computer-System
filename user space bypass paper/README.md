What problems are they trying to solve?


Context switching between kernel mode and user mode can slow down applications, especially for the syscall-intensive ones. 


What is their proposed solution?

This paper proposes userspace bypass (UB). By transparently moving userspace instructions into kernel, syscall-intensive applications can be accelerated.

How did they evaluate their solution?
What were the results?

Experiments and Results

Experiment: Inplemented a prototype of UB and evaluated its performance gain in I/O micro-benchmark and real-world applications.
Result: proved UB's effectiveness (existing applications can be executed without modification and enjoy the performance gain.)
Experiment: Compared UB with other systems that optimize syscalls, including io_uring, F-Stack DPDK and eBPF.
Result: UB is less advantageous in some aspects, but it has a unique advantage of no code change is required for developers.

What future work does this suggest?
.
