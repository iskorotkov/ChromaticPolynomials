#pragma once
#include "expression.h"
#include <vector>

class graph
{
public:
	explicit graph(int vertices);

	void add_edge(int vertex1, int vertex2);
	void merge_vertices(int vertex1, int vertex2);

	expression calculate_chromatic_polynomial() const;

	int count_vertices() const;
	int count_edges() const;

	bool is_complete() const;
	bool is_tree() const;
	bool has_edges() const;
	bool has_edge(int vertex1, int vertex2) const;
	bool has_vertex(int vertex) const;

private:
	std::vector<std::vector<bool>> vertices_data_;

	void remove_vertex(int vertex);

	bool is_tree_impl(std::vector<bool>& vertices_reached, int current_vertex) const;
};

std::ostream& operator<<(std::ostream& stream, const graph& g);
