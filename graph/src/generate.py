import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

fig, ax = plt.subplots()

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure

ax.set_title('Publisher / Subscriber benchmark image (1920 x 1080) mean values')
# ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second

def getLatencies(data_filepath: str):
    return pd.read_csv(data_filepath, engine="pyarrow")["latency"]

transports = ["Shared Memory", "TCP", "UDP"]
latencies = [getLatencies("jetson_agx_xavier_shared-mem_1920_1080_image.csv").mean(), getLatencies("jetson_agx_xavier_tcp_1920_1080_image.csv").mean(), getLatencies("jetson_agx_xavier_udp_1920_1080_image.csv").mean()]
# addLegend(ax, "jetson_agx_xavier_shared-mem_1920_1080_image.csv", "Shared Memory")
# addLegend(ax, "jetson_agx_xavier_tcp_1920_1080_image.csv", "TCP")
# addLegend(ax, "jetson_agx_xavier_udp_1920_1080_image.csv", "UDP")
bar_labels = ['Shared Memory', 'TCP', 'UDP']
bar_colors = ['tab:red', 'tab:blue', 'tab:orange']
ax.bar(transports, latencies, label=bar_labels, color=bar_colors)

ax.legend()

#                         height width
fig.savefig('pubsub_image.png')

print("generated the graph")