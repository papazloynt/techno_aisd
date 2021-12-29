#include <cassert>
#include <iostream>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    [[nodiscard]] virtual int VerticesCount() const  = 0;

    [[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    [[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph {
public:
    ListGraph(int size) : list_graph(size) {}

    ListGraph(const IGraph& graph) : list_graph(graph.VerticesCount()) {
        for (int i = 0; i < list_graph.size(); ++i) {
            list_graph[i] = graph.GetNextVertices(i);
        }
    }

    ~ListGraph() = default;

    void AddEdge(int from, int to) {
        assert(0 <= from && from < list_graph.size());
        assert(0 <= to && to < list_graph.size());
        list_graph[from].push_back(to);
    }

    int VerticesCount() const { return list_graph.size();}

    std::vector<int> GetNextVertices(int vertex) const {
        assert(0 <= vertex && vertex < list_graph.size());
        return list_graph[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const {
        assert(0 <= vertex && vertex < list_graph.size());
        std::vector<int> prevs;

        for (int from = 0; from < list_graph.size(); ++from) {
            for (int to : list_graph[from]) {
                if (to == vertex) prevs.push_back(to);
            }
        }
        return prevs;
    }

private:
    std::vector<std::vector<int>> list_graph;
};

enum Color {
    white,
    gray,
    black
};


unsigned int number_of_shortest_paths(const IGraph& graph, unsigned int from, unsigned int to) {
    std::vector<unsigned int> distance(graph.VerticesCount(), UINT32_MAX);
    distance[from] = 0;

    std::vector<unsigned int> count(graph.VerticesCount(), 0);
    count[from] = 1;

    std::queue<unsigned int> q;
    q.push(from);

    std::vector<Color> visited(graph.VerticesCount(), white);
    visited[from] = gray;

    while (!q.empty()) {
        auto vertex = q.front();
        q.pop();

        for (unsigned int neigh : graph.GetNextVertices(vertex)) {
            if (visited[neigh] == white) {
                visited[neigh] = gray;
                distance[neigh] = distance[vertex] + 1;
                count[neigh] = count[vertex];
                q.push(neigh);
            } else if (visited[neigh] == gray && distance[neigh] == distance[vertex] + 1) {
                count[neigh] += count[vertex];
            } else if (visited[neigh] == black && neigh == to) { break; }
        }
        visited[vertex] = black;
    }

    return count[to];
}

int main() {
    int v, n;
    std::cin >> v >> n;

    ListGraph graph(v);
    for (int i = 0; i < n; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int number_from, number_to;
    std::cin >> number_from >> number_to;

    std::cout << number_of_shortest_paths(graph, number_from, number_to) << std::endl;
    return 0;
}

