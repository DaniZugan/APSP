#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// returns array with m 1s randomly (other 0)
int* createSelectionArray(int n, int m) {
    if (m > n) {
        printf("Error: Cannot select %d spots in an array of size %d.\n", m, n);
        return NULL;
    }

    int* values = (int*)malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++) {
        values[i] = 0;
    }

    // Randomly pick m spots to set to 1
    int selected = 0;
    while (selected < m) {
        int index = rand() % n; // Random index from 0 to n-1
        if (values[index] == 0) {  // Only select if the spot is not already selected
            values[index] = 1;
            selected++;
        }
    }

    // Print the resulting array
    printf("Selection array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    return values;
}

void printGraph(float** graph, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", graph[i][j]);
        }
        printf("\n");
    }
}

float** GenerateDAG(int N, float p) {
    float** graph = (float**)malloc(sizeof(float*) * N);
    for (int i = 0; i < N; i++) {
        graph[i] = (float*)malloc(N * sizeof(float));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = INFINITY;
        }
    }

    // ensure that the graph is acyclic
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Add edge from i to j with probability p
            if ((float)rand() / (float)RAND_MAX < p) {
                graph[i][j] = (float)rand() / (float)RAND_MAX;
            }
        }
    }
    return graph;
}

float** GenerateDag(int N, int edges) {
    float** graph = (float**)malloc(sizeof(float*) * N);
    for (int i = 0; i < N; i++) {
        graph[i] = (float*)malloc(N * sizeof(float));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = INFINITY;
        }
    }

    int pos = N*(N-1)*0.5;
    printf("%d\n", pos);
    int* selection = createSelectionArray(N*(N-1)*0.5, edges);
    int index = 0;

    // ensure that the graph is acyclic
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (selection[index] == 1) {
                graph[i][j] = (float)rand() / (float)RAND_MAX;
            }
            index++;
        }
    }

    free(selection);
    return graph;
}


int main(void) {

    srand(time(NULL));

    int N = 5;
    float** graph = GenerateDag(N, 6);

    printGraph(graph, N);

    for (int i = 0; i < N; ++i) {
        free(graph[i]);
    }
    free(graph);



    return 0;
}


