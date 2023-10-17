#include <lib/graph.h>
#include <solver/greedy.h>
#include <solver/vertexcover.h>

int main() {
    AbstractSolver* solver = new VertexCover();
    UnorientedGraph graph;

    InGraph(graph);

    std::vector<size_t> answer = solver->GetOptimalCover(graph);

    OutAnswer(answer);
}