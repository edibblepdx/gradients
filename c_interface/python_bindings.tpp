template<class R_TYPE>
inline R_TYPE parse_python(PyObject *pResult)
{
    R_TYPE output{};
    if (pResult && PyList_Check(pResult)) {
        output.x = static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 0)));
        output.y = static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 1)));
        output.z = static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 2)));
    }
    if (PyErr_Occurred()) {
        PyErr_Print();
        fprintf(stderr, "Failed to parse return value\n");
    }
    Py_DECREF(pResult);

    return output;
}
