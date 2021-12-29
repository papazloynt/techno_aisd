#ifndef INC_1_ARC_GRAPH_H
#define INC_1_ARC_GRAPH_H

#include "abstract_graph.h"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int size) : vert_count(size) {}
    explicit ArcGraph(const IGraph& graph);
    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override { return vert_count; }
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> pairs;
    int vert_count;
};

#endif //INC_1_ARC_GRAPH_H
