import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import seaborn as sns

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

fig, ax = plt.subplots()

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure

ax.set_title('Publisher / Subscriber benchmark image (1920 x 1080)')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second

def addLegend(df: pd.DataFrame, ax: plt.Axes, data_filepath: str, platform: str):
    df = pd.read_csv(data_filepath, engine="pyarrow")
    freqs = pd.unique(df["frequency"])
    latencies = [df.loc[df["frequency"] == freq]["latency"].mean() for freq in freqs]
    ax.plot(freqs, latencies, label=platform)

addLegend(pd.DataFrame(), ax, "jetson_agx_orin_dev_kit_1920_1080_image_pubsub_data.csv", "NVIDIA Jetson AGX Orin Developer Kit")
addLegend(pd.DataFrame(), ax, "personal_pc_psd_UPDATED.csv", "Personal PC")

ax.legend()

#                         height width
fig.savefig('pubsub_plot.png')

print("generated the graph")