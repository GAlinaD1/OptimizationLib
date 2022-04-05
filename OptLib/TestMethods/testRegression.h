#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		struct testLikelihood
		{
			static void testLikelihoodLinear()
			{
				std::cout << "******LikelihoodLinear test start*****\n";

				Point<2> a{ 1.0,0.0 };
				auto* f = new OptLib::FuncParamInterface::LinearFunc();

				 auto data = GenerateDataSet<1, 2>(a, f );
				 auto data1 = data;

				ConcreteReg::LikelihoodLinear<1, 2, FuncInterface::IFunc, FuncParamInterface::IFuncParam> L{std::move(data), f};
				std::cout << std::sqrt(L(a)/data1.size()) << "  " << '\n';

				std::cout << "******LikelihoodLinear test end*******\n\n";
			}


			template<size_t dimX, size_t dimP>
			static RegInterface::DataSet<dimX> GenerateDataSet(const Point<dimP>& a, const FuncParamInterface::IFuncParam<dimX, dimP>* f)
			{
				std::default_random_engine generatorX;
				std::uniform_real_distribution<double> Xdistrib(0.0, 1.0); // generate x-values

				double eps = 0.01; // small noise to y-values
				std::default_random_engine generatorY;
				std::uniform_real_distribution<double> Ynoise(-eps, eps); // generate x-values

				int nrolls = 101; // number of correlation points

				RegInterface::DataSet<dimX> out;

				for (int i = 0; i < nrolls; ++i) {
					Point<dimX> x;
					for (int k = 0; k < dimX; k++)
						x[k] = Xdistrib(generatorX);
					double val = f->operator()(x, a) + Ynoise(generatorY);
					out.emplace_back(x, val);
				}

				return out;


			}

		};




		class testRegression
		{

		};

	} // UnitTests
} // OptLib