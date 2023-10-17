#pragma once
#include <lib/graph.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool Check(UnorientedGraph& graph, set<size_t>& infected_cities) {
    set<size_t> remaining_cities;
    for (int i = 0; i < graph.Size(); i++) {
        if (infected_cities.find(i) == infected_cities.end()) {
            remaining_cities.insert(i);
        }
    }

    while (!remaining_cities.empty()) {
        bool found = false;
        for (int city : remaining_cities) {
            int cnt = 0;
            for (int neighbor : graph[city]) {
                if (infected_cities.find(neighbor) != infected_cities.end()) {
                    ++cnt;
                }
            }
            if (cnt >= 2) {
                infected_cities.insert(city);
                remaining_cities.erase(city);
                found = true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    UnorientedGraph graph;
    std::cin.rdbuf(in.rdbuf());
    InGraph(graph);

    in.close();
    std::ifstream in1(argv[2]);
    std::cin.rdbuf(in1.rdbuf());

    int cnt;
    std::cin >> cnt;
    std::set<size_t> cities;
    int t;

    for (int i = 0; i < cnt; ++i) {
        std::cin >> t;
        std::cout << t << ' ';
        t -= 1;
        cities.insert(t);
    }
    in1.close();

    if (Check(graph, cities)) {
        return 0;
    } else {
        return -1;
    }
}
