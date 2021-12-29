#include "set_graph.h"
#include <cassert>
#include <unordered_set>

SetGraph::SetGraph(const IGraph& graph) : sets(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for (auto &neigh: graph.GetNextVertices(i)) {
            sets[i].insert(neigh);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < sets.size());
    assert(0 <= to && to < sets.size());
    sets[from].insert(to);
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < sets.size());
    return std::vector<int>(sets[vertex].begin(), sets[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < sets.size());
    std::vector<int> prev;
    for (int i = 0; i < sets.size(); ++i) {
        if (sets[i].find(vertex) != sets[i].end()) prev.push_back(i);
    }
    return prev;
}
