import pandas as pd
import matplotlib.pyplot as plt


# Función para graficar tiempo vs. número de puntos
def plot_time_vs_num_points(file_name, k):
    # Cargar los datos
    data = pd.read_csv(file_name)

    # Graficar
    plt.figure(figsize=(10, 5))
    plt.plot(data["num_points"], data["kmeans_time"], marker="o", label="k-means")
    plt.plot(
        data["num_points"], data["kdtree_time"], marker="o", label="k-means con kd-tree"
    )
    plt.title(f"Tiempo de ejecución vs. Número de puntos (k={k})")
    plt.xlabel("Número de puntos")
    plt.ylabel("Tiempo de ejecución (microsegundos)")
    plt.legend()
    plt.grid()
    plt.show()


# Función para graficar tiempo vs. número de k
def plot_time_vs_num_k(file_name, num_points):
    # Cargar los datos
    data = pd.read_csv(file_name)

    # Graficar
    plt.figure(figsize=(10, 5))
    plt.plot(data["num_k"], data["kmeans_time"], marker="o", label="k-means")
    plt.plot(
        data["num_k"], data["kdtree_time"], marker="o", label="k-means con kd-tree"
    )
    plt.title(f"Tiempo de ejecución vs. Número de k (puntos={num_points})")
    plt.xlabel("Número de k (centroides)")
    plt.ylabel("Tiempo de ejecución (microsegundos)")
    plt.legend()
    plt.grid()
    plt.show()


# Usar las funciones para graficar
plot_time_vs_num_points("kmeans_vs_kdtree_num_points.csv", k=5)  # Ejemplo para k=5
plot_time_vs_num_k(
    "kmeans_vs_kdtree_num_k.csv", num_points=500
)  # Ejemplo para 500 puntos
