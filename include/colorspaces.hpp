/*
 *  Ethan Dibble
 *
 *  Define color types and C++ bindings for Python color math.
 *  These data structs all contain 3 floats, but colors that
 *  are in different spaces are inherently different types.
 *
 *  All colors channels are accessed with x,y,z for all types
 *  for simplicity. No alpha channel because it's not needed.
 */

#pragma once

/* Define color types */
namespace color
{
    static inline constexpr float clamp(float v) { return (v < 0.f) ? 0.f : (v > 1.f) ? 1.f : v; }

    ////////////////////////////////////////////////////////////////////////////

    struct color_t
    {
        color_t() = default;
        color_t(const float x, const float y, const float z) : x{x}, y{y}, z{z} {}

        float x{0.f}, y{0.f}, z{0.f};
    };

    struct rgb_t: public color_t
    {
        rgb_t() = default;
        rgb_t(const float x, const float y, const float z) : color_t(clamp(x), clamp(y), clamp(z)) {}
    };

    struct xyz_t: public color_t
    {
        xyz_t() = default;
        xyz_t(const float x, const float y, const float z) : color_t(x, y, z) {}
    };

    struct lab_t: public color_t
    {
        lab_t() = default;
        lab_t(const float x, const float y, const float z) : color_t(x, y, z) {}
    };

    struct luv_t: public color_t
    {
        luv_t() = default;
        luv_t(const float x, const float y, const float z) : color_t(x, y, z) {}
    };

    struct hsv_t: public color_t
    {
        hsv_t() = default;
        hsv_t(const float x, const float y, const float z) : color_t(x, y, z) {}
    };

    struct hls_t: public color_t
    {
        hls_t() = default;
        hls_t(const float x, const float y, const float z) : color_t(x, y, z) {}
    };

    ////////////////////////////////////////////////////////////////////////////

    // addition
    template<class T>
    constexpr T operator + (const T &v1, const T &v2)
    {
        return T { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    }

    // subtraction
    template<class T>
    constexpr T operator - (const T &v1, const T &v2)
    {
        return T { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    }

    // left-hand scalar multiplication
    template<class T>
    constexpr T operator * (float s, const T &v)
    {
        return T { s * v.x, s * v.y, s * v.z };
    }

    // right-hand scalar multiplication
    template<class T>
    constexpr T operator * (const T &v, float s)
    {
        return T { s * v.x, s * v.y, s * v.z };
    }
}