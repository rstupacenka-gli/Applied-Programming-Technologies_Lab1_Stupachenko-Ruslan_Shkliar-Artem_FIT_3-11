#pragma once

#include <cstddef>
#include <memory>
#include <vector>


struct InputData
{
    std::vector<std::vector<double>> A; 
    std::vector<double> b;              
    double epsilon = 1e-6;             
    std::size_t maxIterations = 1000;   
};


struct Result
{
    std::vector<double> x;      
    std::size_t iterations = 0; 
    double residualNorm = 0.0;  
    double timeMs = 0.0;       
};


std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);