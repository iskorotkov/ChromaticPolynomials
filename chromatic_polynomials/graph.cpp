#include "graph.h"
#include <cassert>
#include <algorithm>
#include <ostream>

graph::graph(const int vertices)
{
	vertices_data_.resize(vertices);
	std::for_each(vertices_data_.begin(), vertices_data_.end(), [vertices](auto & vec) { vec.resize(vertices, false); });
}

void graph::add_edge(const int vertex1, const int vertex2)
{
	assert(has_vertex(vertex1));
	assert(has_vertex(vertex2));

	vertices_data_[vertex1][vertex2] = true;
	vertices_data_[vertex2][vertex1] = true;
}

void graph::merge_vertices(const int vertex1, const int vertex2)
{
	for (auto vertex = 0, vertices = count_vertices(); vertex < vertices; vertex++)
	{
		if (vertex != vertex1 && vertex != vertex2)
		{
			if (has_edge(vertex1, vertex) || has_edge(vertex2, vertex))
			{
				add_edge(vertex1, vertex);
			}
		}
	}
	remove_vertex(vertex2);
}

expression graph::calculate_chromatic_polynomial() const
{
	expression expr;
	// TODO: check for tree structure or edges absence only for original graph; if original graph doesn't meet conditions, other graphs won't either
	if (is_tree())
	{
		expr.add_tree(count_vertices());
	}
	else if (is_complete())
	{
		expr.add_complete(count_vertices());
	}
	else if (!has_edges())
	{
		expr.add_empty(count_vertices());
	}
	else
	{
		const auto [first, second] = get_two_unrelated_vertices();
		// TODO: avoid copying adjustment matrix twice - copy only once and reuse this graph for second call
		auto g_minus = create_g_minus(first, second);
		auto g_plus = create_g_plus(first, second);
		expr = g_minus.calculate_chromatic_polynomial() + g_plus.calculate_chromatic_polynomial();
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
	// TODO: is there are several link components, we can't be sure there is no loops (not all edges will be traversed)
	const auto first_vertex = 0;
	std::vector<bool> vertices_reached(count_vertices());
	return is_tree_impl(vertices_reached, first_vertex);
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
	return has_vertex(vertex1)
		&& has_vertex(vertex2)
		&& vertices_data_[vertex1][vertex2];
}

bool graph::has_vertex(const int vertex) const
{
	return vertex >= 0 && vertex <= count_vertices();
}

void graph::remove_vertex(int vertex)
{
	vertices_data_.erase(vertices_data_.begin() + vertex);
	std::for_each(vertices_data_.begin(), vertices_data_.end(), [vertex](auto & vec) { vec.erase(vec.begin() + vertex); });
}

bool graph::is_tree_impl(std::vector<bool> & vertices_reached, int current_vertex) const
{
	if (vertices_reached[current_vertex])
	{
		return false;
	}
	vertices_reached[current_vertex] = true;
	for (auto vertex = current_vertex + 1, vertices = count_vertices(); vertex < vertices; vertex++)
	{
		if (has_edge(current_vertex, vertex) && !is_tree_impl(vertices_reached, vertex))
		{
			return false;
		}
	}
	return true;
}

graph graph::create_g_plus(int vertex1, int vertex2) const
{
	graph g = *this;
	g.add_edge(vertex1, vertex2);
	return g;
}

graph graph::create_g_minus(int vertex1, int vertex2) const
{
	graph g = *this;
	g.merge_vertices(vertex1, vertex2);
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
