#include "shared_types.h"

#include <chrono>
#include <cmath>
#include <stdexcept>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data)
{
    using clock = std::chrono::steady_clock;
    const auto start = clock::now();

    const std::size_t n = data->b.size();
    const std::vector<std::vector<double>>& A = data->A;
    const std::vector<double>& b = data->b;

    for (std::size_t i = 0; i < n; ++i)
    {
        if (std::abs(A[i][i]) < 1e-12)
        {
            throw std::runtime_error("Zero diagonal element, method cannot proceed");
        }
    }

    std::vector<double> x(n, 0.0);
    std::vector<double> xNext(n, 0.0);

    std::size_t iteration = 0;
    double diffNorm = 0.0;

    for (iteration = 0; iteration < data->maxIterations; ++iteration)
    {
        for (std::size_t i = 0; i < n; ++i)
        {
            double sum = b[i];
            for (std::size_t j = 0; j < n; ++j)
            {
                if (j != i)
                {
                    sum -= A[i][j] * x[j];
                }
            }
            xNext[i] = sum / A[i][i];
        }

        diffNorm = 0.0;
        for (std::size_t i = 0; i < n; ++i)
        {
            const double diff = xNext[i] - x[i];
            diffNorm += diff * diff;
        }
        diffNorm = std::sqrt(diffNorm);

        x = xNext;

        if (diffNorm < data->epsilon)
        {
            ++iteration;
            break;
        }
    }

    double residualSquares = 0.0;
    for (std::size_t i = 0; i < n; ++i)
    {
        double rowSum = 0.0;
        for (std::size_t j = 0; j < n; ++j)
        {
            rowSum += A[i][j] * x[j];
        }
        const double diff = rowSum - b[i];
        residualSquares += diff * diff;
    }

    auto result = std::make_unique<Result>();
    result->x = std::move(x);
    result->iterations = iteration;
    result->residualNorm = std::sqrt(residualSquares);

    const auto end = clock::now();
    result->timeMs = std::chrono::duration<double, std::milli>(end - start).count();
    return result;
}