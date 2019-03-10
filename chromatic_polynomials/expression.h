#pragma once
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
	friend std::ostream& operator<<(std::ostream& stream, const expression& expr);
public:
	void add_complete(int vertices);
	void add_tree(int vertices);
	void add_empty(int vertices);

	int evaluate(int x) const;

private:
	std::map<graph_data, int> sum_;
};

bool operator==(const graph_data& lhs, const graph_data& rhs);
bool operator<(const graph_data& lhs, const graph_data& rhs);

std::ostream& operator<<(std::ostream& stream, const expression& expr);
