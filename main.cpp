#include "stdafx.h"

#ifdef DEBUG_LIB
	#include "OptLib/TestMethods/testSimplex.h"
	#include "OptLib/TestMethods/testFunction.h"
	#include "OptLib/TestMethods/testState.h"
	#include "OptLib/TestMethods/testOptimizer.h"
	#include "OptLib/TestMethods/testRegression.h"
#endif // DEBUG_LIB






int main()
{


#ifdef DEBUG_LIB
	// test Simplex
	OptLib::UnitTests::testSimplex::testPointOperations();
	OptLib::UnitTests::testSimplex::testSimplexVal();
	
	// test functions
	OptLib::UnitTests::testFunction::testGradient();
	OptLib::UnitTests::testFunction::testHessian();
	OptLib::UnitTests::testFunction::test2DHessian();
	OptLib::UnitTests::testFunction::test2DWithHessNoGrad();
	OptLib::UnitTests::testFunction::testParaboloid();
	OptLib::UnitTests::testFunction::testParaboloidAlongDirection();

	// test states
	OptLib::UnitTests::testState::testStateDirect();
	OptLib::UnitTests::testState::testStateSegment();
	//OptLib::UnitTests::testState::testStatePoint(); // TODO
	//OptLib::UnitTests::testState::testStateStochastic(); // TODO

	// test optimizers
	OptLib::UnitTests::testOptimizer::testBicection();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithBicection(); 
	OptLib::UnitTests::testOptimizer::testDichotomy();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithDichotomy(); 
	OptLib::UnitTests::testOptimizer::testGrid();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithGrid();
	OptLib::UnitTests::testOptimizer::testGoldenSection();
	OptLib::UnitTests::testOptimizer::testOverallOptimizer_WithGoldenSection();
	//testOptimizer::testOptimizer_();

	// test regression

//	OptLib::UnitTests::testLikelihood::GenerateDataSet<1,2>({1.0, 0.0}, new OptLib::FuncParamInterface::LinearFunc());
	OptLib::UnitTests::testLikelihood::testLikelihoodLinear();

#endif // DEBUG_LIB
}
