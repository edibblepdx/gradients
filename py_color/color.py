#!/usr/bin/python3

import numpy as np

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

def xyz(rgb):
    # sRGB to XYZ conversion matrix
    M = np.array([[0.4124, 0.3576, 0.1805],
                  [0.2126, 0.7151, 0.0721],
                  [0.0193, 0.1192, 0.9505]])

    return np.dot(M, rgb)

def lab(xyz):
    lab = np.zeros(3)
    X = xyz[0] / 0.950455
    Y = xyz[1] / 1.0
    Z = xyz[2] / 1.088753
    f = lambda t : t**(1 / 3) if t > 0.008856 else 7.787 * t + (16 / 116)

    lab[0] = 116 * f(Y) - 16 if Y > 0.008856 else 903.3 * Y
    lab[1] = 500 * (f(X) - f(Y))
    lab[2] = 200 * (f(Y) - f(Z))

    return lab

def lerp(colorStart, colorEnd, u):
    return (1 - u) * colorStart + u * colorEnd

if __name__ == "__main__":
    colorStart = np.array([0.5, 0, 0])
    colorEnd = np.array([1, 1, 1])

    print(f"{'sRGB':24}", 'L*a*b*')
    print('-' * 70)
    for u in [0, 0.25, 0.5, 0.75, 1]:
        color = lerp(colorStart, colorEnd, u)
        print(f"{np.array_str(color):20}", '\t', lab(xyz(color)))

    print(f"{bcolors.WARNING}Warning: No active frommets remain. Continue?{bcolors.ENDC}")

    for i in range(1):
        r, g, b = i, 255 - i, 128  # Example gradient logic
        print(f"\x1b[38;2;{r};{g};{b}m█\x1b[0m", end="")
