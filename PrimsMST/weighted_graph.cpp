#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define VEC_FACT 5

int V = 20000;

int getRandomNode(vector<int> arr)
{
    int ran = rand() % (int)(arr.size());   
    for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        if (ran == 0)
            return *it;
        ran--;
    }
    return -1;
}

// arg1 - numNodes
int main(int argc, char* argv[])
{
    if (argc > 1)
        V = stoi(argv[1]);
    int** graph = (int**)(malloc(V*sizeof(int*)));
    srand(time(NULL));
    pair<int, int>* edges = (pair<int, int>*)(malloc(V*VEC_FACT*sizeof(pair<int, int>)));
    vector<int> conn;
    vector<int> unconnected;
    for (int i = 1; i < V; i++)
    {
        unconnected.push_back(i);
    }
    bool* connected = (bool*)calloc(V,sizeof(bool));
    int edgeCount = 0;
    connected[0] = true;
    conn.push_back(0);

    for (int i = 0; i < V; i++)
        graph[i] = (int*)calloc(V,sizeof(int));
    while (!unconnected.empty())
    {
        int curr = getRandomNode(conn);
        while (curr == -1) curr = getRandomNode(conn);
        int randInd = rand() % (int) (unconnected.size());
        int end = unconnected.at(randInd);

        // remove end from unconnected vector
        unconnected.erase(unconnected.begin() + randInd);

        // add new edge to pairs, newly connected node to conn
        conn.push_back(end);
        edges[edgeCount++] = pair<int, int>(curr, end);
        connected[end] = true;

        // add edge weight
        graph[curr][end] = rand() % V;
        graph[end][curr] = graph[curr][end];
        
    }
    //cout << "base MST created" << endl;

    while (edgeCount < V * VEC_FACT)
    {
        int start = rand() % V;
        int end = rand() % V;
        while (start == end || graph[start][end])
        {
            start = rand() % V;
            end = rand() % V;
        }
        graph[start][end] = rand() % V;
        graph[end][start] = graph[start][end];
        edges[edgeCount++] = pair<int, int>(start,end);

    }

    cout << V << endl << edgeCount << endl;

    for (int i = 0; i < edgeCount; i++)
    {
        cout << edges[i].first << "\t" << edges[i].second << "\t" << graph[edges[i].first][edges[i].second] << endl;
    }
    
    return 0;
}