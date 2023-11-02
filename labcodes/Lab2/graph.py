import matplotlib.pyplot as plt

N_values = [100, 1000, 10000]
serial_times = [0.001000, 0.012000, 0.142000] # Replace with your actual serial execution times
parallel_times = [0.165000, 1.265000, 9.869000]

# Set the width of the bars
bar_width = 0.35

# Create an array with the x positions for the bars
x = range(len(N_values))

# Create the bar graph
plt.bar(x, serial_times, width=bar_width, label='Serial', alpha=0.7)
plt.bar([i + bar_width for i in x], parallel_times, width=bar_width, label='Parallel', alpha=0.7)

# Set the x-axis labels
plt.xlabel('N Values')
plt.xticks([i + bar_width/2 for i in x], N_values)

# Set the y-axis label
plt.ylabel('Execution Time (seconds)')

# Set the title for the graph
plt.title('Serial vs Parallel Execution Times')

# Add a legend
plt.legend()

# Show the plot
plt.show()
