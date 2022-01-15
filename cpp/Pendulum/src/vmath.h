#ifndef VMATH_H
#define VMATH_H

#include<vector>
#include<algorithm>
#include<functional>

namespace vmath
{
	// Broadcast binary operation taking vector on left and scalar on right
	template<typename L, typename R, typename BinaryOp>
	std::vector<L> ScalarMap(std::vector<L> left, R right, BinaryOp binary_op)
	{
		std::transform(left.begin(), left.end(), left.begin(), [=](L e) -> L { return binary_op(e, L(right)); });
		return left;
	}

	// Apply elementwise operation between two vectors
	// Similar to std::inner_product
	template<typename L, typename R, typename BinaryOp>
	std::vector<L> VectorMap(std::vector<L> left, std::vector<R> right, BinaryOp binary_op)
	{
		std::transform(left.begin(), left.end(), right.begin(), left.begin(), binary_op);
		return left;
	}

	// Return sum of two vectors
	template<typename L, typename R>
	std::vector<L> VectorSum(std::vector<L> left, std::vector<R> right)
	{
		return VectorMap(left, right, std::plus<L>());
	}

	// Return sum of vector and scalar
	template<typename L, typename R>
	std::vector<L> ScalarSum(std::vector<L> left, R right)
	{
		return ScalarMap(left, right, std::plus<L>());
	}

	// Return difference between two vectors
	template<typename L, typename R>
	std::vector<L> VectorDiff(std::vector<L> left, std::vector<R> right)
	{
		return VectorMap(left, right, std::minus<L>());
	}

	// Return difference between vector and scalar
	template<typename L, typename R>
	std::vector<L> ScalarDiff(std::vector<L> left, R right)
	{
		return ScalarMap(left, right, std::minus<L>());
	}

	// Return hadamard product of two vectors
	template<typename L, typename R>
	std::vector<L> VectorProd(std::vector<L> left, std::vector<R> right)
	{
		return VectorMap(left, right, std::multiplies<L>());
	}

	// Return product of vector and scalar
	template<typename L, typename R>
	std::vector<L> ScalarProd(std::vector<L> left, R right)
	{
		return ScalarMap(left, right, std::multiplies<L>());
	}
	
	// Return elementwise quotient of two vectors
	template<typename L, typename R>
	std::vector<L> VectorQuot(std::vector<L> left, std::vector<R> right)
	{
		return VectorMap(left, right, std::divides<L>());
	}

	// Return quotient of vector and scalar
	template<typename L, typename R>
	std::vector<L> ScalarQuot(std::vector<L> left, R right)
	{
		return ScalarMap(left, right, std::divides<L>());
	}
}

#endif