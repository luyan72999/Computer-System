import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np



import re
import statistics


# Function to extract TLB hit rates from a text file
def extract_tlb_hit_rates(file_path):
    # Read the contents of the file
    with open(file_path, 'r') as file:
        file_contents = file.read()

    # Use regular expression to find all TLB hit rates
    tlb_hit_rate_pattern = r'TLB hit rate: (\d+\.\d+)'
    matches = re.findall(tlb_hit_rate_pattern, file_contents)

    # Check if matches are found
    if matches:
        # Convert the extracted values to floats
        tlb_hit_rates = [float(match) for match in matches]

        rates_with_20_1 = tlb_hit_rates[:10]
    
        rates_with_50_1 = tlb_hit_rates[10:20]
    
        rates_with_90_1 = tlb_hit_rates[20:30]

        if rates_with_20_1:
            average_rates_with_20_1 = statistics.mean(rates_with_20_1)
       
        if rates_with_50_1:
            average_rates_with_50_1 = statistics.mean(rates_with_50_1)

        if rates_with_90_1:
            average_rates_with_90_1 = statistics.mean(rates_with_90_1)
    

        return (average_rates_with_20_1, average_rates_with_50_1, average_rates_with_90_1)
    else:
        print("TLB hit rates not found in the file.")
        return None


def main():
#  one-level TLB and variable page size

    file_path_fifo = 'fifo_var_10entries_new.txt'
    result_fifo = extract_tlb_hit_rates(file_path_fifo)
    print("fifo: ",result_fifo)

    file_path_ran = 'ran_var_10entries_new.txt'
    result_ran = extract_tlb_hit_rates(file_path_ran)
    print("random: ",result_ran)

    file_path_lfu = 'lfu_var_10entries_new.txt'
    result_lfu = extract_tlb_hit_rates(file_path_lfu)
    print("lfu: ", result_lfu)

    file_path_lru = 'lru_var_10entries_new.txt'
    result_lru = extract_tlb_hit_rates(file_path_lru)
    print("lru: ",result_lru)
        
    policies = ("20%", "50%", "90%")
    data = {
        'FIFO': result_fifo,
        'Random': result_ran,
        'LFU': result_lfu,
        'LRU': result_lru
    }

    x = np.arange(len(policies))  # the label locations
    width = 0.2  # the width of the bars
    multiplier = 0

    fig, ax = plt.subplots(layout='constrained')

    for attribute, measurement in data.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, measurement, width, label=attribute)
        ax.bar_label(rects, padding=3)
        multiplier += 1

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_xlabel('Locality')
    ax.set_ylabel('TLB hit rate')
    ax.set_title('TLB hit rate with 4 policies (one-level TLB with 10 entries)')
    ax.set_xticks(x + width, policies)
    ax.legend(loc='upper left', ncols=3)
    ax.set_ylim(0.8, 0.95)

    plt.show()

# plt.savefig('plot.png', dpi=300)

main()