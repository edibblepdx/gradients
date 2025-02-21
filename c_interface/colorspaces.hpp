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
#define PY_SSIZE_T_CLEAN

static inline float clamp(float v) { return (v < 0.f) ? 0.f : (v > 1.f) ? 1.f : v; }

/* Define color types */
namespace color
{
    struct color_t
    {
        color_t() = default;
        color_t(float x, float y, float z) : x{x}, y{y}, z{z} {}

        float x{0.f}, y{0.f}, z{0.f};
    };

    struct rgb_t: public color_t
    {
        rgb_t() = default;
        rgb_t(float x, float y, float z) : color_t(clamp(x), clamp(y), clamp(z)) {}
    };

    struct xyz_t: public color_t
    {
        xyz_t() = default;
        xyz_t(float x, float y, float z) : color_t(x, y, z) {}
    };

    struct lab_t: public color_t
    {
        lab_t() = default;
        lab_t(float x, float y, float z) : color_t(x, y, z) {}
    };
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
