#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class GoldenSection : public OptimizerInterface::ISegmentAlgo
		{
			SetOfPoints<4, PointVal<1>> AuxPoints;
			double phi;
			double resphi;
		public:
			GoldenSection(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints) :
				OptimizerInterface::ISegmentAlgo{ f_pointer, std::move(setOfPoints) }
			{
				phi = (1 + std::sqrt(5)) / 2;
				resphi = 2 - phi;

				AuxPoints[0] = State.GuessDomain().Points()[0];
				AuxPoints[3] = State.GuessDomain().Points()[1];

				Point<1> x1{ AuxPoints[0].P[0] + resphi * (AuxPoints[3].P[0] - AuxPoints[0].P[0]) };
				AuxPoints[1] = PointVal{ x1, f->operator()(x1) };

				Point<1> x2{ AuxPoints[3].P[0] - resphi * (AuxPoints[3].P[0] - AuxPoints[0].P[0]) };
				AuxPoints[2] = PointVal{ x2, f->operator()(x2) };

			}
		public:
			virtual PointVal<1> Proceed() override
			{
				if (AuxPoints[1].Val < AuxPoints[2].Val) {
					AuxPoints[3] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[1];

					Point<1> x1{ AuxPoints[0].P[0] + resphi * (AuxPoints[3].P[0] - AuxPoints[0].P[0]) };
					AuxPoints[1] = PointVal{ x1, f->operator()(x1) };
				}
				else {
					AuxPoints[0] = AuxPoints[1];
					AuxPoints[1] = AuxPoints[2];

					Point<1> x2{ AuxPoints[3].P[0] - resphi * (AuxPoints[3].P[0] - AuxPoints[0].P[0]) };
					AuxPoints[2] = PointVal{ x2, f->operator()(x2) };
				}
				State.UpdateDomain({ AuxPoints[0], AuxPoints[3] });
				return State.Guess();
			}
		};
	} // Optimizer
} // OptLib
