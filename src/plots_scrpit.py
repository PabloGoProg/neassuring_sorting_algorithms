import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Read the data
bubble_times = pd.read_csv('./results/bubble_time.csv', header=None)
quick_times = pd.read_csv('./results/quick_time.csv', header=None)

# Creates the n-sizes array
data_sizes = np.array([100, 1000, 10000, 100000, 1000000, 10000000])

# Get mean time for every set of data
bubble_mean_times = [ np.mean(meassure) for meassure in bubble_times.values ]
quick_mean_times = [ np.mean(meassure) for meassure in quick_times.values ]

# Plot Bubble Sort data with a connecting line
plt.plot(data_sizes, bubble_mean_times, label='Bubble sort', color='red', marker='o', linestyle='-', linewidth=2)
plt.scatter(data_sizes, bubble_mean_times, color='red', marker='o')
plt.title('Bubble Sort Performance Analysis')
plt.xlabel('Input Size (n)')
plt.ylabel('Mean Time (s)')
plt.xscale('log')  # Use logarithmic scale for better visualization
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.savefig('./plots/bubble_plot.png')

plt.clf()

# Plot Quick Sort data with a connecting line
plt.plot(data_sizes, quick_mean_times, label='Quick sort', color='blue', marker='o', linestyle='-', linewidth=1)
plt.scatter(data_sizes, quick_mean_times, color='blue', marker='o')
plt.title('Quick Sort Performance Analysis')
plt.xlabel('Input Size (n)')
plt.ylabel('Mean Time (s)')
plt.xscale('log')  # Use logarithmic scale for better visualization
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.savefig('./plots/quick_plot.png')

plt.clf()

# Plot both data in the same graph
plt.plot(data_sizes, bubble_mean_times, label='Bubble sort', color='red', marker='o', linestyle='-', linewidth=1)
plt.scatter(data_sizes, bubble_mean_times, color='red', marker='o')
plt.plot(data_sizes, quick_mean_times, label='Quick sort', color='blue', marker='o', linestyle='-', linewidth=1)
plt.scatter(data_sizes, quick_mean_times, color='blue', marker='o')
plt.title('Bubble and Quick Sort Performance Analysis')
plt.xlabel('Input Size (n)')
plt.ylabel('Mean Time (s)')
plt.xscale('log')  # Use logarithmic scale for better visualization
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.savefig('./plots/bubble_quick_plot.png')

plt.clf()




