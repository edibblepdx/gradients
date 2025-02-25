/*
 *  Ethan Dibble
 *
 *  Header file for C++ bindings for Python color math.
 */

#pragma once

#include <Python.h>
#include "colorspaces.hpp"

namespace color
{
    rgb_t rgb_grayscale( const rgb_t& );

    /////////////////////////////////

    xyz_t rgb_to_xyz( const rgb_t& );
    hsv_t rgb_to_hsv( const rgb_t& );
    hls_t rgb_to_hls( const rgb_t& );

    /////////////////////////////////

    rgb_t xyz_to_rgb( const xyz_t& );
    lab_t xyz_to_lab( const xyz_t& );
    luv_t xyz_to_luv( const xyz_t& );
}