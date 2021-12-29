#ifndef INC_1_MATRIX_GRAPH_H
#define INC_1_MATRIX_GRAPH_H

#include "abstract_graph.h"

struct MatrixGraph: public IGraph {
public:
    explicit MatrixGraph(int size);
    explicit MatrixGraph(const IGraph& graph);
    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override { return matrix.size(); }
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> matrix;
};

#endif //INC_1_MATRIX_GRAPH_H
