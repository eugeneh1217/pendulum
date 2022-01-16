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
		std::vector<T> GetK0(std::vector<T> x, T step);
		std::vector<T> GetKMid(std::vector<T> x, T step, std::vector<T> prev_k);
		std::vector<T> GetK3(std::vector<T> x, T step, std::vector<T> k2);
		std::vector<T> GetKSum(std::vector<T> x, T step);
		std::vector<T> Step(std::vector<T> initial, double step);
	private:
		std::vector<T (*)(std::vector<T>)> derivatives;
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
std::vector<T> RungeKuttaSystem<T>::GetK0(std::vector<T> x, T step)
{
	return vmath::ScalarProd(Evaluate(x), step);
}

template<typename T>
std::vector<T> RungeKuttaSystem<T>::GetKMid(std::vector<T> x, T step, std::vector<T> prev_k)
{
	prev_k = prefix_vector(prev_k, step);
	return vmath::ScalarProd(Evaluate(vmath::VectorSum(x, vmath::ScalarQuot(prev_k, 2))), step);
}

template<typename T>
std::vector<T> RungeKuttaSystem<T>::GetK3(std::vector<T> x, T step, std::vector<T> k2)
{
	k2 = prefix_vector(k2, step);
	return vmath::ScalarProd(Evaluate(vmath::VectorSum(x, k2)), step);
}
template<typename T>
std::vector<T> RungeKuttaSystem<T>::GetKSum(std::vector<T> x, T step)
{
	std::vector<std::vector<T>> k;
	k.push_back(GetK0(x, step));
	k.push_back(GetKMid(x, step, k.back()));
	k.push_back(GetKMid(x, step, k.back()));
	k.push_back(GetK3(x, step, k.back()));
	std::vector<T> k_sum = vmath::VectorSum(k[0], vmath::ScalarProd(k[1], 2));
	k_sum = vmath::VectorSum(k_sum, vmath::ScalarProd(k[2], 2));
	return vmath::VectorSum(k_sum, k[3]);
}

template<typename T>
std::vector<T> RungeKuttaSystem<T>::Step(std::vector<T> initial, double step)
{
	std::vector<T> kterm = prefix_vector(vmath::ScalarQuot(GetKSum(initial, step), 6), step);
	return vmath::VectorSum(initial, kterm);
}

#endif