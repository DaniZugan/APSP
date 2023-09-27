#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

long geom_edges;
int seed = 1;
float** GenerateGridGraph(int sqrN)
{
	int n = sqrN*sqrN;
	float** graph = (float**)malloc(sizeof(float*)*n);
	for (int i=0; i<n; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*n);
		for (int j=0; j<n; j++)
		{
			graph[i][j] = INFTY;
		}
	}
	for (int j=0; j<sqrN; j++)
	{
		for (int i=0; i<sqrN-1; i++)
		{
			graph[i + j*sqrN][(i+1) + j*sqrN] = frand();
			graph[(i+1) + j*sqrN][i + j*sqrN] = graph[i + j*sqrN][(i+1) + j*sqrN];
		}
	}
	
	for (int i=0; i<sqrN; i++)
	{
		for (int j=0; j<sqrN-1; j++)
		{
			graph[i + j*sqrN][i + (j+1)*sqrN] = frand();
			graph[i + (j+1)*sqrN][i + j*sqrN] = graph[i + j*sqrN][i + (j+1)*sqrN];
		}
	}

	return graph;
}

float** GenerateCompleteGraph(int n, int unit)
{
	float** graph = (float**)malloc(sizeof(float*)*n);
	for (int i=0; i<n; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*n);
		for (int j=0; j<n; j++)
		{
			if (i != j)
			{
				if (unit)
					graph[i][j] = 1;
				else
					graph[i][j] = frand();
			}
			else
				graph[i][j] = INFTY;
		}
	}
	
	return graph;
}

float** GenerateBinomERGraph(int n, double prob)
{	
	long edges = 0;
	float** graph = (float**)malloc(sizeof(float*)*n);
	for (int i=0; i<n; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*n);
		}
	do {
	
	for (int i=0; i<n; i++)
	{		
		for (int j=0; j<n; j++)
		{
			if (i != j)
			{
				if (drand() < prob){
					graph[i][j] = frand();
					edges++;					
				}
										
				else
					graph[i][j] = INFTY;
			}
			else
				graph[i][j] = INFTY;
		}
	}

	}
	while (0);

	printf("Number of edges: %d\n", edges);
	FILE *csvFile = fopen("data.csv", "a");
	fprintf(csvFile, "%ld,", edges);
	fclose(csvFile);
	
		// is not Connected
	
	
	return graph;
}

float** GenerateAlbertBarabasi(int vertices, int m, int klika)
{
	srand(seed);
	printf("Seed: %d\n", seed);	// to see if seed is correctly incremented
	long long arcs = 0;	// for counting edges
	
    float** graph = (float**)malloc(sizeof(float*)*vertices);

	for (int i=0; i<vertices; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*vertices);
	}
    
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph[i][j] = 0.0;
        }
        
    }
    
    
    int *degree = (int*)malloc(sizeof(int)*vertices);
    
    for (int i = 0; i < klika; i++)
    {
        degree[i] = klika-1;    // stopnja vsake točke v začetni kliki    
        

        for (int j = 0; j < klika; j++) // vse povezave so 1, diagonala je 0
        {
            if (i != j)
            {
                graph[i][j] = 1.0;
            }
            else
            {
                graph[i][j] = 0.0;
            }
            
        }
        
    }
	// vsota stopenj
    int SumDegrees = klika * (klika-1);

	// seznam dodanih točk v rundi
    int* added = (int*)malloc(m * sizeof(int));
    
    // dodajamo točke od začetne klike do končne točke (vertices)
    for (int i = klika; i < vertices; i++)
    {          
        for (int o = 0; o < m; o++)
        {
            added[o] = -1;
        }       

        // število dodanih povezav v vsaki rundi
        int attachedEdges = 0;
        
        while (attachedEdges < m)
        {   
            
            // izberemo naključno celo število med [0, vsota stopenj)
            int chosen = rand() % SumDegrees;
			
            if (SumDegrees<chosen)
            {
                printf("Random degree problem");
            }              
            

            // število namenjeno prištevanju stopenj da bi prišli do tiste, ki smo jo naključno izbrali
            int cumWeigth = 0;

            // naključno stopnjo iščemo med trenutnimi vozlišči
            for (int j = 0; j < i; j++)
            {   
                
                if ((degree[j] + cumWeigth) > chosen)
                {   
                    // če je povezava že bila dodana v tej rundi
                    if (containsValue(added, m, j))
                    {						
                        break;
                    }
                    else
                    {
                        graph[j][i] = 1.0;
                        graph[i][j] = 1.0;
                        added[attachedEdges] = j;
                        attachedEdges++;
                        break;
                    }                    
                    
                }
                else
                {
                    cumWeigth += degree[j];
					
                }
                
            }
                        

        }

        // posodobitev stopenj
        for (int z = 0; z < attachedEdges; z++)
        {
            degree[added[z]]++;            
        }

        SumDegrees = SumDegrees + (2*m);        
        degree[i] = m;
        
        
    }
    
	free(added);
    free(degree);
	
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {   

            if (graph[i][j] == 0.0)
            {
                graph[i][j] = INFTY;
            }
            
            else if (graph[i][j] == 1.0 && graph[j][i] == 1.0)
            {
                if (frand()< 0.5)
                {
                    graph[i][j] = frand();
                    graph[j][i] = INFTY;
                }
                else
                {
                    graph[i][j] = INFTY;
                    graph[j][i] = frand();
                }
				arcs++;                
            }
            
        }
        
    }
    
	
    if (isConnected(graph, vertices))
    {	
		seed++;
		FILE *csvFile = fopen("data.csv", "a");
		fprintf(csvFile, "%ld,", arcs);
		fclose(csvFile);
		return graph;        
    }
	else {
        seed++;
        for (int c = 0; c < vertices; c++) {
                free(graph[c]);
            }
            free(graph);        
        if (seed > 100)
        {
            
            printf("to high seed");
            return NULL;
        }       
        
        return  graph = GenerateAlbertBarabasi(vertices, m, klika);  
    }        	
	
    
}


