/* vim: set filetype=cpp : */

/*
 *  Ethan Dibble
 *
 *  Linear gradient.
 */

#include <vector>
#include "colorspaces.hpp"

// Always convert to rgb_t because it only makes sense for displaying
template<class COLOR_T>
std::vector<color::rgb_t>
linear_gradient(
        COLOR_T &start,
        COLOR_T &end,
        int n_samples,
        color::rgb_t (*to_rgb)(const COLOR_T&)
    )
{
    std::vector<rgb_t> gradient;

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
