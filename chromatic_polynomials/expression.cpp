#include "expression.h"
#include "string"

void expression::add_complete(const int vertices)
{
	graph_data g = { graph_type::complete, vertices };
	++sum_[g];
}

void expression::add_tree(const int vertices)
{
	graph_data g = { graph_type::tree, vertices };
	++sum_[g];
}

void expression::add_empty(int vertices)
{
	graph_data g = { graph_type::empty, vertices };
	++sum_[g];
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

expression operator+(const expression & lhs, const expression & rhs)
{
	expression result;
	result.sum_.insert(lhs.sum_.cbegin(), lhs.sum_.cend());
	for (const auto& gd : rhs.sum_)
	{
		result.sum_[gd.first] += gd.second;
	}
	return result;
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
			str += "x!/(x-" + std::to_string(gd.first.vertices) + ")!";
			break;
		case graph_type::tree:
			str += "x(x-1)^" + std::to_string(gd.first.vertices - 1);
			break;
		case graph_type::empty:
			str += "x^" + std::to_string(gd.first.vertices);
			break;
		default:
			throw std::logic_error("Unknown graph type");
		}
	}
	stream << str;
	return stream;
}
