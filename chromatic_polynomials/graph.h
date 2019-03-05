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
	enum status
	{
		not_reached,
		reached,
		explored
	};

	std::vector<std::vector<bool>> vertices_data_;

	void remove_vertex(int vertex);

	expression calculate_chromatic_polynomial_impl();

	bool is_tree_impl(std::vector<char>& vertices_reached, int current_vertex) const;

	graph create_g_plus(int vertex1, int vertex2) const;
	graph create_g_minus(int vertex1, int vertex2) const;

	std::pair<int, int> get_two_unrelated_vertices() const;
};

std::ostream& operator<<(std::ostream& stream, const graph& g);
