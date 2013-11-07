#include "StdAfx.h"
#include "Vector.h"

bool operator <= (double value, const Math::CTolerance& tolerance)
{
    return value < tolerance.ToleranceValue;
}
bool operator > (double value, const Math::CTolerance& tolerance)
{
    return value > tolerance.ToleranceValue;
}
bool operator >= (double value, const Math::CTolerance& tolerance)
{
    return value > -tolerance.ToleranceValue;
}