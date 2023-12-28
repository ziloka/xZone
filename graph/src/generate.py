import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
from scipy import stats
import seaborn as sns

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

fig, ax = plt.subplots()

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure

ax.set_title('Publisher / Subscriber benchmark image (4096 x 2160) mean values')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (ns)') # nanoseconds, a billionth of a second

def addLegend(data_filepath: str, transport: str, color: str):
    df = pd.read_csv(data_filepath, engine="pyarrow")
    freqs = pd.unique(df["frequency"])

    y = [df.loc[df["frequency"] == freq]["latency"].mean() for freq in freqs]
    plt.scatter(freqs, y, label = transport)
    err = [df.loc[df["frequency"] == freq]["latency"].std() for freq in freqs]
    # fmt='none' to prevent the lines from connecting
    ax.errorbar(freqs, y, xerr=None, yerr=err, ls='none')

addLegend("data/dev/image_4096x2160_tcp.csv", "TCP", "tab:purple")
addLegend("data/dev/image_4096x2160_udp.csv", "UDP", "tab:green")
addLegend("data/dev/image_4096x2160_sharedmem.csv", "Shared Memory", 'tab:blue')
ax.legend()

#                         height width
fig.savefig('pubsub_image.png')

print("generated the graph")