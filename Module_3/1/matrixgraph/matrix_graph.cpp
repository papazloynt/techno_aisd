#include "matrix_graph.h"
#include <cassert>

MatrixGraph::MatrixGraph(int size) : matrix(size) {
    for (auto & i : matrix) {
        i = std::vector<bool>(size, false);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph) : matrix(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        matrix[i] = std::vector<bool>(graph.VerticesCount(), false);
        for (const auto &neight: graph.GetNextVertices(i)) {
            matrix[i][neight] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < matrix.size());
    assert(0 <= to && to < matrix.size());
    matrix[from][to] = true;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < matrix.size());
    std::vector<int> next;
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[vertex][i]) next.push_back(i);
    }
    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < matrix.size());
    std::vector<int> prev;
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][vertex]) prev.push_back(i);
    }
    return prev;
}
