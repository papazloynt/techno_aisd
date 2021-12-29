#ifndef INC_1_SET_GRAPH_H
#define INC_1_SET_GRAPH_H

#include "../igraph/abstract_graph.h"
#include <unordered_set>

struct SetGraph : public IGraph {
public:
    explicit SetGraph(int size) : sets(size) {}
    explicit SetGraph(const IGraph& graph);
    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override { return sets.size(); }
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<unsigned int>> sets{};
};

#endif //INC_1_SET_GRAPH_H
