import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('_mpl-gallery')

df = pd.read_csv("../Datasets/Exercise1_Results.csv")

hits = df["Hit"]
misses = df["Miss"]

fig, ax = plt.subplots(figsize=(15, 6))

# Plot the histogram of hits and misses
num_bins = 25000
min_val = min(hits.min(), misses.min())
max_val = max(hits.max(), misses.max())
bins = np.linspace(min_val, max_val, num_bins)

ax.hist(hits, bins=bins, alpha=0.6, label='Hits', histtype='stepfilled', linewidth=1, color='green')
ax.hist(misses, bins=bins, alpha=0.6, label='Misses', histtype='stepfilled', linewidth=1, color='red')
ax.legend()
ax.set_xlabel('Duration in nanoseconds')
ax.set_ylabel('Frequency')
ax.set_title('Exercise One: Distribution of Cache Hits and Misses')

# Focus x-axis on the region containing the majority of the data
combined = pd.concat([hits, misses])
left = combined.quantile(0)
right = combined.quantile(0.99)
ax.set_xlim(left, right)

# Ensure the figure is properly aligned and sized
fig.tight_layout()

plt.savefig("Exercise1.png")