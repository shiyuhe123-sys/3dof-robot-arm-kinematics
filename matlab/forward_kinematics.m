function xyz = forward_kinematics(theta_deg)
%FORWARD_KINEMATICS Return [x y z] in cm for mathematical joint angles.
% Canonical geometry: L1=9.5 cm, L2=15.0 cm, +z upward.

L1 = 9.5;
L2 = 15.0;

t1 = deg2rad(theta_deg(1));
t2 = deg2rad(theta_deg(2));
t3 = deg2rad(theta_deg(3));

c1 = cos(t1); s1 = sin(t1);
c2 = cos(t2); s2 = sin(t2);
c3 = cos(t3); s3 = sin(t3);

x = L2*c1*c2*c3 + L2*c1*s2*s3 + L1*c1*c2;
y = L2*s1*c2*c3 + L2*s1*s2*s3 + L1*s1*c2;
z = -L2*s2*c3 + L2*c2*s3 - L1*s2;

xyz = [x, y, z];
end
