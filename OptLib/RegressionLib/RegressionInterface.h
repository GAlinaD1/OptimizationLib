#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace RegInterface
	{
		/// <summary>
		/// Data for regression. A vector of {P, Val}
		/// </summary>
		template<size_t dimX, template<size_t dimX> typename point = PointVal>
		using DataSet = std::vector<point<dimX>>;

		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP, typename bin_op>
		class ILikelihoodFunc : public func<dimP>
		{
		protected:
			DataSet<dimX> Data;
			funcP<dimX, dimP>* f;
			bin_op op;

		public:
			ILikelihoodFunc(DataSet<dimX>&& data, FuncParamInterface::IFuncParam<dimX, dimP>* f_pointer) : Data{ std::move(data) }, f{ f_pointer } {}

			double operator() (const Point<dimP>& a) const override
			{
				double s = bin_op::zero();
				for (int i = 0; i < Data.size(); i++)
					s = op(s, Data[i].Val, f->operator()(Data[i].P, a));
				return s;
			}
		};



		/// <summary>
		/// func template --- smotthness of Likelihood function
		/// </summary>
	/*	template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		class IRegression
		{
		protected:
			ILikelihoodFunc<dimX, dimP, func, funcP> L;

		public:

			double Likelihood(const Point<dimP>& a) { return L(a); }


		};*/

	} // RegInterface
} // OptLib