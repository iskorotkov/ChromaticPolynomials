#pragma once
#include <string>
#include <ostream>
#include <map>

enum class graph_type
{
	complete,
	tree,
	empty
};

struct graph_data
{
	graph_type type;
	int vertices;
};

class expression
{
public:
	void add_complete(int vertices);
	void add_tree(int vertices);
	void add_empty(int vertices);

	int evaluate(int x) const;

	const auto& get_sum() const { return sum; }

private:
	std::map<graph_data, int> sum;
};

bool operator==(const graph_data& lhs, const graph_data& rhs);

bool operator<(const graph_data& lhs, const graph_data& rhs);

// TODO: provide operator+= as well
expression operator+(const expression& lhs, const expression& rhs);

std::ostream& operator<<(std::ostream& stream, const expression& expr);
