Homework (Simulation)
2. 
The height of the process tree increases as fork percentage went from 0.1 to 0.9.
3. 
action 1: a forks b
action 2: a forks c
action 3: c exits
action 4: a forks d
action 5: a forks e
4.
1st try: -A a+b,b+c,c+d,c+e,c- 
2nd try: -A a+b,b+c,c+d,d+e,b- 
3rd try: -A a+b,b+c,c+d,e+p,e- 
Finding: when a parent process is killed, its children becomes the children of root process (a or init)
         so the parent process is allowed to exit before its children exit, and the children becomes independant processes under root, not a child of its grandparent

4th try: -A a+b,b+c,c+d,a-  
Finding: root process cannot exit

5.
seed: -1
  a
   |____ c
   |     |_____ e
   |_____d

seed: -2
   a
   |____ c
   |     |_____ d
   |_____e 

6.
seed: -3
actions 5
Final Process Tree: in this case there are 5 actions, thus we can tell all of them are fork() given the tree.
                               a
                               ├── b
                               │   ├── c
                               │   └── f
                               └── d
                                   └── e
seed: -4
actions 5
Final Process Tree: in this case there are 5 actions, but because there are exit() involved, we can't tell the exact actions.
For example, the following tree can be a+b,a+c,a+d,a+e,d- or a+b,a+c,c+d,d+e,d- 
                               a
                               ├── b
                               ├── c
                               └── e

  
