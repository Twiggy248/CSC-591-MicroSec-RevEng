import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('_mpl-gallery')

df = pd.read_csv("../Exercise5_Results.csv")

First = df["First"]
Second = df["Second"]

fig, ax = plt.subplots(figsize=(15, 6))

# Plot the histogram of First and Second
num_bins = 25000
min_val = min(First.min(), Second.min())
max_val = max(First.max(), Second.max())
bins = np.linspace(min_val, max_val, num_bins)

ax.hist(First, bins=bins, alpha=0.6, label='Inital Operation', histtype='stepfilled', linewidth=5, color='green')
ax.hist(Second, bins=bins, alpha=0.6, label='Operation after Wait', histtype='stepfilled', linewidth=5, color='red')
ax.legend()
ax.set_xlabel('Duration in nanoseconds')
ax.set_ylabel('Frequency')
ax.set_title('Exercise Five: Timing Operations separated by 100ms')

# Focus x-axis on the region containing the majority of the data
combined = pd.concat([First, Second])
left = combined.quantile(0)
right = combined.quantile(0.99)
ax.set_xlim(left, right)

# Ensure the figure is properly aligned and sized
fig.tight_layout()

plt.savefig("Exercise5.png")