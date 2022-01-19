#include "Fuzzy.h"

/// <summary>
/// Membership Function for range 0 -> 1
/// </summary>
/// <param name="t_val">Starting Value</param>
/// <param name="t_x0">Leftmost Value (0)</param>
/// <param name="t_x1">Rightmost Value (1)</param>
/// <returns>Value position in Grade</returns>
float FuzzyLogic::Grade(float t_val, float t_x0, float t_x1)
{
	float result = 0;

	if (t_val <= t_x0)
		result = 0;
	else if (t_val > t_x1)
		result = 1;
	else
		result = ((t_val - t_x0) / (t_x1 - t_x0));
	
	return result;
}

/// <summary>
/// Triangle Membership Function for range 0 -> 1 -> 0
/// </summary>
/// <param name="t_val">Starting Value</param>
/// <param name="t_x0">Leftmost Value (0)</param>
/// <param name="t_x1">Center Value (1)</param>
/// <param name="t_x2">Rightmost Value (0)</param>
/// <returns>Value position in Triangle</returns>
float FuzzyLogic::Triangle(float t_val, float t_x0, float t_x1, float t_x2)
{
	float result = 0;

	if ((t_val <= t_x0) || (t_val >= t_x2))
		result = 0;
	else if (t_val == t_x1)
		result = 1;
	else if ((t_val > t_x0) && (t_val < t_x1))
		result = ((t_val - t_x0) / (t_x1 - t_x0));
	else
		result = ((t_x2 - t_val) / (t_x2 - t_x1));
	
	return result;
}

/// <summary>
/// Trapezoid Membership Function for range 0 -> 1 -> 1 -> 0
/// </summary>
/// <param name="t_val">Starting Value</param>
/// <param name="t_x0">Leftmost Value (0)</param>
/// <param name="t_x1">Center Leftmost Value (1)</param>
/// <param name="t_x2">Center Rightmost Value (1)</param>
/// <param name="t_x3">Rightmost Value (0)</param>
/// <returns>Value position in Trapezoid</returns>
float FuzzyLogic::Trapezoid(float t_val, float t_x0, float t_x1, float t_x2, float t_x3)
{
	float result = 0;

	if ((t_val <= t_x0) || (t_val >= t_x3))
		result = 0;
	else if ((t_val >= t_x1) && (t_val <= t_x2))
		result = 1;
	else if ((t_val > t_x0) && (t_val < t_x1))
		result = ((t_val - t_x0) / (t_x1 - t_x0));
	else
		result = ((t_x3 - t_val) / (t_x3 - t_x2));
	
	return result;
}
