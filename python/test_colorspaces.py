#!/usr/bin/python3

import unittest
from colorspaces import (
    rgb_grayscale,
    rgb_to_xyz,
    xyz_to_rgb,
    rgb_to_hsv,
    rgb_to_hls,
    xyz_to_lab,
    lerp
)

DELTA = 1e-4

# test black and white for all
# test all piecewise conditions

class TestColorConversions(unittest.TestCase):

    def assertListAlmostEqual(self, first, second, delta=DELTA):
        self.assertEqual(len(first), len(second))
        for x, y in zip(first, second):
            self.assertAlmostEqual(x, y, delta=delta)

    def test_rgb_grayscale(self):
        # black and white (and gray)
        self.assertListAlmostEqual([0.0, 0.0, 0.0], rgb_grayscale([0.0, 0.0, 0.0]))
        self.assertListAlmostEqual([0.5, 0.5, 0.5], rgb_grayscale([0.5, 0.5, 0.5]))
        self.assertListAlmostEqual([1.0, 1.0, 1.0], rgb_grayscale([1.0, 1.0, 1.0]))
        # extra
        self.assertListEqual([0.299, 0.299, 0.299], rgb_grayscale([1.0, 0.0, 0.0]))

    def test_rgb_to_xyz(self):
        # black and white (and gray)
        self.assertListAlmostEqual([0.0, 0.0, 0.0], rgb_to_xyz([0.0, 0.0, 0.0]))
        self.assertListAlmostEqual([0.4752, 0.5, 0.5444], rgb_to_xyz([0.5, 0.5, 0.5]))
        self.assertListAlmostEqual([0.9505, 1.0, 1.0888], rgb_to_xyz([1.0, 1.0, 1.0]))

    def test_xyz_to_rgb(self):
        # black and white (and gray)
        self.assertListAlmostEqual([0.6024, 0.4741, 0.4545], xyz_to_rgb([0.5, 0.5, 0.5]))

    def test_rgb_to_hsv(self):
        # black and white (and gray)
        self.assertListAlmostEqual([0.0, 0.0, 0.0], rgb_to_hsv([0.0, 0.0, 0.0]))
        self.assertListAlmostEqual([0.0, 0.0, 0.5], rgb_to_hsv([0.5, 0.5, 0.5]))
        self.assertListAlmostEqual([0.0, 0.0, 1.0], rgb_to_hsv([1.0, 1.0, 1.0]))
        # h depends on the color channel with the highest intensity
        self.assertListAlmostEqual([0.0, 0.375, 0.8], rgb_to_hsv([0.8, 0.5, 0.5]))
        self.assertListAlmostEqual([120.0, 0.375, 0.8], rgb_to_hsv([0.5, 0.8, 0.5]))
        self.assertListAlmostEqual([240.0, 0.375, 0.8], rgb_to_hsv([0.5, 0.5, 0.8]))

    def test_rgb_to_hls(self):
        # black and white (and gray)
        self.assertListAlmostEqual([0.0, 0.0, 0.0], rgb_to_hls([0.0, 0.0, 0.0]))
        self.assertListAlmostEqual([0.0, 0.5, 0.0], rgb_to_hls([0.5, 0.5, 0.5]))
        self.assertListAlmostEqual([0.0, 1.0, 0.0], rgb_to_hls([1.0, 1.0, 1.0]))
        # h depends on the color channel with the highest intensity
        self.assertListAlmostEqual([0.0, 0.65, 0.4285], rgb_to_hls([0.8, 0.5, 0.5]))
        self.assertListAlmostEqual([120.0, 0.65, 0.4285], rgb_to_hls([0.5, 0.8, 0.5]))
        self.assertListAlmostEqual([240.0, 0.65, 0.4285], rgb_to_hls([0.5, 0.5, 0.8]))

    def test_xyz_to_lab(self):
        # black and white (and gray)
        self.assertListAlmostEqual([76.0693, 6.7790, 4.4363], xyz_to_lab([0.5, 0.5, 0.5]))

    def test_lerp(self):
        self.assertListEqual([0.625, 0.625, 0.625], lerp([0.5, 0.5, 0.5], [1.0, 1.0, 1.0], 0.25))

if __name__ == '__main__':
    unittest.main()
