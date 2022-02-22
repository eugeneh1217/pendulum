% pkg load symbolic

%{
syms theta1(t) theta2(t) m1 m2 g y1(t) y2(t) x1(t) x2(t) L1 L2

diff_sys = [
  ( m2*diff(y2, 2) + m2*g ) * sin(theta2) == -m2*x2*cos(theta2);
  ( m1*diff(y1, 2) + m1*g + m2*diff(y2, 2) + m2*g )*sin(theta1) == ...
    -(m2*diff(x2, 2) + m1*diff(x1, 2))*cos(theta1);
  diff(y1, 2) == ...
    L1*( diff(theta1, 2)*sin(theta1) + diff(theta1)*cos(theta1) );
  diff(x1, 2) == ...
    L1*( diff(theta1, 2)*cos(theta1) - diff(theta1)*sin(theta1) );
  diff(y2, 2) == ...
    diff(y1, 2) + L2*( diff(theta2, 2)*sin(theta2) + diff(theta2)*cos(theta2) );
  diff(x2, 2) == ...
    diff(x1, 2) + L2*( diff(theta2, 2)*cos(theta2) - diff(theta2)*sin(theta2) );
];

solution = solve(diff_sys);


solution
%}

syms theta1 theta11 theta12 theta2 theta21 theta22 m1 m2 g y1 y2 y12 y22 x1 x12 x2 x22 L1 L2

diff_sys = [
  ( m2*y22 + m2*g ) * sin(theta2) == -m2*x2*cos(theta2);
  ( m1*y12 + m1*g + m2*y22 + m2*g )*sin(theta1) == ...
    -(m2*x22 + m1*x12)*cos(theta1);
  y12 == ...
    L1*( theta12*sin(theta1) + theta11^2*cos(theta1) );
  x12 == ...
    L1*( theta12*cos(theta1) - theta11^2*sin(theta1) );
  y22 == ...
    y12 + L2*( theta22*sin(theta2) + theta21^2*cos(theta2) );
  x22 == ...
    x12 + L2*( theta22*cos(theta2) - theta21^2*sin(theta2) );
];

solution = solve(diff_sys, [theta12, theta22])
