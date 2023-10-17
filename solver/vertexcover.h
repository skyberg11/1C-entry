#pragma once
#include <lib/graph.h>

// Ищет листья + вершинное покрытие
class VertexCover : public AbstractSolver {
  public:
    std::vector<size_t> GetOptimalCover(UnorientedGraph& graph) {
        std::vector<size_t> vertex_cover = FindLeafNodes(graph);
        std::vector<Edge> uncovered_edges = graph.Edges();

        while (!uncovered_edges.empty()) {
            Edge arbitrary_edge = uncovered_edges.back();

            vertex_cover.push_back(arbitrary_edge.from);
            vertex_cover.push_back(arbitrary_edge.to);

            std::vector<Edge> new_uncovered_nodes;
            for (auto& edge : uncovered_edges) {
                if (!(edge.IsIncident(arbitrary_edge.from) ||
                      edge.IsIncident(arbitrary_edge.to))) {
                    new_uncovered_nodes.push_back(edge);
                }
            }

            uncovered_edges = new_uncovered_nodes;
        }

        std::sort(vertex_cover.begin(), vertex_cover.end());
        vertex_cover.erase(
            std::unique(vertex_cover.begin(), vertex_cover.end()),
            vertex_cover.end());
        return vertex_cover;
    }

  private:
    std::vector<size_t> FindLeafNodes(UnorientedGraph& graph) {
        std::vector<size_t> leaf_nodes;

        for (size_t i = 0; i < graph.Size(); i++) {
            if (graph[i].size() == 1) {
                leaf_nodes.push_back(i);
            }
        }

        return leaf_nodes;
    }
};
