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

class TestColorConversions(unittest.TestCase):

    def assertListAlmostEqual(self, first, second, delta=DELTA):
        self.assertEqual(len(first), len(second))
        for x, y in zip(first, second):
            self.assertAlmostEqual(x, y, delta=delta)

    def test_rgb_grayscale(self):
        self.assertListAlmostEqual([0.0, 0.0, 0.0], rgb_grayscale([0.0, 0.0, 0.0]))
        self.assertListAlmostEqual([0.5, 0.5, 0.5], rgb_grayscale([0.5, 0.5, 0.5]))
        self.assertListAlmostEqual([1.0, 1.0, 1.0], rgb_grayscale([1.0, 1.0, 1.0]))
        self.assertListEqual([0.299, 0.299, 0.299], rgb_grayscale([1.0, 0.0, 0.0]))

    def test_rgb_to_xyz(self):
        self.assertListAlmostEqual([0.4752, 0.5000, 0.5444], rgb_to_xyz([0.5, 0.5, 0.5]))

    def test_xyz_to_rgb(self):
        self.assertListAlmostEqual([0.6024, 0.4741, 0.4545], xyz_to_rgb([0.5, 0.5, 0.5]))

    def test_rgb_to_hsv(self):
        self.assertListAlmostEqual([0.0000, 0.0000, 0.5000], rgb_to_hsv([0.5, 0.5, 0.5]))

    def test_rgb_to_hls(self):
        self.assertListAlmostEqual([0.0000, 0.5000, 0.0000], rgb_to_hls([0.5, 0.5, 0.5]))

    def test_xyz_to_lab(self):
        self.assertListAlmostEqual([76.0693, 6.7790, 4.4363], xyz_to_lab([0.5, 0.5, 0.5]))

    def test_lerp(self):
        self.assertListEqual([0.625, 0.625, 0.625], lerp([0.5, 0.5, 0.5], [1.0, 1.0, 1.0], 0.25))

if __name__ == '__main__':
    unittest.main()