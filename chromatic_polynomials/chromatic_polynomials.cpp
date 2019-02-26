// chromatic_polynomials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"
#include <fstream>

template <typename T>
void print(T param = "", const std::string& message = "")
{
	std::cout << message << param << std::endl;
}

graph read_graph()
{
	const auto input_file = "input.txt";
	std::ifstream input(input_file);
	auto dimension = 0;
	input >> dimension;
	graph g(dimension);
	for (auto row = 0; row < dimension; row++)
	{
		for (auto column = 0; column < dimension; column++)
		{
			auto edge_present = 0;
			input >> edge_present;
			if (edge_present)
			{
				g.add_edge(row, column);
			}
		}
	}
	return g;
}

int main()
{
	auto g = read_graph();
	std::cout << g;
	print(g.is_complete(), "Complete Graph? ");
	print(g.is_tree(), "Tree? ");
}
