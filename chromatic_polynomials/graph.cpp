#include "graph.h"
#include <cassert>

graph::graph(const int vertices)
{
	vertices_amount_ = vertices;
}

void graph::add_edge(int v1, int v2)
{
	assert(has_vertex(v1));
	assert(has_vertex(v2));

	vertices_data_[v1][v2] = true;
	vertices_data_[v2][v1] = true;
}

int graph::count_vertices() const
{
	return vertices_amount_;
}

bool graph::has_edge(const int v1, const int v2) const
{
	return has_vertex(v1)
		&& has_vertex(v2)
		&& vertices_data_[v1][v2];
}

bool graph::has_vertex(const int v1) const
{
	return v1 >= 0 && v1 <= vertices_amount_;
}
