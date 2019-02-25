#pragma once
#include <string>

class expression
{
public:
	bool add_multiplier(int multiplier);

	int evaluate(int x) const;

private:
	std::string expr_;
};
