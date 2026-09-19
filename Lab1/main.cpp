#include <iostream>
#include <memory>
#include "shared_types.h"

int main()
{
    auto data = std::make_shared<const InputData>(InputData{
        .A = {
            {4.0, 1.0, 2.0},
            {3.0, 5.0, 1.0},
            {1.0, 1.0, 3.0}},
        .b = {4.0, 7.0, 3.0},
        .epsilon = 1e-6,
        .maxIterations = 1000 });

    auto resultA = calculateA(data);
    auto [valueA, iterationsA, residualA, timeA] = *resultA;

    std::cout << "Gauss method (Student A)\n";
    for (std::size_t i = 0; i < valueA.size(); ++i)
    {
        std::cout << "  x[" << i << "] = " << valueA[i] << '\n';
    }
    std::cout << "Residual norm: " << residualA << '\n';
    std::cout << "Execution time: " << timeA << " ms\n\n";

    auto resultB = calculateB(data);
    auto [valueB, iterationsB, residualB, timeB] = *resultB;

    std::cout << "Simple iterations method (Student B)\n";
    for (std::size_t i = 0; i < valueB.size(); ++i)
    {
        std::cout << "  x[" << i << "] = " << valueB[i] << '\n';
    }
    std::cout << "Iterations: " << iterationsB << '\n';
    std::cout << "Residual norm: " << residualB << '\n';
    std::cout << "Execution time: " << timeB << " ms\n\n";

    std::cout << "Comparison\n";
    std::cout << "  Residual norm difference: " << std::abs(residualA - residualB) << '\n';
    std::cout << "  Time Gauss: " << timeA << " ms\n";
    std::cout << "  Time Iterations: " << timeB << " ms\n";

    return 0;
}