#include "graph.h"
#include <cassert>
#include <algorithm>

graph::graph(const int vertices)
{
	vertices_data_.resize(vertices);
	std::for_each(vertices_data_.begin(), vertices_data_.end(), [vertices](auto v) { v.resize(vertices, false); });
}

void graph::add_edge(const int v1, const int v2)
{
	assert(has_vertex(v1));
	assert(has_vertex(v2));

	vertices_data_[v1][v2] = true;
	vertices_data_[v2][v1] = true;
}

int graph::count_vertices() const
{
	return vertices_data_.size();
}

bool graph::has_edge(const int v1, const int v2) const
{
	return has_vertex(v1)
		&& has_vertex(v2)
		&& vertices_data_[v1][v2];
}

bool graph::has_vertex(const int v1) const
{
	return v1 >= 0 && v1 <= count_vertices();
}
