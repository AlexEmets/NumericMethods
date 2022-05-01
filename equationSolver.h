//
// Created by oleksandr.yemets on 5/1/2022.
//
#ifndef NONLINEAREQUATIONS_EQUATIONSOLVER_H
#define NONLINEAREQUATIONS_EQUATIONSOLVER_H
#include <cmath>
#include <stdexcept>



template<typename T>
using IsFloatingPoint = std::enable_if_t<std::is_floating_point_v<T>, bool>;

class equationSolver {
private:

    static char kWrongArgumentError[];


public:
    template<typename Function>
    constexpr double solveEquationDichotomyMethod(Function func,
                                         double leftEnd = std::numeric_limits<double>::min(),
                                         double rightEnd = std::numeric_limits<double>::max(),
                                         double eps = std::numeric_limits<double>::epsilon());


    template<typename Function>
    constexpr double solveEquationRelaxationMethod(Function &&func, double lambda,
                                          double firstApproach,
                                          double eps = std::numeric_limits<double>::epsilon()) noexcept;


    template<typename Function>
    constexpr double solveEquationSimpleIteration(Function &&func,
                                                       double eps = std::numeric_limits<double>::epsilon()) noexcept;

};



template<typename Function>
constexpr double equationSolver::solveEquationDichotomyMethod(Function func,
                                     double leftEnd,
                                     double rightEnd,
                                     double eps) {

    if (func(leftEnd) * func(rightEnd) > 0.0 || eps < 0) {
        throw std::logic_error(kWrongArgumentError);
    }
    while (rightEnd - leftEnd > eps) {
        double middle = (leftEnd + rightEnd) / 2.0;
        if (func(middle) * func(rightEnd) < 0.0) {
            leftEnd = middle;
        } else {
            rightEnd = middle;
        }
    }
    return (leftEnd + rightEnd) / 2.0;
}

template<typename Function>
constexpr double equationSolver::solveEquationRelaxationMethod(Function &&func, double lambda,
                                      double firstApproach,
                                      double eps) noexcept {
    eps = fabs(eps);
    double curr, next = firstApproach;
    do {
        curr = next;
        next = curr - lambda * func(curr);
    } while (fabs(next - curr) > eps);
    return next;
}


template<typename Function>
constexpr double equationSolver::solveEquationSimpleIteration(Function &&func,
                                                                   double eps) noexcept {

    eps = fabs(eps);
    double curr=0, next = func(curr);
    do {
        curr = next;
        next = func(curr);
    } while (fabs(next - curr) > eps);
    return next;
}


char equationSolver::kWrongArgumentError[] = "Wrong argument at dichotomy method: The function at the ends of\n"
                                                "the segment must take values of different signs";

#endif //NONLINEAREQUATIONS_EQUATIONSOLVER_H
