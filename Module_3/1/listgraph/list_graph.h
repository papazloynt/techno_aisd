#ifndef INC_1_LIST_GRAPH_H
#define INC_1_LIST_GRAPH_H

#include "abstract_graph.h"

struct ListGraph: public IGraph {
public:
    explicit ListGraph(int size) : list_graph(size) {}
    explicit ListGraph(const IGraph& graph);
    ~ListGraph() override = default;

    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override { return list_graph.size();}
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override ;

private:
    std::vector<std::vector<int>> list_graph;
};

#endif //INC_1_LIST_GRAPH_H
