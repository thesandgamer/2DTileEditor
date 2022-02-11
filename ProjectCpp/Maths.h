#pragma once
#include "raylib.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

namespace Maths
{
    Vector2 ClampValue(Vector2 value, Vector2 min, Vector2 max)
    {
        Vector2 result = value;
        result.x = (result.x > max.x) ? max.x : result.x;
        result.x = (result.x < min.x) ? min.x : result.x;
        result.y = (result.y > max.y) ? max.y : result.y;
        result.y = (result.y < min.y) ? min.y : result.y;
        return result;
    }

}