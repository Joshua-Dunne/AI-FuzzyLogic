#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <algorithm>

/// <summary>
/// 
/// </summary>
class FuzzyLogic
{
public:

	FuzzyLogic() {};

	// Membership Functions
	static float Grade(float t_val, float t_x0, float t_x1);
	static float Triangle(float t_val, float t_x0, float t_x1, float t_x2);
	static float Trapezoid(float t_val, float t_x0, float t_x1, float t_x2, float t_x3);

	// Logical Operators
	static float AND(float t_a, float t_b) { return std::min(t_a, t_b); };
	static float OR(float t_a, float t_b) { return std::max(t_a, t_b); };
	static float NOT(float t_a) { return 1.0f - t_a; };
};

#endif