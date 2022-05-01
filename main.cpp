#include <iostream>
#include <cmath>
#include <iomanip>
#include "equationSolver.h"


// Equation: e^(-x-1) + x^2 + 2x - 1 = 0.
constexpr double default_func(double x) {
    return exp(-x-1) + pow(x,2) + 2*x - 1;
}

// Equation: x = (-e^(-x-1) - x^2 + 1)/2.
constexpr double funcForSimpleIterationMethod(double x) {
    return (-exp(-x-1) - pow(x,2) + 1)/2;
}



int main() {
    equationSolver solver;
    std::cout << "Enter the left and right limits:\n";
    double left=0,right=0;
    std::cin >> left >> right;

    try {
        std::cout << std::setprecision(20) << solver.solveEquationDichotomyMethod(default_func, left, right)
        << "\n"
        << solver.solveEquationRelaxationMethod(default_func, 0.5, 1.0)
        << "\n"
        << solver.solveEquationSimpleIteration(funcForSimpleIterationMethod);
    }catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }

}
