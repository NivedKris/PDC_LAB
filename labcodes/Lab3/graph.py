import numpy as np
import matplotlib.pyplot as plt

N_values = np.array([100, 1000, 10000, 100000])
serial_times = np.array([0.002200, 0.012000, 0.102800, 0.802800])
parallel_times = np.array([0.002200, 0.020600, 0.157600, 1.510400])

# Set the width of the bars
bar_width = 0.35

# Create an array with the x positions for the bars
x = np.arange(len(N_values))

# Create the bar graph
plt.bar(x, serial_times, width=bar_width, label='Serial', alpha=0.7)
plt.bar(x + bar_width, parallel_times, width=bar_width, label='Parallel', alpha=0.7)

# Set the x-axis labels
plt.xlabel('N Values')
plt.xticks(x + bar_width/2, N_values)

# Set the y-axis label
plt.ylabel('Execution Time (seconds)')

# Set the title for the graph
plt.title('Serial vs Parallel Execution Times')

# Add a legend
plt.legend()

# Show the plot
plt.show()
