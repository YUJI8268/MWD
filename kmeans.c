#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100
#define MAX_CLUSTERS 10

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point centroid;
    int num_points;
    Point points[MAX_POINTS];
} Cluster;

double euclidean_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void initialize_clusters(Cluster clusters[], Point points[], int k, int num_points) {
    for (int i = 0; i < k; i++) {
        clusters[i].centroid = points[rand() % num_points]; // Randomly initialize centroids
        clusters[i].num_points = 0;
    }
}

void assign_points_to_clusters(Cluster clusters[], Point points[], int k, int num_points) {
    for (int i = 0; i < num_points; i++) {
        double min_distance = INFINITY;
        int cluster_index = 0;
        
        for (int j = 0; j < k; j++) {
            double distance = euclidean_distance(points[i], clusters[j].centroid);
            if (distance < min_distance) {
                min_distance = distance;
                cluster_index = j;
            }
        }
        
        clusters[cluster_index].points[clusters[cluster_index].num_points++] = points[i];
    }
}

void update_centroids(Cluster clusters[], int k) {
    for (int i = 0; i < k; i++) {
        if (clusters[i].num_points == 0) continue; // Avoid division by zero
        
        double sum_x = 0.0, sum_y = 0.0;
        
        for (int j = 0; j < clusters[i].num_points; j++) {
            sum_x += clusters[i].points[j].x;
            sum_y += clusters[i].points[j].y;
        }
        
        clusters[i].centroid.x = sum_x / clusters[i].num_points;
        clusters[i].centroid.y = sum_y / clusters[i].num_points;
    }
}

int main() {
    int k = 3; // Number of clusters
    Point points[MAX_POINTS] = {
        {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
        {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0},
        {8.0, 2.0}, {10.0, 2.0}, {9.0, 3.0}
    };
    int num_points = 9;
    
    Cluster clusters[MAX_CLUSTERS];
    
    initialize_clusters(clusters, points, k, num_points);
    
    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < k; i++) {
            clusters[i].num_points = 0; // Reset point count for each iteration
        }
        
        assign_points_to_clusters(clusters, points, k, num_points);
        update_centroids(clusters, k);
        
        printf("Iteration %d:\n", iteration + 1);
        for (int i = 0; i < k; i++) {
            printf("Cluster %d: Centroid(%.2f, %.2f)\n", i + 1, clusters[i].centroid.x, clusters[i].centroid.y);
        }
        printf("\n");
    }
    
    return 0;
}
// -----------------------------------------------------------------------------------------------
//gcc -o kmeans_program kmeans.c -lm


