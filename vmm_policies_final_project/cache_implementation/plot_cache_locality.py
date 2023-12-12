import numpy as np
import matplotlib.pyplot as plt

# Data
fifo_l = [0.493143, 0.655714, 0.656]
random_l = [0.464857, 0.808286, 0.834286]
lfu_l = [0.681143, 0.854, 0.911143]
lru_l = [0.398286,0.769429, 0.769714]

# Number of groups and their positions
num_groups = len(fifo_l)
bar_width = 0.2
index = np.arange(num_groups)

# Creating grouped bar positions
bar_positions_fifo = index
bar_positions_random = index + bar_width
bar_positions_lfu = index + 2 * bar_width
bar_positions_lru = index + 3 * bar_width

# Plotting the grouped bars
plt.bar(bar_positions_fifo, fifo_l, bar_width, label='FIFO')
plt.bar(bar_positions_random, random_l, bar_width, label='Random')
plt.bar(bar_positions_lfu, lfu_l, bar_width, label='LFU')
plt.bar(bar_positions_lru, lru_l, bar_width, label='LRU')

# Adding labels, title, and legend

plt.xlabel('Locality')
plt.ylabel('Cache hit rate')
plt.title('Cache hit rate under memory access with low, medium and high localities')
plt.xticks(index + 1.5 * bar_width, ('Low', 'Medium', 'High'))
plt.legend()

# Show plot
plt.tight_layout()
plt.show()
