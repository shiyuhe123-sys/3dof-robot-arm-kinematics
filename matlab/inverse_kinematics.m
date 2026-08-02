function solutions_deg = inverse_kinematics(target_xyz)
%INVERSE_KINEMATICS Return elbow-up and elbow-down mathematical angles.
% Rows are [theta1 theta2 theta3] in degrees.

L1 = 9.5;
L2 = 15.0;
x = target_xyz(1); y = target_xyz(2); z = target_xyz(3);
r = hypot(x, y);

cos_t3 = (r^2 + z^2 - L1^2 - L2^2) / (2 * L1 * L2);
if abs(cos_t3) > 1 + 1e-9
    error('Target is outside the modelled workspace.');
end
cos_t3 = max(-1, min(1, cos_t3));
t1 = atan2(y, x);
t3_options = [-acos(cos_t3), acos(cos_t3)];

solutions_deg = zeros(2, 3);
for index = 1:2
    t3 = t3_options(index);
    t2 = atan2(-z, r) - atan2(-L2*sin(t3), L1 + L2*cos(t3));
    solutions_deg(index, :) = rad2deg([t1, t2, t3]);
end
end
