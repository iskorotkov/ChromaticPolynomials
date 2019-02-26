// chromatic_polynomials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"

int main()
{
    auto dimension = 0;
    std::cin >> dimension;
    graph g(dimension);
    for (auto row = 0; row < dimension; row++)
    {
        for (auto column = 0; column < dimension; column++)
        {
            auto edge_present = 0;
            std::cin >> edge_present;
            if (edge_present)
            {
                g.add_edge(row, column);
            }
        }
    }
    std::cout << g;
    g.merge_vertices(1, 2);
    std::cout << g;
}
