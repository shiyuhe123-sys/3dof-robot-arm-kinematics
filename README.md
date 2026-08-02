# 3-DOF robot arm: kinematics and Cartesian trajectory control

An assessed UCL team project that converted measured Cartesian targets into physical pick-and-place motion using forward/inverse kinematics, servo calibration and a cubic Cartesian trajectory.

## Result

- **19/20 assessed demonstration**: 3/4 object localisation; 4/4 motion to object, grasping, return/drop-off and release.
- **0.98 cm mean FK error** across five measured poses.
- **0.86 cm mean IK error** across five commanded Cartesian targets.
- Four 5 s trajectory segments, sampled at 0.1 s intervals.

Measurements were made with a ruler at approximately +/-0.5 cm resolution. The largest errors occurred in multi-joint configurations where servo accuracy, backlash, compliance and manual frame alignment compounded at the gripper.

## My contribution

I coordinated task allocation and co-owned the Arduino-side control implementation. The MATLAB verification and submitted report were team outputs. This repository publishes a curated portfolio reconstruction with team publication permission; it is not the original submission archive.

## System

```text
Target XYZ
   -> reachability + elbow-up inverse kinematics
   -> physical-angle conversion
   -> calibrated servo offsets and sign mapping
   -> 3 positional servos + gripper
```

Authoritative configuration:

| Parameter | Value |
|---|---:|
| Upper link, L1 | 9.5 cm |
| Forearm link, L2 | 15.0 cm |
| Joint offsets | 88 deg, 89 deg, 56 deg |
| Trajectory duration | 5.0 s per segment |
| Command interval | 0.1 s |

## Repository map

- [`firmware/robot_arm/robot_arm.ino`](firmware/robot_arm/robot_arm.ino): reconstructed Arduino pick-and-place controller.
- [`matlab/forward_kinematics.m`](matlab/forward_kinematics.m): canonical FK implementation.
- [`matlab/inverse_kinematics.m`](matlab/inverse_kinematics.m): canonical elbow-up/down IK implementation.
- [`docs/validation.md`](docs/validation.md): complete five-point validation tables and assessment breakdown.
- [`docs/reconstruction.md`](docs/reconstruction.md): corrections made while reconciling archived files with the submitted report.
- [`verification/test_kinematics.py`](verification/test_kinematics.py): zero-dependency numerical checks.
- [`media/`](media): selected photographs of the assembled arm and ruler-based FK/IK validation.

Run the verification suite with:

```bash
python -m unittest discover -s verification -v
```

## Evidence boundary

The assessed score and measured errors describe the historical team prototype. The curated source here resolves documentation inconsistencies and has not been rerun on the original hardware. No licence is granted for reuse because team permission to display the work does not establish collective relicensing rights.
