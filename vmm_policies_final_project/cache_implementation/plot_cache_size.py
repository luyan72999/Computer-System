import numpy as np
import matplotlib.pyplot as plt

# Data
fifo_s = [0, 0, 0.99]
random_s = [0.174545, 0.812727, 0.99]
lfu_s = [0, 0, 0.99]
lru_s = [0, 0, 0.99]

# Number of groups and their positions
num_groups = len(fifo_s)
bar_width = 0.2
index = np.arange(num_groups)

# Creating grouped bar positions
bar_positions_fifo = index
bar_positions_random = index + bar_width
bar_positions_lfu = index + 2 * bar_width
bar_positions_lru = index + 3 * bar_width

# Plotting the grouped bars
plt.bar(bar_positions_fifo, fifo_s, bar_width, label='FIFO')
plt.bar(bar_positions_random, random_s, bar_width, label='Random')
plt.bar(bar_positions_lfu, lfu_s, bar_width, label='LFU')
plt.bar(bar_positions_lru, lru_s, bar_width, label='LRU')

# Adding labels, title, and legend

plt.xlabel('Cache sizes')
plt.ylabel('Cache hit rate')
plt.title('Cache hit rate under memory access with low, medium and high localities')
plt.xticks(index + 1.5 * bar_width, ('size 5', 'size 10 (worst/corner case)', 'size 11 (best case)'))
plt.legend()

# Show plot
plt.tight_layout()
plt.show()


#  fifo_l = [0.493143, 0.655714, 0.656]
#     random_l = [0.464857, 0.808286, 0.834286]
#     lfu_l = [0.681143, 0.854, 0.911143]
#     lru_l = [0.398286,0.769429, 0.769714]