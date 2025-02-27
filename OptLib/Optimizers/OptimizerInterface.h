#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace OptimizerInterface
	{
		template<size_t dim, typename func, typename state>
		class IOptimizerAlgorithm
		{
		public:
			IOptimizerAlgorithm(func* f_pointer, SetOfPoints<dim + 1, Point<dim>>&& setOfPoints) :
				f{ f_pointer }, State{ std::move(setOfPoints), f_pointer }{}

			virtual Point<dim> CurrentGuess() const { return State.Guess(); }; // returns current guess
			PointVal<dim> CurrentPointAndVal() // returns the guess and the function value
			{
				Point<dim> p = CurrentGuess();
				return PointVal<dim>{std::move(p), f->operator()(p)};
			}

			virtual bool IsConverged(double abs_tol, double rel_tol) const
			{
				return State.IsConverged(abs_tol, rel_tol);
			}

			virtual PointVal<dim> Proceed() = 0; // continue to next guess

		protected:
			const func* f; // function to optimize
			state State; // state of the method
		};


		template<size_t dim, typename stateT>
		class ISimplexAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, stateT>
		{
		public:
			ISimplexAlgo(
				FuncInterface::IFunc<dim>* f_pointer,
				SetOfPoints<dim + 1, Point<dim>>&& setOfPoints)
				:
				IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, stateT>{ f_pointer, std::move(setOfPoints) } {}
			const auto& GuessDomain() const { return this->State.GuessDomain(); } // unique for direct methods
		};


		/// <summary>
		/// Direct optimization in N-dim space with simplex points sorting according to f(x)
		/// </summary>
		template<size_t dim>
		using IDirectAlgo = ISimplexAlgo<dim, ConcreteState::StateDirect<dim>>;

		/// <summary>
		/// Algorithms for 1D optimization on a segment. Segment [x1; x2], where it is guaranteed that x1 < x2
		/// </summary>
		class ISegmentAlgo : public ISimplexAlgo<1, ConcreteState::StateSegment>
		{
		public:
			ISegmentAlgo(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints) :
				ISimplexAlgo<1, ConcreteState::StateSegment>{ f_pointer, std::move(OrderPointsInSegment(setOfPoints)) } {}
		protected:
			SetOfPoints<2, Point<1>> OrderPointsInSegment(SetOfPoints<2, Point<1>>& setOfPoints)
			{
				if (setOfPoints[0][0] > setOfPoints[1][0])
					std::swap(setOfPoints[0], setOfPoints[1]);
				return setOfPoints;
			}
		};

		template<size_t dim>
		class IGradAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithGrad<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<size_t dim>
		class IHessAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<size_t dim>
		class IStochasticAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StateStochastic<dim>>
		{

		};
	} // OptimizerInterface
} // OptLib