#include "list_graph.h"
#include <cassert>

ListGraph::ListGraph(const IGraph& graph) : list_graph(graph.VerticesCount()) {
    for (int i = 0; i < list_graph.size(); ++i) {
        list_graph[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < list_graph.size());
    assert(0 <= to && to < list_graph.size());
    list_graph[from].push_back(to);
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < list_graph.size());
    return list_graph[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < list_graph.size());
    std::vector<int> prevs;

    for (const auto & from : list_graph) {
        for (int to: from) {
            if (to == vertex) prevs.push_back(to);
        }
    }
    return prevs;
}
