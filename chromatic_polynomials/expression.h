#pragma once
#include <string>

class expression
{
public:
	void multiply(int multiplier, int power = 1);
	void multiply_by_factorial(int min_multiplier, int max_multiplier);

	int evaluate(int x) const;

private:
};
