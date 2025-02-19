/*
 *  Ethan Dibble
 *
 *  Define color types and C++ bindings for Python color math.
 *  These data classes all contain 3 floats, but colors that
 *  are in different spaces are inherently different types.
 */

#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <array>

/* Define color types */
namespace colors
{
    class COLOR {
    public:
        COLOR()             : alpha{1.f} {}
        COLOR(float alpha)  : alpha{clamp(alpha)} {}

        static float clamp(float v) { return (v < 0.f) ? 0.f : (v > 1.f) ? 1.f : v; }

        virtual std::array<float, 3> toArray()              = 0;
        virtual void fromArray(std::array<float, 3> arr)    = 0;

        float alpha;
    };

    class RGB: public COLOR {
    public:
        RGB() = default;
        RGB(float r, float g, float b)              : r{clamp(r)}, g{clamp(g)}, b{clamp(b)} {}
        RGB(float r, float g, float b, float alpha) : COLOR(alpha), r{clamp(r)}, g{clamp(g)}, b{clamp(b)} {}

        std::array<float, 3> toArray()              override { return {r, g, b}; }
        void fromArray(std::array<float, 3> arr)    override { r=clamp(arr[0]), g=clamp(arr[1]), b=clamp(arr[2]); }

        float r{0.f}, g{0.f}, b{0.f};
    };

    class XYZ: public COLOR {
    public:
        XYZ() = default;
        XYZ(float x, float y, float z)              : x{x}, y{y}, z{z} {}
        XYZ(float x, float y, float z, float alpha) : COLOR(alpha), x{x}, y{y}, z{z} {}

        std::array<float, 3> toArray()              override { return {x, y, z}; }
        void fromArray(std::array<float, 3> arr)    override { x=clamp(arr[0]), y=clamp(arr[1]), z=clamp(arr[2]); }

        float x{0.f}, y{0.f}, z{0.f};
    };

    class LAB: public COLOR {
    public:
        LAB() = default;
        LAB(float l, float a, float b)              : l{l}, a{a}, b{b} {}
        LAB(float l, float a, float b, float alpha) : COLOR(alpha), l{l}, a{a}, b{b} {}

        std::array<float, 3> toArray()              override { return {l, a, b}; }
        void fromArray(std::array<float, 3> arr)    override { l=clamp(arr[0]), a=clamp(arr[1]), b=clamp(arr[2]); }

        float l{0.f}, a{0.f}, b{0.f};
    };
}

PyObject* call_python(const char *func_name, const float *input, const int size);

template<class IN, class OUT>
OUT convert(const char *func_name, IN input) {
    float *in = input.toArray().data();
    PyObject *pResult = call_python(func_name, in, 3);

    OUT output;
    if (pResult && PyList_Check(pResult)) {
        output.fromArray({
            static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 0))),
            static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 1))),
            static_cast<float>(PyFloat_AsDouble(PyList_GetItem(pResult, 2))),
        });
    }
    if (PyErr_Occurred()) {
        PyErr_Print();
        fprintf(stderr, "Failed to parse return value\n");
    }
    Py_DECREF(pResult);

    return output;
}
