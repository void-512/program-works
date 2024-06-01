#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

// init(size): returns a size * size array with random number between 0-10 to represent a graph
int **init(const int size) {
    srand((unsigned)time(NULL));
    int **graph = malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) {
        graph[i] = malloc(sizeof(int) * size);
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            graph[i][j] = rand() % 10;
            graph[j][i] = graph[i][j];
        }
        graph[i][i] = 0;
    }
    return graph;
}

// minDistance(dist, accessed, size): returns the index that's closest to the source
int minDistance(int *dist, bool *accessed, const int size) {
    int min_dist = INT_MAX;
    int min_idx = -1;
    for (int i = 0; i < size; i++) {
        if (!accessed[i] && dist[i] < min_dist) {
            min_dist = dist[i];
            min_idx = i;
        }
    }
    return min_idx;
}

// dijkstra(graph, size, src): returns the list of the shortest distance between src and each element
int *dijkstra(int **graph, const int size, const int src) {
    bool *accessed = malloc(sizeof(bool) * size);
    int *dist = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        accessed[i] = false;
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    for (int idx = 0; idx < size; idx++) {
        int min_idx = minDistance(dist, accessed, size);
        accessed[idx] = true;
        for (int i = 0; i < size; i++) {
            if (!accessed[i] && graph[min_idx][i] != 0 && dist[min_idx] != INT_MAX && dist[min_idx] + graph[min_idx][i] < dist[i]) {
                dist[i] = dist[min_idx] + graph[min_idx][i];
            }
        }
    }
    free(accessed);
    return dist;
} 

// print(graph, dist, size): print all the information
void print(int **graph, const int *dist, const int size) {
    puts("Graph:");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    puts("================================================");
    puts("Vertex \t\t Distance from index 0");
    for (int i = 0; i < size; i++) {
        printf("%d \t\t\t %d\n", i, dist[i]);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) { 
        puts("err: dijkstra [n] to determine the graph size");
        return 1;
    }
    int size = atoi(argv[1]);
    int **graph = init(size);
    int *dist = dijkstra(graph, size, 0);
    print(graph, dist, size);
    free(graph);
    free(dist);
    return 0;
}