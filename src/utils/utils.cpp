#include "utils.h"

bool floateq(float a, float b)
{
return std::abs(a - b) < EQEPSILON;
}