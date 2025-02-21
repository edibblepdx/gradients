/*
 *  Ethan Dibble
 *
 *  Header file for C++ bindings for Python color math.
 */

#pragma once

#include <Python.h>
#include "colorspaces.hpp"

#define PYTHONFILE "colorspaces"

namespace color
{
    xyz_t rgb_to_xyz( const rgb_t& );
    rgb_t xyz_to_rgb( const xyz_t& );

    lab_t xyz_to_lab( const xyz_t& );

}
