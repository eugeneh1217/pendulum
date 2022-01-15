#include "gtest/gtest.h"

#include "runge_kutta_system.h"

#include <vector>
#include <numeric>
#include <sstream>
#include <string>

#include <iostream>
#include <cstring>

template<typename T>
std::string to_string(T x)
{
	std::ostringstream ss;
	ss << x;
	return ss.str();
}

template<typename T>
wchar_t* vector_to_wchar_t(std::vector<T> vec)
{
	std::ostringstream ss;
	for (auto value : vec)
	{
		ss << value << " ";
	}
	std::string str = ss.str();
	std::wstring widestring = std::wstring(str.begin(), str.end());
	return (wchar_t*) widestring.c_str();
}

template<typename T>
char* vector_to_string(std::vector<T> vec)
{
	std::ostringstream ss;
	for (auto value : vec)
	{
		ss << value << " ";
	}
	return const_cast<char*>(ss.str().c_str());
}

double y_deriv(std::vector<double> input)
{
    return input[1] + input[2];
}

double z_deriv(std::vector<double> input)
{
    return 2 * input[1] + input[2];
}

TEST(TestRungeKuttaSystem, TestEvaluate)
{
    std::vector<double (*)(std::vector<double>)> system{ y_deriv, z_deriv };
    RungeKuttaSystem<double> solver(system);
    std::vector<double> input = std::vector<double>{ 1.0, 2.0, 3.0 };
    std::vector<double> out = solver.Evaluate(input);
    std::vector<double> expected = std::vector<double>{ 5.0, 7.0 };
    ASSERT_EQ(out, expected);
}
TEST(TestRungeKuttaSystem, TestSize)
{
    std::vector<double (*)(std::vector<double>)> system{ y_deriv, z_deriv };
    RungeKuttaSystem<double> solver(system);
    ASSERT_EQ(solver.size, 2);
}
TEST(TestRungeKuttaSystem, TestStep)
{
    std::vector<double (*)(std::vector<double>)> system{ y_deriv, z_deriv };
    RungeKuttaSystem<double> solver(system);
    std::vector<double> actual = solver.Step(std::vector<double>{ 0, 0, 1 }, 1);
    std::vector<double> expected{ 1 / 6, 10 / 3, 43 / 8 };
    ASSERT_EQ(actual, expected);
}
