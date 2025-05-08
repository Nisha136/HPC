#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void parallelDFS(vector<vector<int>>& adjList, int startNode, int numVertices) {
    vector<bool> visited(numVertices, false);
    stack<int> s;

    s.push(startNode);
    visited[startNode] = true;

    cout << "\nDFS Traversal: ";

    while (!s.empty()) {
        int u;

        #pragma omp critical
        {
            u = s.top();
            s.pop();
            cout << u << " ";
        }

        // Parallel for loop for adjacent nodes
        #pragma omp parallel for
        for (int i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];

            if (!visited[v]) {
                #pragma omp critical
                {
                    if (!visited[v]) {
                        visited[v] = true;
                        s.push(v);
                    }
                }
            }
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<int>> adjList(vertices);

    cout << "Enter edges (u v) format (0-based index):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u); // undirected graph
    }

    int startNode;
    cout << "Enter starting node: ";
    cin >> startNode;

    double start = omp_get_wtime();
    parallelDFS(adjList, startNode, vertices);
    double end = omp_get_wtime();

    cout << "\nTime taken: " << (end - start) << " seconds\n";

    return 0;
}
