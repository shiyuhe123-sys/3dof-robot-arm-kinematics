# Validation record

## Forward kinematics

The predicted gripper position was calculated from measured joint angles and compared with a ruler measurement in the robot base frame.

| Point | Predicted x | Predicted y | Predicted z | Measured x | Measured y | Measured z | Error |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 | 9.83 | -4.58 | 14.06 | 10.0 | -4.0 | 15.0 | 1.12 cm |
| 2 | 14.10 | 0.00 | 14.63 | 14.0 | 0.0 | 14.0 | 0.64 cm |
| 3 | 15.72 | 7.33 | 14.06 | 18.0 | 8.0 | 13.0 | 2.60 cm |
| 4 | 15.75 | 0.00 | 14.49 | 16.0 | 0.0 | 14.0 | 0.55 cm |
| 5 | 0.00 | 15.00 | 9.50 | 0.0 | 15.0 | 9.5 | 0.00 cm |

Mean Euclidean error: **0.98 cm**. Four of five points were below 1.2 cm; Point 3 combined base, shoulder and elbow motion and produced the 2.60 cm outlier.

## Inverse kinematics

Five Cartesian targets were converted to servo commands and the resulting gripper position was measured.

| Point | Commanded x | Commanded y | Commanded z | Measured x | Measured y | Measured z | Error |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 | 15.0 | 0.0 | 9.5 | 15.5 | 0.0 | 9.5 | 0.50 cm |
| 2 | 20.0 | 0.0 | 0.0 | 20.0 | 0.0 | 0.0 | 0.00 cm |
| 3 | 0.0 | 20.0 | 0.0 | 0.0 | 20.5 | 0.0 | 0.50 cm |
| 4 | 14.0 | 14.0 | 5.0 | 16.0 | 15.0 | 4.5 | 2.29 cm |
| 5 | 10.0 | 0.0 | 15.0 | 10.0 | 0.0 | 16.0 | 1.00 cm |

Mean Euclidean error: **0.86 cm**. The diagonal target produced the largest error because base-angle error affected both x and y while shoulder/elbow compliance affected reach.

## Measurement boundary

- Ruler resolution: approximately +/-0.5 cm per axis.
- Servo positioning accuracy: approximately +/-1-2 deg.
- No encoders or camera-based external reference were available.
- Each point was measured once, so the results do not estimate repeatability.

## Assessed demonstration

| Criterion | Score |
|---|---:|
| Object localisation | 3/4 |
| Straight-line cubic motion to object | 4/4 |
| Stable grasp | 4/4 |
| Return and drop-off motion | 4/4 |
| Controlled release | 4/4 |
| **Total** | **19/20** |

The assessor identified a small bounce during pickup and recommended smoother trajectory timing. The score is a team result.
