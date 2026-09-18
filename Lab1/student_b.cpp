#include "shared_types.h"

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data)
{
    (void)data;
    return std::make_unique<Result>();
}