/*
 *  Ethan Dibble
 *
 *  Color Space Interpolation.
 */

#pragma once

#include "colorspaces.hpp"

namespace color
{
    namespace rgb
    {
        rgb_t lerp (const rgb_t &start, const rgb_t &end, float t)
        {
            t = clamp(t); // [0.0, 1.0]
            return start + t * (end - start);
        }
    }

    namespace gray { using rgb::lerp; }

    namespace xyz
    {
        rgb_t lerp (const rgb_t &start, const rgb_t &end, float t)
        {
            return start + t * (end - start);
        }
    }

    namespace lab {}
}
