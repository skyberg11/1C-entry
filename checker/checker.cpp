#pragma once
#include <lib/graph.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool Check(UnorientedGraph& graph, set<int>& infected_cities) {
    set<int> remaining_cities;
    for (int i = 0; i < graph.Size(); i++) {
        if (infected_cities.find(i) == infected_cities.end()) {
            remaining_cities.insert(i);
        }
    }

    while (!remaining_cities.empty()) {
        bool found = false;
        vector<int> to_erase;
        for (int city : remaining_cities) {
            int cnt = 0;
            for (int neighbor : graph[city]) {
                if (remaining_cities.find(neighbor) == remaining_cities.end()) {
                    ++cnt;
                    if (cnt >= 2) {
                        break;
                    }
                }
            }
            if (cnt >= 2) {
                infected_cities.insert(city);
                to_erase.push_back(city);
                found = true;
            }
        }
        for (auto it : to_erase) {
            remaining_cities.erase(it);
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
    std::set<int> cities;
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
