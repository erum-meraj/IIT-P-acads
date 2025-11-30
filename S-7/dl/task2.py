# Assignment 1 - Task 1
# Binary Classification using KNN from scratch

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from collections import Counter
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, precision_score, recall_score, accuracy_score
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

# --------------------------
# 1. Load Dataset
# --------------------------

df = pd.read_csv("data.csv")

# Map diagnosis: M=1 (Malignant), B=0 (Benign)
df['diagnosis'] = df['diagnosis'].map({'M': 1, 'B': 0})

# Drop 'id' column and any unnamed columns
columns_to_drop = ['id']
# Also drop any unnamed columns that are just empty
unnamed_cols = [col for col in df.columns if 'Unnamed' in str(col)]
columns_to_drop.extend(unnamed_cols)

# Only drop columns that actually exist in the dataframe
columns_to_drop = [col for col in columns_to_drop if col in df.columns]
df = df.drop(columns=columns_to_drop)

print(f"Dropped columns: {columns_to_drop}")

# Debug: Check the data structure after dropping unnamed columns
print(f"DataFrame shape after dropping columns: {df.shape}")
print(f"DataFrame columns: {df.columns.tolist()}")
print(f"Missing values after dropping unnamed columns:\n{df.isnull().sum().sum()}")

# Handle missing values properly
# First, separate features and target
y = df['diagnosis'].values
X_df = df.drop(columns=['diagnosis'])

print(f"\nFeature matrix shape: {X_df.shape}")
print(f"Missing values in features: {X_df.isnull().sum().sum()}")

# Since all columns should now be numeric and clean, just convert to numpy
X = X_df.values

# Check for any remaining NaN or infinite values
nan_count = np.isnan(X).sum()
inf_count = np.isinf(X).sum()
print(f"NaN values in X: {nan_count}")
print(f"Infinite values in X: {inf_count}")

# Only filter if there are actual problematic values
if nan_count > 0 or inf_count > 0:
    finite_mask = np.isfinite(X).all(axis=1) & np.isfinite(y)
    X = X[finite_mask]
    y = y[finite_mask]
    print(f"Rows removed due to NaN/Inf: {len(finite_mask) - finite_mask.sum()}")

print(f"Final dataset shape: {X.shape}")
print(f"Class distribution: {Counter(y)}")

# Additional check - ensure we have data
if X.shape[0] == 0:
    print("ERROR: No data remaining after cleaning!")
    print("This suggests all your data contains problematic values.")
    print("Please check your CSV file format and content.")
    exit(1)

print(f"Final dataset shape: {X.shape}")
print(f"Class distribution: {Counter(y)}")

# Train-Test Split (80-20)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# --------------------------
# 2. Distance Metrics
# --------------------------
def euclidean_distance(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))

def manhattan_distance(x1, x2):
    return np.sum(np.abs(x1 - x2))

def minkowski_distance(x1, x2, p=3):
    return np.sum(np.abs(x1 - x2) ** p) ** (1 / p)

def cosine_similarity(x1, x2):
    num = np.dot(x1, x2)
    den = np.linalg.norm(x1) * np.linalg.norm(x2)
    if den == 0:
        return 0
    return 1 - (num / den)   # Convert similarity → distance

def hamming_distance(x1, x2):
    return np.mean(x1 != x2)

distance_functions = {
    "Euclidean": euclidean_distance,
    "Manhattan": manhattan_distance,
    "Minkowski": lambda x1, x2: minkowski_distance(x1, x2, p=3),
    "Cosine": cosine_similarity,
    "Hamming": hamming_distance
}

