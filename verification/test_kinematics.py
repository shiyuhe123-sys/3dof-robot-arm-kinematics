import math
import unittest

L1 = 9.5
L2 = 15.0


def forward(theta1_deg, theta2_deg, theta3_deg):
    t1, t2, t3 = map(math.radians, (theta1_deg, theta2_deg, theta3_deg))
    c1, s1 = math.cos(t1), math.sin(t1)
    c2, s2 = math.cos(t2), math.sin(t2)
    c3, s3 = math.cos(t3), math.sin(t3)
    x = L2 * c1 * c2 * c3 + L2 * c1 * s2 * s3 + L1 * c1 * c2
    y = L2 * s1 * c2 * c3 + L2 * s1 * s2 * s3 + L1 * s1 * c2
    z = -L2 * s2 * c3 + L2 * c2 * s3 - L1 * s2
    return x, y, z


def inverse_elbow_up(x, y, z):
    radial = math.hypot(x, y)
    cosine = (radial**2 + z**2 - L1**2 - L2**2) / (2 * L1 * L2)
    if abs(cosine) > 1.0 + 1e-9:
        raise ValueError("target is outside the modelled workspace")
    cosine = max(-1.0, min(1.0, cosine))
    t3 = -math.acos(cosine)
    t2 = math.atan2(-z, radial) - math.atan2(-L2 * math.sin(t3), L1 + L2 * math.cos(t3))
    t1 = math.atan2(y, x) if radial > 1e-9 else 0.0
    return tuple(map(math.degrees, (t1, t2, t3)))


def cubic_position(start, end, duration, time):
    delta = end - start
    ratio = time / duration
    return start + delta * (3 * ratio**2 - 2 * ratio**3)


class KinematicsTests(unittest.TestCase):
    def test_inverse_forward_round_trip(self):
        for target in [(15, 0, 9.5), (20, 0, 0), (0, 20, 0), (14, 14, 5), (10, 0, 15)]:
            result = forward(*inverse_elbow_up(*target))
            for actual, expected in zip(result, target):
                self.assertAlmostEqual(actual, expected, places=8)

    def test_published_mean_errors(self):
        fk_errors = [1.12, 0.64, 2.60, 0.55, 0.00]
        ik_errors = [0.50, 0.00, 0.50, 2.29, 1.00]
        self.assertAlmostEqual(sum(fk_errors) / len(fk_errors), 0.98, places=2)
        self.assertAlmostEqual(sum(ik_errors) / len(ik_errors), 0.86, places=2)

    def test_cubic_boundary_conditions(self):
        self.assertEqual(cubic_position(2.0, 9.0, 5.0, 0.0), 2.0)
        self.assertEqual(cubic_position(2.0, 9.0, 5.0, 5.0), 9.0)
        epsilon = 1e-5
        start_velocity = (cubic_position(2.0, 9.0, 5.0, epsilon) - 2.0) / epsilon
        end_velocity = (9.0 - cubic_position(2.0, 9.0, 5.0, 5.0 - epsilon)) / epsilon
        self.assertAlmostEqual(start_velocity, 0.0, places=4)
        self.assertAlmostEqual(end_velocity, 0.0, places=4)


if __name__ == "__main__":
    unittest.main()
