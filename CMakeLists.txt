# CMakeList.txt : CMake project for OptimizationLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OptimizationLib")

# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 17)
add_executable (OptimizationLib "main.cpp" "OptLib/TestMethods/testRegression.h" "OptLib/Functions/FuncParamInterface.h")

# TODO: Add tests and install targets if needed.
