SIZE = 2.5;
Z_SIZE = 1.5;
STEP_SIZE = 0.2;
STEP_SIZE_SPHERE = 0.3;

R = 0.5;
K = 5 / 2 * R;

% LIMITS
x = -SIZE:STEP_SIZE:SIZE;
y = x;
alpha = 5 * R^2;

% PLANE
[xx, yy] = meshgrid(x, y);
z = - K * exp(-(xx.^2 + yy.^2) / alpha);
mesh(x, y, z);

% SPHERE
psi = 0:STEP_SIZE_SPHERE:pi+STEP_SIZE_SPHERE;
theta = 0:STEP_SIZE_SPHERE:2*pi+STEP_SIZE_SPHERE;

[Theta, Psi] = meshgrid(theta, psi);
X = R * sin(Psi) .* cos(Theta);
Y = R * sin(Psi) .* sin(Theta);
Z = R * cos(Psi);
Z_displacement = R - K;

hold on;
mesh(X, Y, Z + Z_displacement);


% VISUALS
colormap(brighten(copper, 0));
shading interp;
axis([-SIZE SIZE -SIZE SIZE -Z_SIZE Z_SIZE]), axis off;