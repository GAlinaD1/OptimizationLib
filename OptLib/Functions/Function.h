#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteFunc
	{
		/// <summary>
		/// Templated paraboloid in dim-D space with gradient and hessian
		/// </summary>
		template<size_t dim>
		class Paraboloid : public FuncInterface::IFuncWithHess<dim>
		{
		protected:
			SetOfPoints<dim, Point<dim>> hessian, coef_matrix;
		public:
			Paraboloid(const SetOfPoints<dim, Point<dim>> coefs) : hessian{ coefs }, coef_matrix{coefs}
			{
				// transform coefficientts to hessian symmetric matrix
				// make the hessian matrix symmetric
				for (int i = 0; i < dim; i++)
				{
					hessian[i][i] *= 2;
					for (int j = i + 1; j < dim; j++)
					{
						double temp = (hessian[i][j] + hessian[j][i]);
						hessian[i][j] = temp;
						hessian[j][i] = temp;
					}
				}
				// make the coefficient matrix symmetric
				for (int i = 0; i < dim; i++)
					for (int j = i + 1; j < dim; j++)
					{
						double temp = (coef_matrix[i][j] + coef_matrix[j][i]) / 2.0;
						coef_matrix[i][j] = temp;
						coef_matrix[j][i] = temp;
					}
#ifdef DEBUG_LIB
				std::cout << "Paraboloid in " << dim << "D space with Hessian "
					<< hessian << " has been instantiated\n";
				std::cout << "Its coefficient matrix A for xAx is " << CoefMatrix() << '\n';
#endif // DEBUG_LIB
			}

			virtual double operator()(const Point<dim>& x) const override
			{
				double result = 0.0;
				for (int i = 0; i < dim; i++)
				{
					result += hessian[i][i] / 2.0 * x[i] * x[i];
					for (int j = i + 1; j < dim; j++)
						result += hessian[i][j] * x[i] * x[j];
				}
				return result;
			}

			virtual Point<dim> grad(const Point<dim>& x) const override
			{
				Point<dim> result{};
				for (int i = 0; i < dim; i++)
					result[i] = 2*dot_product(x, CoefMatrixRow(i));
				return result;
			}

			virtual SetOfPoints<dim, Point<dim>> hess(const Point<dim>& x) const override
			{
				return hessian;
			}

		protected:
			SetOfPoints<dim, Point<dim>> CoefMatrix() const
			{
				return coef_matrix;
			}
			const Point<dim>& CoefMatrixRow(int i) const
			{
				return CoefMatrix()[i];
			}
		};


		/// <summary>
		/// Paraboloid in 2D space, without hessian
		/// </summary>
		using Paraboloid2D = Paraboloid<2>;


		/// <summary>
		/// Parabola in 1D without hessian. mostly a test function...
		/// </summary>
		class Function : public FuncInterface::IFuncWithGrad<1>
		{
		public:
			Function()
			{
#ifdef DEBUG_LIB
				std::cout << "Parabola  x^2  has been instantiated.\n";
#endif // DEBUG_LIB
			}

		public:

			virtual double operator () (const Point<1>& x) const override
			{
				return x[0] * x[0];
			}

			virtual std::array<double, 1> grad(const Point<1>& x) const override
			{
				return std::array < double, 1>{2 * x[0]};
			}
		};

		/// <summary>
		/// Adding a hessian to a parabola
		/// </summary>
		class FunctionWithHess : public Function, public FuncInterface::IHess<1>
		{
		public:
			virtual SetOfPoints<1, Point<1>> hess(const Point<1>& x) const override
			{
				return SetOfPoints<1, Point<1>>{ { {2}} };
			}
		};

		class Function2DWithHessNoGrad : public FuncInterface::IFunc<2>, public FuncInterface::IHess<2>
		{
		public:
			Function2DWithHessNoGrad()
			{
#ifdef DEBUG_LIB
				std::cout << "Parabola  x^2 + y^2  has been instantiated. No gradient is defined.\n";
#endif // DEBUG_LIB

			}
			virtual double operator () (const Point<2>& x) const override
			{
				return x[0] * x[0] + x[1] * x[1];
			}
			virtual SetOfPoints<2,Point<2>> hess(const Point<2>& x) const override
			{
				return SetOfPoints<2, Point<2>>{ { { {2.0, 0.0} }, { { 0.0, 2.0 }}} };
			}
		};




		template <size_t dim>
		class FuncAlongGradDirection : public FuncInterface::IFuncWithGrad<1>
		{
		public:
			FuncAlongGradDirection(FuncInterface::IFuncWithGrad<dim>* f_pointer, const Point<dim>& x0_) noexcept :
				x0{ x0_ }, grad0{ f_pointer->grad(x0_) }, f{ f_pointer }{}

			virtual double operator () (const Point<1>& gamma) const override
			{
				return f->operator()(x0 - grad0 * gamma[0]);
			}

			virtual Point<1> grad(const Point<1>& gamma) const override
			{
				Point<dim> gr = f->grad(x0 - grad0 * gamma[0]);

				return Point<1>{-dot_product(gr, grad0)};
			}

		protected:
			Point<dim> x0;
			Point<dim> grad0;

			FuncInterface::IFuncWithGrad<dim>*  f;// function to optimize
		};

		template<size_t dimX, size_t dimP>
		class FuncWithParams : public FuncInterface::IFunc<dimX>
		{
		protected:
			FuncParamInterface::IFuncParam<dimX, dimP>* f;
			Point<dimP> ParamVals;
		public:
			FuncWithParams(Point<dimP>&& pVals, FuncParamInterface::IFuncParam<dimX, dimP>* f_pointer) : f{ f_pointer }, ParamVals{ std::move(pVals) } {}

			double operator()(const Point<dimX>& x)  const override
			{
				return f->operator()(x, ParamVals);
			}
		};
	} // ConcreteFuncs

} // OptLib