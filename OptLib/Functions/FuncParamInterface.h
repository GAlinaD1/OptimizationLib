#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace FuncParamInterface
	{
		template<size_t dimX, size_t dimP>
		class IFuncParam
		{
		public:
			virtual double operator() (const Point<dimX>& x, const Point<dimP>& a) const = 0;

			template<size_t count>
			std::array<double, count> operator() (const SetOfPoints<count, Point<dimX>>& x, const Point<dimP>& a) const
			{
				std::array<double, count> out;
				for (int i = 0; i < count; i++)
					out[i] = this->operator()(x[i], a);
				return out;
			}
		};

		template<size_t dimX, size_t dimP>
		class IFuncParamWithGrad : public IFuncParam<dimX, dimP>
		{
		public:
			virtual Point<dimX> GradX(const Point<dimX>& x, const Point<dimP>& a) const = 0;
			virtual Point<dimX> GradP(const Point<dimX>& x, const Point<dimP>& a) const = 0;
		};



		class LinearFunc : public IFuncParam<1, 2>
		{
		public:
			double operator() (const Point<1>& x, const Point<2>& a) const override
			{
				return x[0] * a[0] + a[1];
			}
		};



	} // FuncParamInterface
} // OptLib