#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

#define _USE_MATH_DEFINES
#include <math.h>

#define DEGREE_CONVERSION 180.0/M_PI 

inline static double degreesToRadians(double degrees)
{
    return 0.0;
}

inline static double RadiansToDegrees(double radians)
{
    return radians * DEGREE_CONVERSION;
}

#endif