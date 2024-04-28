import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Read alignment results from file
with open("bin/alignment_results.txt", "r") as file:
    lines = file.readlines()

# Extract data for each alignment
data = []
current_alignment = {}
for line in lines:
    if line.startswith("Alignment with pattern:"):
        if current_alignment:
            data.append(current_alignment)
        current_alignment = {"Pattern": line.split(": ")[1].strip()}
    elif line.startswith("Text:"):
        current_alignment["Text"] = line.split(": ")[1].strip()
    elif line.startswith("Score:"):
        current_alignment["Score"] = int(line.split(": ")[1].strip())

# Add the last alignment
if current_alignment:
    data.append(current_alignment)

# Create DataFrame
df = pd.DataFrame(data)

# Pivot DataFrame to create a matrix of scores
pivot_df = df.pivot_table(index='Pattern', columns='Text', values='Score', fill_value=0)

# Convert DataFrame values to integers
pivot_df = pivot_df.astype(int)

# Plotting heatmap using Seaborn
plt.figure(figsize=(12, 8))
sns.heatmap(pivot_df, cmap='viridis', annot=True, fmt='d', linewidths=.5)
plt.title('Alignment Scores Heatmap')
plt.xlabel('Sequence number')
plt.ylabel('Pattern')
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
