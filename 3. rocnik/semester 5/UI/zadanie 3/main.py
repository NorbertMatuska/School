import random
import time
import matplotlib.pyplot as plt
import numpy as np


def generate_starting_points(num_points=20, x_range=(-5000, 5000), y_range=(-5000, 5000)):
    starting_points = set()  # set, so the points dont repeat

    while len(starting_points) < num_points:
        x = random.randint(*x_range)
        y = random.randint(*y_range)
        starting_points.add((x, y))

    return starting_points


def generate_offset_points(base_points, num_of_new_points=40000, x_range=(-5000, 5000), y_range=(-5000, 5000)):
    all_points = set(base_points)
    offset_range = (-100, 100)

    while len(all_points) < num_of_new_points + len(base_points):
        base_x, base_y = random.choice(list(all_points))

        x_offset = random.randint(max(offset_range[0], x_range[0] - base_x), min(offset_range[1], x_range[1] - base_x))
        y_offset = random.randint(max(offset_range[0], y_range[0] - base_y), min(offset_range[1], y_range[1] - base_y))

        new_point = (base_x + x_offset, base_y + y_offset)
        all_points.add(new_point)

    return list(all_points)


def evaluate_clusters(centroids, clusters):
    success_rate = 0

    for centroid, points in zip(centroids, clusters.values()):
        distances = [np.linalg.norm(np.array(point) - np.array(centroid)) for point in points]
        average_distance = np.mean(distances)

        if average_distance <= 500:
            success_rate += 1

    success_percentage = (success_rate / len(clusters)) * 100
    return success_percentage


def k_means(points, k=10, max_iterations=100):
    # initialize centroids
    centroids = random.sample(points, k)
    clusters = None

    for _ in range(max_iterations):
        # assign points to the nearest centroid
        clusters = {i: [] for i in range(k)}
        for point in points:
            distances = [np.linalg.norm(np.array(point) - np.array(centroid)) for centroid in centroids]
            min_distance_idx = distances.index(min(distances))
            clusters[min_distance_idx].append(point)

        # update centroids
        new_centroids = []
        for idx in range(k):
            cluster_points = clusters[idx]
            new_centroid = np.mean(cluster_points, axis=0)
            new_centroids.append(new_centroid)

        # check for convergence (if centroids don't change)
        if all([np.array_equal(new_centroids[i], centroids[i]) for i in range(k)]):
            break

        centroids = new_centroids

    return centroids, clusters


def k_means_medoids(points, k=10, max_iterations=100):
    # initialize medoids
    medoids = random.sample(points, k)
    clusters = None

    for _ in range(max_iterations):
        # assign points to the nearest medoid
        clusters = {i: [] for i in range(k)}
        for point in points:
            distances = [np.linalg.norm(np.array(point) - np.array(medoid)) for medoid in medoids]
            min_distance_idx = distances.index(min(distances))
            clusters[min_distance_idx].append(point)

        # update medoids
        new_medoids = []
        for idx in range(k):
            cluster_points = clusters[idx]
            # find the point in the cluster that minimizes the sum of distances to all other points in the cluster
            medoid = min(cluster_points, key=lambda p: sum(np.linalg.norm(np.array(p) - np.array(other)) for other in
                                                           cluster_points))
            new_medoids.append(medoid)

        # check for convergence (if medoids don't change)
        if all([medoids[i] == new_medoids[i] for i in range(k)]):
            break

        medoids = new_medoids

    return medoids, clusters