float** GenerateSparseGraph(int n, int edgesToAdd, int unitWeight)
{
	// 1. Ensure strong connectivity by creating a cycle of length n
	// 2. Construct edge list, permute it randomly, then take first K edges.
	if (edgesToAdd > n*(n-1))
		edgesToAdd = n*(n-1);
	float** graph = (float**)malloc(sizeof(float*)*n);
	
	for (int i=0; i<n; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*n);
		for (int j=0; j<n; j++)
		{
			graph[i][j] = INFTY;
		}
	}
	
	int* list = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++)
	{
		list[i] = i;
	}
	shuffle(list, n);
	int prev = -1;
	for (int i=0; i<n; i++)
	{
		if (prev != -1)
		{
			if (unitWeight)
			{
				graph[prev][list[i]] = 1.0f;
			}
			else
			{
				graph[prev][list[i]] = frand();
			}
		}
		prev = list[i];
	}
	if (unitWeight)
	{
		graph[prev][list[0]] = 1.0f;
	}
	else
	{
		graph[prev][list[0]] = frand();
	}
	
	free(list);
	
	list = (int*)malloc(sizeof(int)*n*(n-2)); // no loops, none of the cycle-edges
	int listSize = 0;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (i != j && !isfinite_cust(graph[i][j]))
			{
				list[listSize++] = i*n + j;
			}
		}
	}
	edgesToAdd -= n;
	// Permute edge list
	shuffle(list, listSize);
	for (int newEdge = 0; newEdge < edgesToAdd; newEdge++)
	{
		int j=list[newEdge]%n;
		int i=(list[newEdge] - j)/n;

		if (unitWeight)
		{
			graph[i][j] = 1.0f;
		}
		else
		{
			graph[i][j] = frand();
		}
	}
	free(list);
	
	return graph;
}

float** GenerateGeometricGraph(int n, float threshold)
{
	geom_edges = 0;
	int edges = 0;
	float** graph = (float**)malloc(sizeof(float*)*n);
	/*for (int i=0; i<n; i++)
	{
		graph[i] =  (float*)malloc(sizeof(float)*n);
		for (int j=0; j<n; j++)
		{
			graph[i][j] = INFTY;
		}
	}
	
	// Generate points
	
	float* x = (float*)malloc(sizeof(float)*n);
	float* y = (float*)malloc(sizeof(float)*n);
	
	for (int i=0; i<n; i++)
	{
		x[i] = frand();
		y[i] = frand();
	}
	
	// Generate random spanning tree
	
	int* list = (int*)malloc(sizeof(int)*n);
	for (int i=0; i<n; i++)
	{
		list[i] = i;
	}
	shuffle(list, n);
	
	for (int i=1; i<n; i++)
	{
		int src = list[i];
		int targ = list[rand()%i];
		graph[src][targ] = sqrt((x[src] - x[targ])*(x[src] - x[targ]) + (y[src]-y[targ])*(y[src]-y[targ]));
		graph[targ][src] = graph[src][targ];
		edges += 2;
	}
	
	// Now add edges between close enough points
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (i == j || isfinite_cust(graph[i][j]))
				continue;
			float distance = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i]-y[j])*(y[i]-y[j]));
			if (distance <= threshold)
			{
				graph[i][j] = distance;
				edges++;
			}
		}
	}
	geom_edges = edges;
	free(y);
	free(x);
	free(list);*/
	return graph;
}