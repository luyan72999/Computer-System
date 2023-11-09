import random

# q3: generate a trace
addrTrace = []
counter = 0
while (counter < 20):
    addr = random.randint(1,20)
    addrTrace.append(addr)
    counter += 1

print(addrTrace)

# q4: generate a trace with some locality
addrTrace_two = []

for i in range(5):
    r = random.randint(1,20)
    addrTrace_two.append(r)

for i in range(5):
    r = random.randint(5,5)
    addrTrace_two.append(r)

for i in range(5):
    r = random.randint(1,20)
    addrTrace_two.append(r)

for i in range(5):
    r = random.randint(10,10)
    addrTrace_two.append(r)

for i in range(5):
    r = random.randint(1,20)
    addrTrace_two.append(r)

print(addrTrace_two)

