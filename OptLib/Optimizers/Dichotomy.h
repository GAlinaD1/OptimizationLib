#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class Dichotomy : public OptimizerInterface::ISegmentAlgo
		{
		public:
			Dichotomy(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints) :
				OptimizerInterface::ISegmentAlgo{ f_pointer, std::move(setOfPoints) }{}
			virtual PointVal<1> Proceed() override
			{
				PointVal<1> a = State.GuessDomain().Points()[0];
				PointVal<1> b = State.GuessDomain().Points()[1];

				Point<1> _e = (b.P - a.P) / 4;

				Point<1> x1{ GuessDomain().Mean().P - _e };
				Point<1> x2{ GuessDomain().Mean().P + _e };

				double f_x1 = f->operator()(x1);
				double f_x2 = f->operator()(x2);

				SetOfPoints<2, PointVal<1>> newSet({ {{x1, f_x1}, {b, f_x2}} });
				if (f_x1 < f_x2)
				{
					newSet[0] = a;
					newSet[1] = { x2, f_x2 };
				}
				else
				{
					std::swap(x1, x2);
					std::swap(f_x1, f_x2);
				}
				//state.UpdateDomain(newSet);
				State.UpdateDomain({ {{newSet[0]}, {newSet[1]}} });
				return State.Guess();
			}
		};
	} // ConcreteOptimizer
} // OptLib
