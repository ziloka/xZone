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

ax.set_title('Publisher / Subscriber benchmark image (1920 x 1080) mean values')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel('Latency (μs)') # microseconds, a millionth of a second

def addLegend(data_filepath: str, transport: str, color: str):
    df = pd.read_csv(data_filepath, engine="pyarrow")
    df = df.reset_index(drop=True)
    # print(df)

    Q1 = df.quantile(0.25)
    Q3 = df.quantile(0.75)
    IQR = Q3 - Q1

    # freqs = []
    # for freq in pd.unique(df["frequency"]):
    #     arr = df.loc[df["frequency"] == freq]

    #     # print(type(arr))

    #     # remove outliers
    #     Q1 = arr['latency'].quantile(0.25)
    #     Q3 = arr['latency'].quantile(0.75)
    #     IQR = Q3 - Q1
    #     lower = Q1 - 1.5*IQR
    #     upper = Q3 + 1.5*IQR

    #     # print(np.where(arr['latency'] >= upper))
    #     # ~~Create arrays of Boolean values indicating the outlier rows~~
    #     # Return the indices of the elements that are non-zero.
    #     upper_array = arr.index[arr['latency'] >= upper].tolist()
    #     lower_array = arr.index[arr['latency'] <= lower].tolist()
    #     # upper_array = np.where(arr['latency'] >= upper)[0]
    #     # lower_array = np.where(arr['latency'] <= lower)[0]
    #     # print(upper_array)
    #     # print(arr['latency'])
        
    #     # Removing the outliers
        
    #     # print(arr)
    #     # # print(type(arr))
    #     df.drop(index=upper_array, inplace=True)
    #     df.drop(index=lower_array, inplace=True)

    #     # print([freq] * len(arr))
    #     # freqs.extend([freq] * len(arr))
    #     # y.extend(arr)

    freqs = pd.unique(df["frequency"])
    # print(len(freqs))
    # print(len(df["latency"]))
    # print(len(y))
    y = [df.loc[df["frequency"] == freq]["latency"].mean() for freq in freqs]
    plt.scatter(freqs, y, label = transport)
    err = [df.loc[df["frequency"] == freq]["latency"].std() for freq in freqs]
    # fmt='none' to prevent the lines from connecting
    ax.errorbar(freqs, y, xerr=None, yerr=err, ls='none')
addLegend("image_pubsub_data.csv", "TCP", "tab:purple")

# addLegend("pc_tcp_1920_1080_image.csv", "TCP", "tab:purple")
# addLegend("pc_udp_1920_1080_image.csv", "UDP", "tab:green")
# addLegend("pc_shared-mem_1920_1080_image.csv", "Shared Memory", 'tab:blue')
ax.legend()

#                         height width
fig.savefig('pubsub_image.png')

print("generated the graph")