def divisive_clustering(points, max_clusters=10):
    clusters = {0: points}
    centroids = [np.mean(points, axis=0)]

    while len(clusters) < max_clusters:
        # find the largest cluster
        largest_cluster_id = max(clusters, key=lambda k: len(clusters[k]))
        largest_cluster = clusters.pop(largest_cluster_id)
        cluster_centroid = np.mean(largest_cluster, axis=0)

        # choose seed points
        farthest_point = max(largest_cluster, key=lambda p: np.linalg.norm(np.array(p) - cluster_centroid))
        second_farthest_point = max(largest_cluster, key=lambda p: np.linalg.norm(np.array(p) -
                                                                                  np.array(farthest_point)))

        # initial split
        new_clusters = {0: [], 1: []}
        for point in largest_cluster:
            distances = [np.linalg.norm(np.array(point) - np.array(seed)) for seed in [farthest_point,
                                                                                       second_farthest_point]]
            closest_cluster = distances.index(min(distances))
            new_clusters[closest_cluster].append(point)

        # refine clusters
        for _ in range(50):  # number of iterations for refinement
            new_centroids = [np.mean(new_clusters[i], axis=0) for i in new_clusters]
            stable = True

            for i in new_clusters:
                updated_cluster = []
                for point in new_clusters[i]:
                    distances = [np.linalg.norm(np.array(point) - np.array(centroid)) for centroid in new_centroids]
                    closest_cluster = distances.index(min(distances))
                    if closest_cluster != i:
                        stable = False
                    updated_cluster.append(point)
                new_clusters[i] = updated_cluster

            if stable:
                break

        # add new clusters
        cluster_ids = list(range(len(centroids), len(centroids) + 2))
        for new_id, cluster_points in zip(cluster_ids, new_clusters.values()):
            if len(centroids) < max_clusters - 1:  # Adjust the condition to account for two new centroids
                clusters[new_id] = cluster_points
                centroids.append(np.mean(cluster_points, axis=0))
            elif len(centroids) < max_clusters:
                # if adding both centroids would exceed the limit, only add one
                clusters[new_id] = cluster_points
                centroids.append(np.mean(cluster_points, axis=0))
                return centroids, clusters
    return centroids, clusters


def visualize_cluster(centroids, clusters):
    cmap = plt.get_cmap('tab20')  # 'tab20' has 20 distinct colors

    plt.figure(figsize=(10, 10))

    # Generate the plot for each cluster using a color from the colormap
    for i, cluster in clusters.items():
        # Separate the points into x and y lists
        xs, ys = zip(*cluster)
        color = cmap(i % cmap.N)  # Use modulo to cycle through the colormap if necessary
        plt.scatter(xs, ys, c=[color], label=f'Cluster {i}', alpha=0.6)

    # Plot centroids
    cent_xs, cent_ys = zip(*centroids)
    plt.scatter(cent_xs, cent_ys, c='k', marker='x', s=100, label='Centroids')

    plt.title('Cluster Visualization')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.legend()
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    # Generate 40k points
    start_time = time.time()
    fin_points = generate_offset_points(generate_starting_points())
    end_time = time.time()
    exec_time = end_time - start_time
    print(f"Execution time generating 40k points: {exec_time}s")
    print()

    # k-means with centroid as center
    start_time = time.time()
    k_centroids, k_clusters = k_means(fin_points)
    end_time = time.time()
    exec_time = end_time - start_time
    print(f"Execution time k-means(Centroid as center): {exec_time}s")
    print(f"Success rate k-means(Centroid as center): {evaluate_clusters(k_centroids, k_clusters)}%")
    visualize_cluster(k_centroids, k_clusters)
    print()

    # Divisive clustering with centroid as center
    start_time = time.time()
    div_centroids, div_clusters = divisive_clustering(fin_points)
    end_time = time.time()
    exec_time = end_time - start_time
    print(f"Execution time k-means(Centroid as center): {exec_time}s")
    print(f"Success rate k-means(Centroid as center): {evaluate_clusters(div_centroids, div_clusters)}%")
    visualize_cluster(div_centroids, div_clusters)
    print()

    # k-means clustering with medoid as center
    start_time = time.time()
    k_medoids, k_clusters = k_means_medoids(fin_points)
    end_time = time.time()
    exec_time = end_time - start_time
    print(f"Execution time k-means(Medoid as center): {exec_time}s")
    print(f"Succes rate k-means(Medoid as center): {evaluate_clusters(k_medoids, k_clusters)}%")
    visualize_cluster(k_medoids, k_clusters)
    print()
