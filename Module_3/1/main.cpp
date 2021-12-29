#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"
#include "arc_graph.h"

#include <iostream>
#include <queue>

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(vertex);
    visited[vertex] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::cout << current << "  ";

        for (auto neigh : graph.GetNextVertices(current)) {
            if (!visited[neigh]) {
                visited[neigh] = true;
                q.push(neigh);
            }
        }
    }
}

void mainBFS(const IGraph& graph) {
    std::cout << "BFS: ";
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            BFS(graph, i, visited);
        }
    }
    std::cout << std::endl;
}

int main() {
    ListGraph list_graph(7);
    list_graph.AddEdge(0, 1);
    list_graph.AddEdge(0, 5);
    list_graph.AddEdge(1, 2);
    list_graph.AddEdge(1, 3);
    list_graph.AddEdge(1, 5);
    list_graph.AddEdge(1, 6);
    list_graph.AddEdge(3, 2);
    list_graph.AddEdge(3, 4);
    list_graph.AddEdge(3, 6);
    list_graph.AddEdge(5, 4);
    list_graph.AddEdge(5, 6);
    list_graph.AddEdge(6, 4);

    std::cout << "List ";
    mainBFS(list_graph);

    MatrixGraph matrix_graph(list_graph);
    std::cout << "Matrix ";
    mainBFS(matrix_graph);

    ArcGraph arc_graph(matrix_graph);
    std::cout << "Arc ";
    mainBFS(arc_graph);

    SetGraph set_graph(arc_graph);
    std::cout << "Set ";
    mainBFS(set_graph);

    return 0;
}
