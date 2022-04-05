#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteReg
	{

		/// <summary>
		/// Operations for linear regression
		/// </summary>
		struct Linear
		{
			static double zero() { return 0.0; }
			double operator()(double prev, double y, double f) const { return prev + std::pow(f - y, 2.0); }
		};

		/// <summary>
		/// Operations for logistic regression
		/// </summary>
		struct Logistic
		{
			static double zero() { return 1.0; }
			double operator()  (double prev, double y, double f) const
			{
				double term;
				if (y == 1.0) term = Sigmoid(f);
				else term = 1 - Sigmoid(f);
				return prev * term;
			}
		private:
			static double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }
		};


		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLinear = RegInterface::ILikelihoodFunc<dimX, dimP, func, funcP, Linear>;

		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLogistic = RegInterface::ILikelihoodFunc<dimX, dimP, func, funcP, Logistic>;
		
	} // ConcreteReg
} // OptLib