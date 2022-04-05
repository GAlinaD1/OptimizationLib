#pragma once

#ifdef __AVX__
#include <immintrin.h>
#else
//#warning No AVX support - will not compile
#endif


#define DEBUG_LIB

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <numeric>
#include <tuple>
#include <iterator>
#include <immintrin.h>
#include <cmath>

#include "OptLib/AuxMethods/Simplex.h"

#include "OptLib/Functions/FunctionInterface.h"
#include "OptLib/Functions/Function.h"

#include "OptLib/States/StateInterface.h"
#include "OptLib/States/State.h"

#include "OptLib/Optimizers/OptimizerInterface.h"
#include "OptLib/Optimizers/OneDim/Bisection.h"
#include "OptLib/Optimizers/OverallOptimizer.h"
#include "OptLib/Optimizers/OneDim/Grid.h"
#include "OptLib/Optimizers/OneDim/GoldenSection.h"
