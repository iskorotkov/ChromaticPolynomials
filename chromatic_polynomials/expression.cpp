#include "expression.h"

void expression::add_complete(int vertices)
{
	graph_data g = { graph_type::complete, vertices };
	++sum[g];
}

void expression::add_tree(int vertices)
{
	graph_data g = { graph_type::tree, vertices };
	++sum[g];
}

void expression::add_empty(int vertices)
{
	graph_data g = { graph_type::empty, vertices };
	++sum[g];
}

int expression::evaluate(int x) const
{
	auto result = 0;
	for (const auto& gd : sum)
	{
		switch (gd.first.type)
		{
		case graph_type::complete:
			auto accum = 1;
			for (auto i = 0; i < gd.first.vertices; i++)
			{
				accum *= x - i;
			}
			result += accum;
			break;
		}
	}
	return result;
}

bool operator==(const graph_data& lhs, const graph_data& rhs)
{
	return lhs.type == rhs.type && lhs.vertices == rhs.vertices;
}

bool operator<(const graph_data& lhs, const graph_data& rhs)
{
	return lhs.type < rhs.type ||
		lhs.type == rhs.type && lhs.vertices < rhs.vertices;
}

expression operator+(const expression& lhs, const expression& rhs)
{
	// TODO: implement
	return expression();
}

std::ostream& operator<<(std::ostream& stream, const expression& expr)
{
	std::string str;
	for (const auto& gd : expr.get_sum())
	{
		if (!str.empty())
		{
			str += " + ";
		}
		if (gd.second > 1)
		{
			str += gd.second + "*";
		}
		switch (gd.first.type)
		{
		case graph_type::complete:
			str += "x!/(x-" + std::to_string(gd.first.vertices) + ")!";
			break;
		}
	}
	stream << str;
	return stream;
}
