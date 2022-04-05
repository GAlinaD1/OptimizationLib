#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		class testOptimizer
		{
		public:
			static void testBicection()
			{
				std::cout << "******Bicection test start*****\n";
				ConcreteOptimizer::Bisection Algo{ new ConcreteFunc::FunctionWithHess{}, {{{-2}, {5}}} };
				std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					Algo.Proceed();
					std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				}
				std::cout << "******Bicection test end*******\n\n";
			}
			
			static void testDichotomy()
			{
				std::cout << "******Dichotomy test start*****\n";
				ConcreteOptimizer::Dichotomy Algo{ new ConcreteFunc::FunctionWithHess{}, {{{-2}, {5}}} };
				std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					Algo.Proceed();
					std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				}
				std::cout << "******Dichotomy test end*******\n\n";
			}
			static void testOverallOptimizerWithDichotomy()
			{
				std::cout << "******OverallOptimizer With Dichotomy test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteOptimizer::Dichotomy Algo{ &f, {{{-2}, {5}}} };
				Optimizer<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo, prm };

				std::cout << "Optimization with Dichotomy started...\n";
				opt.Optimize();
				std::cout << "Optimization with Dichotomy finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';

				std::cout << "******OverallOptimizer With Dichotomy test end*****\n";
			}

			static void testOverallOptimizerWithBicection()
			{
				std::cout << "******OverallOptimizer With Bicection test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteOptimizer::Bisection Algo{ &f, {{{-2}, {5}}} };
				Optimizer<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo, prm };

				std::cout << "Optimization with Bicection started...\n";
				opt.Optimize();
				std::cout << "Optimization with Bicection finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';

				std::cout << "******OverallOptimizer With Bicection test end*******\n\n";
			}

			static void testGoldenSection()
			{
				std::cout << "******GoldenSection test start*****\n";
				ConcreteOptimizer::GoldenSection Algo{ new ConcreteFunc::FunctionWithHess{}, {{{-2}, {5}}} };
				std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					Algo.Proceed();
					std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
				}
				std::cout << "******GoldenSection test end*******\n\n";
			}

			static void testOverallOptimizer_WithGoldenSection()
			{
				std::cout << "******OverallOptimizer With GoldenSection test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteOptimizer::GoldenSection Algo{ &f, {{{-2}, {5}}} };
				Optimizer<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo, prm };

				std::cout << "Optimization with GoldenSection started...\n";
				opt.Optimize();
				std::cout << "Optimization with GoldenSection finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';

				std::cout << "******OverallOptimizer With GoldenSection test end*******\n\n";
			}
			/*static void testDirect1DFuncAlongGrad()
			{
				std::cout << "******Optimization test start*****\n";
				FuncInterface::IFunc<1>* f = new ConcreteFunc::FunctionWithHess();
				ConcreteState::StateSimplex<1>* state = new ConcreteState::StateSimplex(Simplex<2, 1>{ { {-2}, { 5 }}});
				OptimizerInterface::IDirectAlgo<1>* algo = new ConcreteOptimizer::Bicection(f, state);

				Optimizer<1> Optimizer{ algo, OptimizerParams{0.001, 0.001, 100} };

				std::cout << "Initial simplex is:\n" << "  " << algo->CurSimplex() << "\n";
				Optimizer.Optimize();
				std::cout << "Final simplex is:\n" << "  " << algo->CurSimplex() << "\n";
				std::cout << "Guess value is:\n" << "  " << Optimizer.CurrentGuess() << "\n";
				std::cout << "Iter count is:\n" << "  " << Optimizer.cur_iter_count() << "\n";
				std::cout << "****** Optimization test end*******\n\n";
			}*/
			static void testGrid()
			{
				std::cout << "******Grid test start*****\n";
				ConcreteOptimizer::Grid Algo { new ConcreteFunc::FunctionWithHess{}, {{{-15}, {25}}} , 100};
				std::cout << "Simplex is:\n" << "  " << Algo.GuessDomain() << "\n" << "n = "<< Algo.n<<"\n";
				std::cout<<"Result is: "<< Algo.Proceed() << "\n";
				std::cout << "******Grid test end*******\n\n";
			}
			static void testOverallOptimizerWithGrid()
			{
				std::cout << "******OverallOptimizer With Grid test start*****\n";

				ConcreteFunc::Function f{};
				ConcreteOptimizer::Grid Algo{ &f, {{{-15}, {25}}} ,5};
				Optimizer1Step<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo};

				std::cout << "Optimization with Grid started...\n";
				std::cout << "Optimization with Grid finalized.\n";
				std::cout << "Final guess is x = " <<  opt.Optimize() << '\n';
				std::cout << "******OverallOptimizer With Grid test end*******\n\n";
			}
		};

	} // UnitTests
} // OptLib
