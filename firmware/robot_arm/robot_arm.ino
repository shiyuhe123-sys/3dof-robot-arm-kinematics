#include <Servo.h>
#include <math.h>

namespace Config {
constexpr uint8_t JOINT_1_PIN = 2;
constexpr uint8_t JOINT_2_PIN = 3;
constexpr uint8_t JOINT_3_PIN = 4;
constexpr uint8_t GRIPPER_PIN = 11;
constexpr float L1_CM = 9.5f;
constexpr float L2_CM = 15.0f;
constexpr int OFFSET_1 = 88;
constexpr int OFFSET_2 = 89;
constexpr int OFFSET_3 = 56;
constexpr int GRIPPER_OPEN = 0;
constexpr int GRIPPER_CLOSED = 120;
constexpr float SEGMENT_SECONDS = 5.0f;
constexpr float SAMPLE_SECONDS = 0.1f;
}

struct Point3 {
  float x;
  float y;
  float z;
};

struct JointAngles {
  float theta1;
  float theta2;
  float theta3;
};

Servo joint1;
Servo joint2;
Servo joint3;
Servo gripper;

const Point3 HOME = {15.0f, 0.0f, 9.5f};
const Point3 PICKUP = {7.0f, 18.0f, 3.0f};
const Point3 DROP_OFF = {15.0f, 5.0f, 4.5f};

bool solveElbowUp(const Point3 &target, JointAngles &mathAngles) {
  const float radial = sqrt(target.x * target.x + target.y * target.y);
  float cosineTheta3 =
      (radial * radial + target.z * target.z - Config::L1_CM * Config::L1_CM -
       Config::L2_CM * Config::L2_CM) /
      (2.0f * Config::L1_CM * Config::L2_CM);

  if (cosineTheta3 > 1.0001f || cosineTheta3 < -1.0001f) return false;
  cosineTheta3 = constrain(cosineTheta3, -1.0f, 1.0f);

  const float theta3 = -acos(cosineTheta3);
  const float theta2 = atan2(-target.z, radial) -
                       atan2(-Config::L2_CM * sin(theta3),
                             Config::L1_CM + Config::L2_CM * cos(theta3));
  const float theta1 = radial < 0.001f ? 0.0f : atan2(target.y, target.x);

  mathAngles = {theta1 * RAD_TO_DEG, theta2 * RAD_TO_DEG, theta3 * RAD_TO_DEG};
  return true;
}

bool commandCartesian(const Point3 &target) {
  JointAngles theta;
  if (!solveElbowUp(target, theta)) return false;

  const float physical1 = theta.theta1;
  const float physical2 = theta.theta2 + 90.0f;
  const float physical3 = theta.theta3 + 90.0f;

  const int servo1 = constrain(lround(physical1) + Config::OFFSET_1, 0, 180);
  const int servo2 = constrain(-lround(physical2) + Config::OFFSET_2, 0, 180);
  const int servo3 = constrain(-lround(physical3) + Config::OFFSET_3, 0, 180);

  joint1.write(servo1);
  joint2.write(servo2);
  joint3.write(servo3);
  return true;
}

float cubicPosition(float start, float end, float duration, float time) {
  const float ratio = time / duration;
  const float blend = 3.0f * ratio * ratio - 2.0f * ratio * ratio * ratio;
  return start + (end - start) * blend;
}

bool moveCartesian(const Point3 &start, const Point3 &end) {
  const int intervals = lround(Config::SEGMENT_SECONDS / Config::SAMPLE_SECONDS);
  for (int index = 0; index <= intervals; ++index) {
    const float time = index * Config::SAMPLE_SECONDS;
    const Point3 target = {
        cubicPosition(start.x, end.x, Config::SEGMENT_SECONDS, time),
        cubicPosition(start.y, end.y, Config::SEGMENT_SECONDS, time),
        cubicPosition(start.z, end.z, Config::SEGMENT_SECONDS, time)};
    if (!commandCartesian(target)) return false;
    delay(lround(Config::SAMPLE_SECONDS * 1000.0f));
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  joint1.attach(Config::JOINT_1_PIN);
  joint2.attach(Config::JOINT_2_PIN);
  joint3.attach(Config::JOINT_3_PIN);
  gripper.attach(Config::GRIPPER_PIN);

  commandCartesian(HOME);
  gripper.write(Config::GRIPPER_OPEN);
  delay(5000);

  if (!moveCartesian(HOME, PICKUP)) return;
  delay(5000);
  gripper.write(Config::GRIPPER_CLOSED);
  delay(500);

  if (!moveCartesian(PICKUP, HOME)) return;
  delay(5000);
  if (!moveCartesian(HOME, DROP_OFF)) return;
  delay(5000);
  gripper.write(Config::GRIPPER_OPEN);
  delay(500);
  moveCartesian(DROP_OFF, HOME);
}

void loop() {}
