// Parallel implementation of Prim's algorithm
// to compile on mac: clang++ -Xpreprocessor -fopenmp par_prims.cpp -o par.out -lomp
// to compile libomp needs to be installed, this can be done with homebrew with the command:
// homebrew install libomp
// to compile on windows: g++ -fopenmp par_prims.cpp -o par.exe
// fopenmp needs to be enabled in GCC to compile

// Command line execution arguments: ./par.out (./par.exe on WINDOWS) #MAXNUMTHREADS #NUMVECTORS
#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <string>
using namespace std;

int num, num_nodes = 30000;
bool printEdges = false;

int** graph_generator()
{
    srand(time(NULL));
    int ** graph = (int**)calloc(num_nodes,sizeof(int*));
    for (int i = 0; i < num_nodes; i++)
    {
        graph[i] = (int*)calloc(num_nodes,sizeof(int));

        for (int j = 0; j < num_nodes; j++)
        {
            if (i == j)
                continue;
            if (j < i)
            {
                graph[i][j] = graph[j][i];
                continue;
            }
            bool conn = (rand() % 10) > 0;
            if (conn)
                graph[i][j] = (rand() % num_nodes);
            
        }
    }
    return graph;
}

// Function to print the adjacency matrix
void print_graph(int** graph)
{
    cout << "{\n";
    for (int i = 0; i < num_nodes; i++)
    {
        cout << "{";
        for (int j = 0; j < num_nodes; j++)
        {
            cout << graph[i][j];
            cout << ",";
        }
        cout << "},\n";
    }
}

// A utility function to find the vertex with
// minimum key value remaining, with parallelization included
int minKey(int key[], bool mstSet[])
{
	 int min = INT_MAX, index, i;
     // set the outer nest to be parallel so that intialized data is hosted on the correct thread
#pragma omp parallel
    {
        //num = omp_get_num_threads();
        //cout << num << endl;
        int index_local = index;
        int min_local = min;

        // Run this for-loop concurrently with a nowait condition
#pragma omp for nowait
        for (i = 0; i < num_nodes; i++)
        {
            if (mstSet[i] == false && key[i] < min_local)
            {
                min_local = key[i];
                index_local = i;
            }
        }
        // establish the portion that needs to be synchronized across threads
#pragma omp critical
        {
            if (min_local < min)
            {
                min = min_local;
                index = index_local;
            }
        }
    }
    return index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int** graph)
{
	cout<<"Edge \tWeight\n";
	for (int i = 1; i < num_nodes; i++)
    {
        cout << parent[i];
        cout << " - ";
        cout << i;
        cout <<" ";
        cout << (int)graph[i][parent[i]];
        cout << endl;
    }
		
}

void printTotalWeight(int parent[], int** graph)
{
    unsigned long long sum = 0;
    for (int i = 1; i < num_nodes; i++)
    {
        sum +=graph[i][parent[i]];
    }
    cout << sum;
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int** graph)
{
    
	// Array to store constructed MST
	int* parent = (int*)(calloc(num_nodes, sizeof(int)));
	
	// Key values used to pick minimum weight edge in cut
	int* key = (int*)(calloc(num_nodes, sizeof(int)));
	
	// To represent set of vertices included in MST
	bool* mstSet = (bool*)(calloc(num_nodes, sizeof(bool)));;

	// Initialize all keys as INFINITE
	for (int i = 0; i < num_nodes; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first vertex.
	key[0] = 0;
	parent[0] = -1; // First node is always root of MST

	// The MST will have num_nodes vertices
	for (int count = 0; count < num_nodes - 1; count++)
	{
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Set parallelization point 
#pragma omp parallel for schedule(static)
		for (int v = 0; v < num_nodes; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST, if user specified
    if (printEdges)
	    printMST(parent, graph);
    // print total MST weight, to check correctness
    printTotalWeight(parent, graph);
}

// arg1 - max number of threads
// arg2 - non-zero if you want edges printed
int main(int argc, char *argv[])
{
    int num_threads = 4;
    num_nodes = 30000;
    int num_edges;
    // Grabbing command line arguments
    if (argc > 1)
        num_threads = stoi(argv[1]);
    if (argc > 2)
        printEdges = stoi(argv[2]);
    omp_set_num_threads(num_threads);
    cin >> num_nodes >> num_edges;

	// Reading in adjacency matrix
    int ** graph = (int**)(malloc(num_nodes*sizeof(int*)));
    for (int i = 0; i < num_nodes; i++)
        graph[i] = (int*)(calloc(num_nodes, sizeof(int)));

    while (num_edges > 0)
    {
        int start, end, weight;
        cin >> start >> end >> weight;
        graph[start][end] = weight;
        graph[end][start] = weight;
        num_edges--;
    }

    clock_t startTime = clock();
    primMST(graph);
    //cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds" << endl;

	return 0;
}
