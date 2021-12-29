#include "arc_graph.h"
#include <cassert>

ArcGraph::ArcGraph(const IGraph& graph) : vert_count(graph.VerticesCount()) {
    for (int i = 0; i < vert_count; ++i) {
        for (auto &neigh: graph.GetNextVertices(i)) {
            pairs.emplace_back(i, neigh);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < vert_count);
    assert(0 <= to && to < vert_count);
    pairs.emplace_back(from, to);
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < vert_count);
    std::vector<int> next;
    for (const auto &pair: pairs) {
        if (pair.first == vertex) next.push_back(pair.second);
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < vert_count);
    std::vector<int> prev;
    for (const auto &pair: pairs) {
        if (pair.second == vertex) prev.push_back(pair.first);
    }
    return prev;
}
