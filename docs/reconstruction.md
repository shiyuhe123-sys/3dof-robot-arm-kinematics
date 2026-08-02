# Portfolio reconstruction notes

This repository was reconstructed from archived MATLAB/Arduino files and the submitted team report. The report is treated as the authoritative record because several working files contained contradictory constants or stale serial-output labels.

## Corrections

1. **Link length**: an archived IK test file used `L1 = 7.5`; the report, physical setup and other source files use `L1 = 9.5 cm`. The curated code uses 9.5 cm everywhere.
2. **Trajectory labels**: archived Arduino variables used `(7, 18, 3)` and `(15, 5, 4.5)` while serial strings described different points. Variables and printed output now agree.
3. **Vertical sign**: archived validation and trajectory files mixed upward-positive model coordinates with a trajectory-only negative home coordinate. The curated implementation uses a single base frame with +z upward.
4. **Sample count**: a 5.0 s segment at 0.1 s has 50 intervals and 51 commanded samples when both endpoints are included.
5. **Evidence wording**: measured historical results remain attributed to the team prototype; corrected source is labelled as a portfolio reconstruction rather than represented as the exact assessed binary.

## Coordinate convention

- `theta1`: base rotation about +z.
- `theta2`, `theta3`: mathematical joint angles used by the kinematic equations.
- `J1 = theta1`, `J2 = theta2 + 90 deg`, `J3 = theta3 + 90 deg`.
- Servo writes apply the measured offsets and mounting sign inversions.

The planar equations are:

```text
r  = L1 cos(theta2) + L2 cos(theta2 - theta3)
-z = L1 sin(theta2) + L2 sin(theta2 - theta3)
theta1 = atan2(y, x)
```

The elbow-up solution uses the negative branch of `acos` for `theta3`.
