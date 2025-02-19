#!/usr/bin/python3

"""
colorspaces.py - conversions between colorspaces.

Author: Ethan Dibble
"""

import numpy as np

def rgb_to_xyz(rgb):
    # sRGB to XYZ conversion matrix
    M = np.array([[0.4124, 0.3576, 0.1805],
                  [0.2126, 0.7151, 0.0721],
                  [0.0193, 0.1192, 0.9505]])

    return np.dot(M, rgb).tolist()

def xyz_to_rgb(xyz):
    M_inv = np.array([[ 3.2408, -1.5375, -0.4988],
                      [-0.9691,  1.8761,  0.0417],
                      [ 0.0557, -0.2041,  1.0570]])

    return np.clip(np.dot(M_inv, xyz), 0, 1).tolist()

def xyz_to_lab(xyz):
    lab = np.zeros(3)
    X = xyz[0] / 0.950455
    Y = xyz[1] / 1.0
    Z = xyz[2] / 1.088753
    f = lambda t : t**(1 / 3) if t > 0.008856 else 7.787 * t + (16 / 116)

    lab[0] = 116 * f(Y) - 16 if Y > 0.008856 else 903.3 * Y
    lab[1] = 500 * (f(X) - f(Y))
    lab[2] = 200 * (f(Y) - f(Z))

    return lab.tolist()


def lerp(colorStart, colorEnd, u):
    return (1 - u) * colorStart + u * colorEnd

if __name__ == "__main__":
    colorStart = np.array([0.5, 0, 0])
    colorEnd = np.array([1, 1, 1])

    print(f"{'sRGB':24}", 'L*a*b*')
    print('-' * 70)
    for u in [0, 0.25, 0.5, 0.75, 1]:
        color = lerp(colorStart, colorEnd, u)
        print(f"{np.array_str(color):20}", '\t', xyz_to_lab(rgb_to_xyz(color)))

    for i in range(1):
        r, g, b = i, 255 - i, 128  # Example gradient logic
        print(f"\x1b[38;2;{r};{g};{b}m█\x1b[0m", end="")
