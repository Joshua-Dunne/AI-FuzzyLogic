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
	static double Grade(double t_val, double t_x0, double t_x1);
	static double Triangle(double t_val, double t_x0, double t_x1, double t_x2);
	static double Trapezoid(double t_val, double t_x0, double t_x1, double t_x2, double t_x3);

	// Logical Operators
	static double AND(double t_a, double t_b) { return std::min(t_a, t_b); };
	static double OR(double t_a, double t_b) { return std::max(t_a, t_b); };
	static double NOT(double t_a) { return 1.0 - t_a; };
};

#endif