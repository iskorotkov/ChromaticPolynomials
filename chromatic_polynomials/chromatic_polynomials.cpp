#include "graph.h"
#include "expression.h"
#include <fstream>
#include <iostream>
#include <chrono>

std::pair<graph, int> read_graph()
{
	const std::string input_file = "input.txt";
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
	auto x = 0;
	input >> x;
	return std::make_pair(g, x);
}

void write_result(const graph& g, int x)
{
	const std::string output_file = "output.txt";
	std::ofstream output(output_file);
	const auto result = g.calculate_chromatic_polynomial();
	output << result << std::endl << result.evaluate(x);
}

void normal_launch()
{
	const auto p = read_graph();
	const auto g = p.first;
	const auto x = p.second;
	write_result(g, x);
}

void performance_test(const int iterations = 1000)
{
	const auto start = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < iterations; ++i)
	{
		normal_launch();
	}
	const auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>((end - start) / iterations).count() << " ms";
}

int main()
{
	//performance_test(20);
	normal_launch();
}
