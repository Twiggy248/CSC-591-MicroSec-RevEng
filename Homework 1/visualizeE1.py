import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("Exercise1_Results.csv")

# Extract the relevant columns
hits = df["Hit"]
misses = df["Miss"]
trails = df["Trial"]

# Create the figure and add scatter plots
plt.figure(figsize=(15, 12))
plt.scatter(trails, hits, label="Hits", color="blue", alpha=0.6)
plt.scatter(trails, misses, label="Misses", color="red", alpha=0.6)

# Labels and title
plt.title("Distribution of Cache Access Times (Hits vs Misses)")
plt.xlabel("Trail")
plt.ylabel("Time (ns)")
plt.legend()

# Save the figure
plt.savefig("Exercise1Graph.png", dpi=1000, bbox_inches="tight")
plt.close()
