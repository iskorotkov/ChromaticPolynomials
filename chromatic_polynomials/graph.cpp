#include "graph.h"
#include <algorithm>
#include <ostream>
#include <algorithm>

graph::graph(const int vertices)
{
	vertices_data_.resize(vertices, std::vector<bool>(vertices, false));
}

void graph::add_edge(const int vertex1, const int vertex2)
{
	vertices_data_.at(vertex1).at(vertex2) = true;
	vertices_data_.at(vertex2).at(vertex1) = true;
}

void graph::merge_vertices(const int vertex1, const int vertex2)
{
	for (auto vertex = 0, vertices = count_vertices(); vertex < vertices; vertex++)
	{
		if (vertex != vertex1 && vertex != vertex2 && has_edge(vertex2, vertex))
		{
			add_edge(vertex1, vertex);
		}
	}
	remove_vertex(vertex2);
}

expression graph::calculate_chromatic_polynomial() const
{
	expression expr;
	if (is_tree())
	{
		expr.add_tree(count_vertices());
	}
	else if (!has_edges())
	{
		expr.add_empty(count_vertices());
	}
	else
	{
		auto copy = *this;
		copy.calculate_chromatic_polynomial_impl(expr);
	}
	return expr;
}

int graph::count_vertices() const
{
	return vertices_data_.size();
}

int graph::count_edges() const
{
	auto edges = 0;
	for (auto row = 0, vertices = count_vertices(); row < vertices; row++)
	{
		for (auto column = row + 1; column < vertices; column++)
		{
			if (has_edge(row, column))
			{
				++edges;
			}
		}
	}
	return edges;
}

bool graph::is_complete() const
{
	const auto vertices = count_vertices();
	const auto edges = count_edges();
	return vertices * (vertices - 1) / 2 == edges;
}

bool graph::is_tree() const
{
	const auto first_vertex = 0;
	std::vector<char> vertices_reached(count_vertices(), not_reached);
	const auto no_cycles = is_tree_impl(vertices_reached, first_vertex);
	const auto all_vertices_reached = std::find(vertices_reached.cbegin(), vertices_reached.cend(), not_reached) == vertices_reached.cend();
	return no_cycles && all_vertices_reached;
}

bool graph::has_edges() const
{
	for (const auto& vec : vertices_data_)
	{
		for (const auto& val : vec)
		{
			if (val)
			{
				return true;
			}
		}
	}
	return false;
}

bool graph::has_edge(const int vertex1, const int vertex2) const
{
	return vertices_data_[vertex1][vertex2];
}

void graph::remove_vertex(const int vertex)
{
	vertices_data_.erase(vertices_data_.begin() + vertex);
	std::for_each(vertices_data_.begin(), vertices_data_.end(), [vertex](auto & vec) { vec.erase(vec.begin() + vertex); });
}

void graph::calculate_chromatic_polynomial_impl(expression & expr)
{
	if (is_complete())
	{
		expr.add_complete(count_vertices());
	}
	else
	{
		const auto p = get_two_unrelated_vertices();
		const auto first = p.first;
		const auto second = p.second;
		auto g_plus = create_g_plus(first, second);
		merge_vertices(first, second);
		calculate_chromatic_polynomial_impl(expr);
		g_plus.calculate_chromatic_polynomial_impl(expr);
	}
}

bool graph::is_tree_impl(std::vector<char> & vertices_reached, const int current_vertex) const
{
	if (vertices_reached[current_vertex] == explored)
	{
		return false;
	}
	vertices_reached[current_vertex] = reached;
	for (auto vertex = 0, vertices = count_vertices(); vertex < vertices; ++vertex)
	{
		if (has_edge(current_vertex, vertex)
			&& vertices_reached[vertex] != reached
			&& !is_tree_impl(vertices_reached, vertex))
		{
			return false;
		}
	}
	vertices_reached[current_vertex] = explored;
	return true;
}

graph graph::create_g_plus(const int vertex1, const int vertex2) const
{
	graph g = *this;
	g.add_edge(vertex1, vertex2);
	return g;
}

std::pair<int, int> graph::get_two_unrelated_vertices() const
{
	for (auto row = 0, vertices = count_vertices(); row < vertices; row++)
	{
		for (auto column = row + 1; column < vertices; column++)
		{
			if (!has_edge(row, column))
			{
				return std::make_pair(row, column);
			}
		}
	}
	throw std::logic_error("There is no unrelated vertices");
}

std::ostream& operator<<(std::ostream & stream, const graph & g)
{
	stream << "Graph: " << std::endl;
	for (auto row = 0, vertices = g.count_vertices(); row < vertices; row++)
	{
		for (auto column = 0; column < vertices; column++)
		{
			stream << g.has_edge(row, column) << " ";
		}
		stream << std::endl;
	}
	return stream;
}
