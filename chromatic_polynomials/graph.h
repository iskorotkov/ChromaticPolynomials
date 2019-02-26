#pragma once
#include "expression.h"
#include <vector>

class graph
{
public:
	explicit graph(int vertices);

	void add_edge(int v1, int v2);
	void merge_vertices(int v1, int v2);

	expression calculate_chromatic_polynomial() const;

	int count_vertices() const;
	int count_edges() const;

	bool is_complete() const;
	bool is_tree() const;
	bool has_edges() const;
	bool has_edge(int v1, int v2) const;
	bool has_vertex(int v1) const;

private:
	std::vector<std::vector<bool>> vertices_data_;
	int vertices_amount_;
};
