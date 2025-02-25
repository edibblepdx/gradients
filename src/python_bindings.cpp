/*
 *  Ethan Dibble
 *
 *  Implementation of C++ bindings for Python color math.
 */

#include "python_bindings.hpp"
#include "python_bindings.tpp"

#define PYTHONFILE "colorspaces"

namespace color
{

static PyObject*
call_python( const char *func_name, const color_t *input )
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    pName = PyUnicode_DecodeFSDefault(PYTHONFILE);
    if (!pName) {
        PyErr_Print();
        fprintf(stderr, "Failed to decode module name\n");
        return NULL;
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, func_name);

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            pValue = PyList_New(3);

            PyList_SetItem(pValue, 0, PyFloat_FromDouble(input->x));
            PyList_SetItem(pValue, 1, PyFloat_FromDouble(input->y));
            PyList_SetItem(pValue, 2, PyFloat_FromDouble(input->z));

            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue == NULL) {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return NULL;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", func_name);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", PYTHONFILE);
        return NULL;
    }
    return pValue;
}

// Convert data values from C++ to Python,
// Perform a function call to a Python interface routine using the converted values, and
// Convert the data values from the call from Python to C++.

rgb_t rgb_grayscale( const rgb_t& c ) { return parse_python<rgb_t>(call_python("rgb_grayscale", &c)); }

////////////////////////////////////////////////////////////////////////////////

xyz_t rgb_to_xyz( const rgb_t& c ) { return parse_python<xyz_t>(call_python("rgb_to_xyz", &c)); }
hsv_t rgb_to_hsv( const rgb_t& c ) { return parse_python<hsv_t>(call_python("rgb_to_hsv", &c)); }
hls_t rgb_to_hls( const rgb_t& c ) { return parse_python<hls_t>(call_python("rgb_to_hls", &c)); }

////////////////////////////////////////////////////////////////////////////////

rgb_t xyz_to_rgb( const xyz_t& c ) { return parse_python<rgb_t>(call_python("xyz_to_rgb", &c)); }
lab_t xyz_to_lab( const xyz_t& c ) { return parse_python<lab_t>(call_python("xyz_to_lab", &c)); }
luv_t xyz_to_luv( const xyz_t& c ) { return parse_python<luv_t>(call_python("xyz_to_luv", &c)); }

////////////////////////////////////////////////////////////////////////////////
}
