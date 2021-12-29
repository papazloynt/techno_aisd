#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, unsigned int len) = 0;

    [[nodiscard]] virtual int VerticesCount() const  = 0;

    [[nodiscard]] virtual std::vector<std::pair<int, unsigned int>> GetNextVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph {
public:
    ListGraph(int size) : list_graph(size) {}

    ~ListGraph() = default;

    void AddEdge(int from, int to, unsigned int len) {
        assert(0 <= from && from < list_graph.size());
        assert(0 <= to && to < list_graph.size());
        list_graph[from].push_back(std::make_pair(to, len));
    }

    int VerticesCount() const { return list_graph.size();}

    std::vector<std::pair<int, unsigned int>> GetNextVertices(int vertex) const {
        assert(0 <= vertex && vertex < list_graph.size());
        return list_graph[vertex];
    }

private:
    std::vector<std::vector<std::pair<int, unsigned int>>> list_graph;
};

unsigned int shortest_path(const IGraph& graph, unsigned int from, unsigned int to) {
    std::vector<unsigned int> distance(graph.VerticesCount(), -1);
    distance[from] = 0;

    std::set<std::pair<unsigned int, unsigned int>> priority_q;
    priority_q.insert(std::make_pair(0, from));
    while (!priority_q.empty()) {
        auto vertex = *priority_q.begin();
        priority_q.erase(priority_q.begin());

        for (std::pair<int, unsigned int> neigh : graph.GetNextVertices(vertex.second)) {
            if (distance[neigh.first] == -1) {
                distance[neigh.first] = distance[vertex.second] + neigh.second;
                priority_q.insert(std::make_pair(distance[neigh.first], neigh.first));
            } else if (distance[neigh.first] > distance[vertex.second] + neigh.second) {
                auto p = priority_q.find(std::make_pair(distance[neigh.first], neigh.first));
                if (p != priority_q.end()) {
                    priority_q.erase(p);
                }
                distance[neigh.first] = distance[vertex.second] + neigh.second;
                priority_q.insert(std::make_pair(distance[neigh.first], neigh.first));
            }
        }
    }
    return distance[to];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    ListGraph graph(n);

    for (int i = 0; i < m; ++i)  {
        int from, to, t;
        std::cin >> from >> to >> t;
        if (from != to) {
            graph.AddEdge(from, to, t);
            graph.AddEdge(to, from, t);
        }
    }
    int final_from, final_to;
    std::cin >> final_from >> final_to;

    std::cout << shortest_path(graph, final_from, final_to) << std::endl;
}
