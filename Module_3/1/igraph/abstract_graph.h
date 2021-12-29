#ifndef INC_1_ABSTRACT_GRAPH_H
#define INC_1_ABSTRACT_GRAPH_H

#include <vector>

// Разнести всё по файлам
// Добавить explicit
// Добавить override
// Проверить работу всех


struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    [[nodiscard]] virtual int VerticesCount() const  = 0;

    [[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    [[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //INC_1_ABSTRACT_GRAPH_H
