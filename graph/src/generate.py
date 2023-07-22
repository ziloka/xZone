import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("../build-vs2019-x64/bin/Debug/data.csv")

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

# fig, ax = plt.subplots()  # Create a figure containing a single axes.
# ax.plot([1, 2, 3, 4], [1, 4, 2, 3])  # Plot some data on the axes.
fig, ax = plt.subplots()

ax.set_title('Publisher / Subscriber benchmark')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second
# set axis maybe
# ax.axis([])

ax.scatter(data["frequency"], data["latency"], s=50, facecolor='C0', edgecolor='k')

plt.show()

fig.savefig('pubsub_benchmark.png')

print("generated the graph")