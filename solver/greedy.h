#pragma once
#include <lib/graph.h>

// Жадный алгоритм
class Greedy : public AbstractSolver {
  public:
    std::vector<size_t> GetOptimalCover(UnorientedGraph& graph) {
        int infected = 0;

        cover.clear();
        cover_addition.clear();

        std::vector<size_t> answer;
        for (int i = 0; i < graph.Size(); ++i) {
            cover_addition.insert(i);
        }
        while (cover.size() < graph.Size()) {
            int best = FindBestCityToInfect(graph);
            if (best == -1) {
                size_t rnd = *cover_addition.begin();
                cover_addition.erase(cover_addition.begin());
                cover.insert(rnd);
                propagate(graph, rnd);
                answer.push_back(rnd);
            } else {
                cover_addition.erase(best);
                cover.insert(best);
                answer.push_back(best);

                propagate(graph, best);
            }
        }

        return answer;
    }

  private:
    void propagate(UnorientedGraph& graph, size_t node) {
        for (int neighbor : graph[node]) {
            if (cover.find(neighbor) != cover.end())
                continue;
            int cnt = 0;
            for (int nn : graph[neighbor]) {
                if (nn == node || cover.find(nn) != cover.end()) {
                    ++cnt;
                }
            }
            if (cnt >= 2) {
                cover.insert(neighbor);
                cover_addition.erase(neighbor);
                propagate(graph, neighbor);
            }
        }
    }

    int FindBestCityToInfect(UnorientedGraph& graph) {
        int best = -1;
        int maxi = 0;

        for (size_t city = 0; city < graph.Size(); city++) {
            if (cover.find(city) == cover.end()) {
                int infections = 0;
                for (int neighbor : graph[city]) {
                    int cnt = 0;
                    for (int nn : graph[neighbor]) {
                        if (nn == city || cover.find(nn) != cover.end()) {
                            ++cnt;
                        }
                    }
                    if (cnt >= 2) {
                        ++infections;
                    }
                }

                if (infections > maxi) {
                    maxi = infections;
                    best = city;
                }
            }
        }

        return best;
    }

    std::set<size_t> cover, cover_addition;
};
