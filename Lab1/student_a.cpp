#include "shared_types.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data)
{
    using clock = std::chrono::steady_clock;
    const auto start = clock::now();

    const std::size_t n = data->b.size();
    std::vector<std::vector<double>> A = data->A;
    std::vector<double> b = data->b;

    for (std::size_t k = 0; k < n; ++k)
    {
        std::size_t pivotRow = k;
        double maxVal = std::abs(A[k][k]);
        for (std::size_t i = k + 1; i < n; ++i)
        {
            if (std::abs(A[i][k]) > maxVal)
            {
                maxVal = std::abs(A[i][k]);
                pivotRow = i;
            }
        }
        if (maxVal < 1e-12)
        {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        if (pivotRow != k)
        {
            std::swap(A[k], A[pivotRow]);
            std::swap(b[k], b[pivotRow]);
        }
        for (std::size_t i = k + 1; i < n; ++i)
        {
            const double factor = A[i][k] / A[k][k];
            for (std::size_t j = k; j < n; ++j)
            {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    std::vector<double> x(n, 0.0);
    for (std::size_t i = n; i-- > 0;)
    {
        double sum = b[i];
        for (std::size_t j = i + 1; j < n; ++j)
        {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }

    double residualSquares = 0.0;
    for (std::size_t i = 0; i < n; ++i)
    {
        double rowSum = 0.0;
        for (std::size_t j = 0; j < n; ++j)
        {
            rowSum += data->A[i][j] * x[j];
        }
        const double diff = rowSum - data->b[i];
        residualSquares += diff * diff;
    }

    auto result = std::make_unique<Result>();
    result->x = std::move(x);
    result->iterations = 0;
    result->residualNorm = std::sqrt(residualSquares);

    const auto end = clock::now();
    result->timeMs = std::chrono::duration<double, std::milli>(end - start).count();
    return result;
}