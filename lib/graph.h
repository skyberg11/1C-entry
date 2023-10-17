#pragma once
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class UnorientedGraph {
  public:
    struct Edge {
        Edge(size_t from, size_t to) : from(from), to(to) {}
        Edge() = default;

        bool IsIncident(size_t cur) const { return from == cur || to == cur; };

        size_t from = -1;
        size_t to = -1;
    };

    UnorientedGraph() = default;

    UnorientedGraph(size_t nodes_cnt)
        : m_node_cnt_(nodes_cnt), m_nodes_edges_(nodes_cnt) {}

    void AddEdge(size_t from, size_t to) {
        m_nodes_edges_[from].push_back(to);
        m_nodes_edges_[to].push_back(from);

        m_edges_.emplace_back(from, to);
    }

    size_t Size() const { return m_node_cnt_; }

    std::vector<Edge> Edges() const { return m_edges_; }

    std::vector<size_t> operator[](size_t index) {
        return m_nodes_edges_[index];
    }

  protected:
    size_t m_node_cnt_ = 0;  // количество ребер
    std::vector<Edge> m_edges_;
    std::vector<std::vector<size_t>>
        m_nodes_edges_;  // для каждой вершины храним список смежных ребер
};

class AbstractSolver {
  public:
    using Edge = UnorientedGraph::Edge;
    virtual std::vector<size_t> GetOptimalCover(UnorientedGraph& graph) = 0;
};

void InGraph(UnorientedGraph& graph) {
    int edges_cnt;
    std::cin >> edges_cnt;
    graph = UnorientedGraph(edges_cnt);

    for (size_t i = 0; i < edges_cnt; ++i) {
        size_t from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
}

void OutAnswer(std::vector<size_t>& answer) {
    std::cout << answer.size() << '\n';
    for (auto& node : answer) {
        std::cout << node + 1 << ' ';
    }
    std::cout << '\n';
}