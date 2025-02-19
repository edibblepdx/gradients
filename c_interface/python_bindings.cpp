/*
 *  Ethan Dibble
 *
 *  Implement C++ bindings for Python color math.
 */

#include "colorspaces.hpp"

// Convert data values from C++ to Python,
// Perform a function call to a Python interface routine using the converted values, and
// Convert the data values from the call from Python to C++.

#define PYTHONFILE "colorspaces"

PyObject*
call_python(const char *func_name, const float *input, const int size) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    pName = PyUnicode_DecodeFSDefault(PYTHONFILE);
    /* Error checking of pName left out */
    if (!pName) {
        PyErr_Print();
        fprintf(stderr, "Failed to decode module name\n");
        return NULL;
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, func_name);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            pValue = PyList_New(size);
            for (i = 0; i < size; ++i) {
                /* PyObject double reference stolen here: */
                PyList_SetItem(pValue, i, PyFloat_FromDouble(input[i]));
            }
            /* pValue reference stolen here: */
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
