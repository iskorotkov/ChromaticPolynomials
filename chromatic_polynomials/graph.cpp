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

int graph::count_vertices() const
{
	return vertices_data_.size();
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

std::ostream & operator<<(std::ostream & stream, const graph & g)
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
