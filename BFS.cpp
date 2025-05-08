#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void parallelBFS(vector<vector<int>>& adjList, int startNode, int numVertices) {
    vector<bool> visited(numVertices, false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    cout << "\nBFS Traversal: ";

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;

        // Get all nodes of current level
        for (int i = 0; i < levelSize; ++i) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            currentLevel.push_back(node);
        }

        // Process current level in parallel
        #pragma omp parallel for
        for (int i = 0; i < currentLevel.size(); ++i) {
            int u = currentLevel[i];
            for (int v : adjList[u]) {
                if (!visited[v]) {
                    #pragma omp critical
                    {
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
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
    parallelBFS(adjList, startNode, vertices);
    double end = omp_get_wtime();

    cout << "\nTime taken: " << (end - start) << " seconds\n";

    return 0;
}
