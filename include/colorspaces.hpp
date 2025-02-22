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

static inline constexpr float clamp(float v) { return (v < 0.f) ? 0.f : (v > 1.f) ? 1.f : v; }

/* Define color types */
namespace color
{
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

    struct gray_t: public color_t
    {
        gray_t() = default;
        gray_t(const float x, const float y, const float z) : color_t(clamp(x), clamp(y), clamp(z)) {}
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

    template<class T>
    constexpr T operator + (const T &c1, const T &c2)
    {
        return T { c1.x + c2.x, c1.y + c2.y, c1.z + c2.z };
    }

    template<class T>
    constexpr T operator - (const T &c1, const T &c2)
    {
        return T { c1.x - c2.x, c1.y - c2.y, c1.z - c2.z };
    }
}

/*
// linearly interpolate a gradient in a given space and convert if chosen
// in most cases, I will interpolate in one space and convert samples to RGB to display
// please compiler optimize my return value
template<class IN, class OUT = IN>
std::vector<OUT> linear_gradient(IN start, IN end, int n_samples, char *conversion)
{
    std::vector<OUT> gradient;

    float step_X = 0.f;
    float step_Y = 0.f;
    float step_Z = 0.f;

    // standard lerp
    for (int i = 0; i < n_samples; ++i) {
        if (conversion) {
            convert(conversion, input);
        }
    }

    return gradient;
}
*/
