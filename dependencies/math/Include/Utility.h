#pragma once
#include "DLL.h"

#define _PI 3.14159265358979323846
#define _2PI (_PI*2)
#define _PI_OVER_180 0.01745329		// 1 radian
#define _180_OVER_PI 57.29578		 

template <typename T>
LIB_API T degToRad(T degrees);

template <typename T>
LIB_API T radToDeg(T radians);

template <typename T>
LIB_API T LinearHalf(T x);