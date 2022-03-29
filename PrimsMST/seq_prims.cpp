// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
#include <limits.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

// Number of vertices in the graph
int num_nodes = 30000;
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


// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < num_nodes; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int** graph)
{
	cout<<"Edge \tWeight\n";
	for (int i = 1; i < num_nodes; i++)
		cout<<parent[i]<<" - "<<i<<" "<<graph[i][parent[i]]<<" \n";
}

void printTotalWeight(int parent[], int** graph)
{
	//cout << "run print weight" << endl;
    unsigned long long sum = 0;
    for (int i = 1; i < num_nodes; i++)
    {
        sum += graph[i][parent[i]];
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

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < num_nodes; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST
	if (printEdges)
		printMST(parent, graph);
	printTotalWeight(parent, graph);
}

// arg1 - printEdges
int main(int argc, char* argv[])
{
	if (argc > 1)
		printEdges = stoi(argv[1]);
	int num_edges;
	cin >> num_nodes >> num_edges;
	// Random graph generation
    

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