import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import seaborn as sns

df = pd.read_csv("../build-vs2019-x64/bin/Debug/image_pubsub_data.csv", engine="pyarrow")

# Plot points (aka markers in mpl) on a coordinate plane and determine best fit

fig, ax = plt.subplots()

# https://matplotlib.org/stable/tutorials/introductory/quick_start.html#parts-of-a-figure

ax.set_title('Publisher / Subscriber benchmark image (1920 x 1080)')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second

filtered = df[(np.abs(stats.zscore(df["latency"])) < 3) & (np.abs(stats.zscore(df["latency"])) > -3)]

freqs = pd.unique(filtered["frequency"])
# https://stackoverflow.com/questions/23199796/detect-and-exclude-outliers-in-a-pandas-dataframe

# latencies = []
# for freq in freqs:
#     dataFrame = filtered.loc[filtered["frequency"] == freq]
#     q_low = dataFrame["latency"].quantile(0.01)
#     q_hi  = dataFrame["latency"].quantile(0.99)
#     print(dataFrame[(dataFrame["latency"] < q_hi) & (dataFrame["latency"] > q_low)]["latency"].mean(), end = "\n\n")
#     latencies.append(dataFrame[(dataFrame["latency"] < q_hi) & (dataFrame["latency"] > q_low)]["latency"].mean())

# latencies = [filtered.loc[filtered["frequency"] == freq]["latency"].mean() for freq in freqs]

latencies = [df.loc[df["frequency"] == freq]["latency"].mean() for freq in freqs]

# plot mean line
ax.plot(freqs, latencies, linewidth=2)

# plot standard deviation line
# plt.show()

#                         height width
fig.savefig('pubsub_image.png')

print("generated the graph")