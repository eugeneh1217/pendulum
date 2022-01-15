#ifndef RUNGEKUTTASYSTEM_H
#define RUNGEKUTTASYSTEM_H

#include "vmath.h"

#include <algorithm>
#include <vector>

template<typename T>
std::vector<T> prefix_vector(std::vector<T> const vec, T prefix)
{
	std::vector<T> out{ prefix };
	for (auto e : vec)
	{
		out.push_back(e);
	}
	return out;
}

template<typename T>
class RungeKuttaSystem
{
	public:
		int size;
		RungeKuttaSystem( std::vector <T (*)(std::vector<T>)> system);
		// x should be 1 larger than system for indep var.
		std::vector<T> Evaluate(std::vector<T> x);
		// initial should be 1 larger than system for indep var.
		std::vector<T> Step(std::vector<T> initial, double step);
	private:
		std::vector <T (*)(std::vector<T>)> derivatives;
};

template<typename T>
RungeKuttaSystem<T>::RungeKuttaSystem(std::vector<T(*)(std::vector<T>)> system)
{
	derivatives = system;
	size = system.size();
}

template<typename T>
std::vector<T> RungeKuttaSystem<T>::Evaluate(std::vector<T> x)
{
	std::vector<T> out;
	for (auto function : derivatives)
	{
		out.push_back(function(x));
	}
	return out;
}

template<typename T>
std::vector<T> RungeKuttaSystem<T>::Step(std::vector<T> initial, double step)
{
	std::vector<std::vector<T>> k;
	std::vector<T> intermesso;
	// k[0] = h * f(x[0], x[1], ..., x[n])
	k.push_back(vmath::ScalarProd(Evaluate(initial), step));
	intermesso = prefix_vector(k.back(), step);
	intermesso = vmath::ScalarQuot(intermesso, 2);
	// k[1] = h * f(x[0] + h/2, x[0] + k[0][0] / 2, ..., x[n] + k[0][n-1] / 2)
	k.push_back(vmath::ScalarProd(Evaluate(vmath::VectorSum(initial, intermesso)), step));
	intermesso = prefix_vector(k.back(), step);
	intermesso = vmath::ScalarQuot(intermesso, 2);
	// k[2] = h * f(x[0] + h/2, x[0] + k[1][0] / 2, ..., x[n] + k[1][n-1] / 2)
	k.push_back(vmath::ScalarProd(Evaluate(vmath::VectorSum(initial, intermesso)), step));
	intermesso = prefix_vector(k.back(), step);
	// k[3] = h * f(x[0] + h, x[1] + k[2][0], ..., x[n] + k[2][n-1])
	k.push_back(vmath::ScalarProd(Evaluate(vmath::VectorSum(initial, intermesso)), step));
	//std::vector<T> next_x = ( k[0] + (k[1]/2) + (k[2]/2) + k[3] );
	std::vector<T> next_x = vmath::VectorSum(
		vmath::VectorSum(k[0], vmath::ScalarQuot(k[1], 2)),
		vmath::VectorSum(vmath::ScalarQuot(k[2], 2), k[3])
	);
	/*next_x = vmath::SMap(next_x, 6, [](auto e) { return vmath::ScalarQuot(e, 6); });*/
	next_x = vmath::ScalarQuot(next_x, 6);
	next_x = prefix_vector(next_x, step);
	return vmath::VectorSum(next_x, initial);
}

#endif