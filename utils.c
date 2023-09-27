#include <stdlib.h>
#include <math.h>
#include <stdbool.h>



#define INFTY INFINITY/*256000.f*/
#define INFTY_CMP 128000.f

bool isfinite_cust(float n) { /*return n < INFTY_CMP;*/return isfinite(n); }
double drand() { return ((double)rand())/((double)RAND_MAX); }
float frand() {	return (float)drand(); }

void shuffle(int *array, int n)
{
    if (n > 1) 
    {
		for (int i=n-1; i>=1; i--)
		{
			int j = (int)(drand()*((double)i));
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
    }
}

void dfs(float **adjMatrix, bool *visited, int node, int vertices) {
    visited[node] = true;
    for (int neighbor = 0; neighbor < vertices; neighbor++) {
        if ((adjMatrix[node][neighbor] > 0) && adjMatrix[node][neighbor] <= 1 && !visited[neighbor]) {
            dfs(adjMatrix, visited, neighbor, vertices);
        }
    }
}

bool isConnected(float **adjMatrix, int vertices) {    
    bool *visited = (bool*)malloc(vertices * sizeof(bool));
    if (visited == NULL) {
        printf("Memory allocation failed\n");
        return false;
    }
    for (int node = 0; node < vertices; node++) {
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        dfs(adjMatrix, visited, node, vertices);
        
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                printf("false\n");
                free(visited);
                return false;
            }
        }        
    }
    free(visited);
    return true;
}

bool containsValue(const int* array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return true;
        }
    }
    return false;
}