# --------------------------
# 3. KNN Classifier from Scratch
# --------------------------
class KNNClassifier:
    def __init__(self, k=3, distance_func=euclidean_distance):
        self.k = k
        self.distance_func = distance_func
    
    def fit(self, X_train, y_train):
        self.X_train = X_train
        self.y_train = y_train
    
    def predict_one(self, x):
        distances = [self.distance_func(x, x_train) for x_train in self.X_train]
        k_idx = np.argsort(distances)[:self.k]
        k_labels = [self.y_train[i] for i in k_idx]
        return Counter(k_labels).most_common(1)[0][0]
    
    def predict(self, X):
        return np.array([self.predict_one(x) for x in X])

# --------------------------
# 4. Experiment with Hyperparameters
# --------------------------
K_values = [3, 4, 9, 20, 47]
results = []

plt.figure(figsize=(12, 8))

for dist_name, dist_func in distance_functions.items():
    acc_list = []
    for k in K_values:
        model = KNNClassifier(k=k, distance_func=dist_func)
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)
        acc = accuracy_score(y_test, y_pred)
        acc_list.append(acc)
        results.append((dist_name, k, acc))
        print(f"[{dist_name}] K={k} → Accuracy={acc:.4f}")
    plt.plot(K_values, acc_list, marker='o', label=dist_name)

plt.title("KNN Accuracy vs K (Different Distance Metrics)")
plt.xlabel("K")
plt.ylabel("Accuracy")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# --------------------------
# 5. Pick Best Model
# --------------------------
best_result = max(results, key=lambda x: x[2])
best_metric, best_k, best_acc = best_result

print("\n=== BEST MODEL RESULTS ===")
print(f"Best Distance Metric : {best_metric}")
print(f"Best K               : {best_k}")
print(f"Best Accuracy        : {best_acc:.4f}")

# Train Best Model Again
best_model = KNNClassifier(k=best_k, distance_func=distance_functions[best_metric])
best_model.fit(X_train, y_train)
y_pred_best = best_model.predict(X_test)

# --------------------------
# 6. Evaluation (Expected Outcomes)
# --------------------------
cm = confusion_matrix(y_test, y_pred_best)
precision = precision_score(y_test, y_pred_best)
recall = recall_score(y_test, y_pred_best)

print("\n=== CONFUSION MATRIX ===")
print(cm)
print(f"\nPrecision: {precision:.4f}")
print(f"Recall   : {recall:.4f}")

# --------------------------
# 7. Bonus: Visualize Decision Boundary
# --------------------------
# Scale the data before PCA for better visualization
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Apply PCA
pca = PCA(n_components=2)
X_train_2d = pca.fit_transform(X_train_scaled)
X_test_2d = pca.transform(X_test_scaled)

# Train model on 2D data
best_model_2d = KNNClassifier(k=best_k, distance_func=distance_functions[best_metric])
best_model_2d.fit(X_train_2d, y_train)

# Create mesh for decision boundary
h = 0.1  # step size in the mesh
x_min, x_max = X_train_2d[:, 0].min() - 1, X_train_2d[:, 0].max() + 1
y_min, y_max = X_train_2d[:, 1].min() - 1, X_train_2d[:, 1].max() + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

# Predict on mesh
Z = best_model_2d.predict(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

# Plot decision boundary
plt.figure(figsize=(10, 8))
plt.contourf(xx, yy, Z, alpha=0.4, cmap=plt.cm.coolwarm)
plt.scatter(X_train_2d[:, 0], X_train_2d[:, 1], c=y_train, cmap=plt.cm.coolwarm, s=20, edgecolor="k")
plt.title(f"Decision Boundary (Best KNN: K={best_k}, Distance={best_metric})")
plt.xlabel(f"PC1 ({pca.explained_variance_ratio_[0]:.2%} variance)")
plt.ylabel(f"PC2 ({pca.explained_variance_ratio_[1]:.2%} variance)")
plt.colorbar()
plt.tight_layout()
plt.show()

# Show explained variance
print(f"\nPCA Explained Variance Ratio: {pca.explained_variance_ratio_}")
print(f"Total Variance Explained: {sum(pca.explained_variance_ratio_):.2%}")