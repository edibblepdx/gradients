#!/usr/bin/python3

"""
colorspaces.py - conversions between colorspaces.
I use piecewise notation for clarity.

Author: Ethan Dibble

Sources for conversions:
- https://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
- https://poynton.ca/PDFs/coloureq.pdf
- https://poynton.ca/ColorFAQ.html
- https://en.wikipedia.org/wiki/SRGB
"""

from decorators import exception_handler

type Vector = list[float] # length 3

@exception_handler
def rgb_grayscale(rgb: Vector) -> Vector:
    """rgb: [0,1] -> rgb: [0,1]"""

    r, g, b = rgb
    intensity = (0.299 * r) + (0.587 * g) + (0.114 * b)

    return [intensity] * 3

@exception_handler
def rgb_to_xyz(rgb: Vector) -> Vector:
    """rgb: [0,1] -> xyz: [0,1]""" # WRONG

    # RGB to XYZ conversion matrix D65 white point
    # [0.412453, 0.357580, 0.180423]
    # [0.212671, 0.715160, 0.072169]
    # [0.019334, 0.119193, 0.950227]

    r,g,b = rgb

    x = (r * 0.412453) + (g * 0.357580) + (b * 0.180423)
    y = (r * 0.212671) + (g * 0.715160) + (b * 0.072169)
    z = (r * 0.019334) + (g * 0.119193) + (b * 0.950227)

    return [x, y, z]

@exception_handler
def rgb_to_hsv(rgb: Vector) -> Vector:
    """rgb: [0,1] -> hsv: 0≤H≤360, 0≤S≤1, 0≤V≤1"""

    r, g, b = rgb
    v_max = max(rgb)
    v_min = min(rgb)
    delta = v_max - v_min

    s = (
        0.0                            if v_max == 0.0
        else (v_max - v_min) / v_max # if v_max != 0.0
    )

    h = (
        0.0                                     if delta == 0.0
        else 60.0 * (g - b) / (delta)           if v_max == r
        else 120.0 + 60.0 * (b - r) / (delta)   if v_max == g
        else 240.0 + 60.0 * (r - g) / (delta) # if v_max == b
    )

    if h < 0:
        h = h + 360.0

    return [h, s, v_max]

@exception_handler
def rgb_to_hls(rgb: Vector) -> Vector:
    """rgb: [0,1] -> hls: 0≤H≤360, 0≤L≤1, 0≤S≤1"""

    r, g, b = rgb
    v_max = max(rgb)
    v_min = min(rgb)
    v_sum = v_max + v_min
    delta = v_max - v_min

    l = v_sum / 2.0

    s = (
        0.0                          if v_sum == 0.0 # validate behavior
        else 0.0                     if v_sum == 2.0 # validate behavior
        else delta / v_sum           if l <  0.5
        else delta / (2.0 - v_sum) # if l >= 0.5
    )

    h = (
        0.0                                     if delta == 0.0
        else 60.0 * (g - b) / (delta)           if v_max == r
        else 120.0 + 60.0 * (b - r) / (delta)   if v_max == g
        else 240.0 + 60.0 * (r - g) / (delta) # if v_max == b
    )

    if h < 0:
        h = h + 360.0

    return [h, l, s]

@exception_handler
def xyz_to_rgb(xyz: Vector) -> Vector:
    """xyz: [0,1] -> rgb: [0,1]""" # WRONG

    # inverse RGB to XYZ conversion matrix D65 white point
    # [ 3.240479, -1.53715, -0.498535]
    # [-0.969256,  1.875991, 0.041556]
    # [ 0.055648, -0.204043, 1.057311]

    x, y, z = xyz

    r = (x *  3.240479) + (y * -1.53715 ) + (z * -0.498535)
    g = (x * -0.969256) + (y *  1.875991) + (z *  0.041556)
    b = (x *  0.055648) + (y * -0.204043) + (z *  1.057311)

    return [r, g, b]

@exception_handler
def xyz_to_lab(xyz: Vector) -> Vector:
    """rgb: [0,1] -> lab: [0,1]""" # WRONG

    x, y, z = xyz
    x /= 0.950456
    z /= 1.088754

    def f(t: float) -> float:
        return (
            t ** (1 / 3)                  if t >  0.008856
            else 7.787 * t + (16 / 116) # if t <= 0.008856
        )

    l = (
        116.0 * y ** (1 / 3) - 16.0   if y >  0.008856
        else 903.3 * y              # if y <= 0.008856
    )
    # assume floating point images
    a = 500.0 * (f(x) - f(y)) # add 128 for 8-bit images
    b = 200.0 * (f(y) - f(z)) # add 128 for 8-bit images

    return [l, a, b]

@exception_handler
def xyz_to_luv(xyz: Vector) -> Vector:
    """xyz: [0,1] -> luv: 0≤L≤100, -134≤u≤220, -140≤v≤122""" # WRONG

    x, y, z = xyz

    l = (
        116.0 * y ** (1 / 3) - 16.0   if y >  0.008856
        else 903.3 * y              # if y <= 0.008856
    )
    u = 4.0 * x / (x + 15.0 * y + 3 * z)
    v = 9.0 * x / (x + 15.0 * y + 3 * z)

    u = 13.0 * l * (u - 0.19793943)
    v = 13.0 * l * (v - 0.46831096)

    return [l, u, v]

@exception_handler
def lerp(colorStart: Vector, colorEnd: Vector, t: float) -> Vector:
    return [
        (1 - t) * colorStart[0] + t * colorEnd[0],
        (1 - t) * colorStart[1] + t * colorEnd[1],
        (1 - t) * colorStart[2] + t * colorEnd[2],
    ]

if __name__ == "__main__":
    for i in range(255):
        r, g, b = i, 255 - i, 128  # Example gradient logic
        print(f"\x1b[38;2;{r};{g};{b}m█\x1b[0m", end="")
    print()
