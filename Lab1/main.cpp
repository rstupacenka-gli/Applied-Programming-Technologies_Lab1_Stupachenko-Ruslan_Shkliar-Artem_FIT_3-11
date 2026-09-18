#include <iostream>
#include <memory>
#include <Windows.h> 
#include "shared_types.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
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

    std::cout << "Метод Гауса (Студент А)\n";
    for (std::size_t i = 0; i < valueA.size(); ++i)
    {
        std::cout << "  x[" << i << "] = " << valueA[i] << '\n';
    }
    std::cout << "Норма нев'язки:: " << residualA << '\n';
    std::cout << "Час виконання:: " << timeA << " ms\n";

    return 0;
}