#include "expression.h"
#include "string"

void expression::add_complete(const int vertices)
{
	++sum_[{ graph_type::complete, vertices }];
}

void expression::add_tree(const int vertices)
{
	++sum_[{ graph_type::tree, vertices }];
}

void expression::add_empty(const int vertices)
{
	++sum_[{ graph_type::empty, vertices }];
}

int expression::evaluate(const int x) const
{
	auto result = 0;
	for (const auto& gd : sum_)
	{
		auto accumulator = gd.second;
		switch (gd.first.type)
		{
		case graph_type::complete:
			for (auto i = 0; i < gd.first.vertices; i++)
			{
				accumulator *= x - i;
			}
			break;
		case graph_type::empty:
			accumulator *= static_cast<int>(std::pow(x, gd.first.vertices));
			break;
		case graph_type::tree:
			accumulator *= x * static_cast<int>(std::pow(x - 1, gd.first.vertices - 1));
			break;
		default:
			throw std::logic_error("Unknown graph type");
		}
		result += accumulator;
	}
	return result;
}

bool operator==(const graph_data & lhs, const graph_data & rhs)
{
	return lhs.type == rhs.type && lhs.vertices == rhs.vertices;
}

bool operator<(const graph_data & lhs, const graph_data & rhs)
{
	return lhs.type < rhs.type ||
		lhs.type == rhs.type && lhs.vertices < rhs.vertices;
}

std::ostream& operator<<(std::ostream & stream, const expression & expr)
{
	std::string str;
	for (const auto& gd : expr.sum_)
	{
		if (!str.empty())
		{
			str += " + ";
		}
		if (gd.second > 1)
		{
			str += std::to_string(gd.second) + "*";
		}
		switch (gd.first.type)
		{
		case graph_type::complete:
			str += "x";
			for (auto i = 1; i < gd.first.vertices; ++i)
			{
				str += "*(x-" + std::to_string(i) + ")";
			}
			break;
		case graph_type::tree:
			str += "x";
			for (auto i = 0; i < gd.first.vertices - 1; ++i)
			{
				str += "*(x-1)";
			}
			break;
		case graph_type::empty:
			str += "x";
			for (auto i = 0; i < gd.first.vertices - 1; ++i)
			{
				str += "*x";
			}
			break;
		default:
			throw std::logic_error("Unknown graph type");
		}
	}
	stream << str;
	return stream;
}
