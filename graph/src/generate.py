import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("../build-vs2019-x64/bin/Debug/image_pubsub_data_176x144.csv")

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

# fig, ax = plt.subplots()  # Create a figure containing a single axes.
# ax.plot([1, 2, 3, 4], [1, 4, 2, 3])  # Plot some data on the axes.
fig, ax = plt.subplots()

ax.set_title('Publisher / Subscriber benchmark image (176 x 144)')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second
# set axis maybe
# ax.axis([])

ax.scatter(data["frequency"], data["latency"], s=50, facecolor='C0', edgecolor='k')

plt.show()

#                         height width
fig.savefig('pubsub_image_176_144.png')

print("generated the graph")