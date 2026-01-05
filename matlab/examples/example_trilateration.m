% example_trilateration.m
% Example: Indoor positioning using trilateration with PK-Formula
%
% This example demonstrates how to use the PK-Formula for solving
% trilateration problems in indoor positioning systems.

clear; clc;

fprintf('=== PK-Formula: Trilateration Example ===\n\n');

% Define sensor positions (x, y coordinates in meters)
sensors = [
    0,  0;   % Sensor 1
    10, 0;   % Sensor 2
    5,  8;   % Sensor 3
    10, 8    % Sensor 4
];

% True object position
true_pos = [6, 4];

fprintf('Sensor positions:\n');
disp(sensors);
fprintf('True object position: [%.2f, %.2f]\n\n', true_pos);

% Calculate distances from object to sensors
n_sensors = size(sensors, 1);
distances = zeros(n_sensors, 1);
for i = 1:n_sensors
    distances(i) = norm(true_pos - sensors(i, :));
end

fprintf('Measured distances from sensors:\n');
for i = 1:n_sensors
    fprintf('  Sensor %d: %.4f m\n', i, distances(i));
end
fprintf('\n');

% Transform to PK-standard form
% For trilateration: sum((x - s_x)^2 + (y - s_y)^2) = sum(d^2)
% After expansion and transformation: n*u^2 + n*v^2 = b
% where u = x - mean(s_x), v = y - mean(s_y)

% Calculate centroid
centroid = mean(sensors, 1);

% Right-hand side
b = sum(distances.^2) - sum(sum(sensors.^2, 2));

% For simplified example: n*x^2 + n*y^2 = b_transformed
% This is the separable form
n = 2;  % 2 variables (x, y in transformed coordinates)
a = [n_sensors, n_sensors];  % coefficients
p = [2, 2];                   % exponents

% Choose parameter k
k = b / (2 * n_sensors);  % Simple heuristic

% Solve using PK-Formula
x_solution = pk_formula(a, p, b, k);

fprintf('PK-Formula solution (transformed coordinates):\n');
fprintf('  u = %.4f, v = %.4f\n\n', x_solution(1), x_solution(2));

% Transform back to original coordinates
estimated_pos = x_solution' + centroid;

fprintf('Estimated position: [%.4f, %.4f]\n', estimated_pos);
fprintf('True position:      [%.4f, %.4f]\n', true_pos);
fprintf('Position error:     %.4f m\n\n', norm(estimated_pos - true_pos));

% Visualize
figure('Position', [100, 100, 800, 600]);
hold on; grid on;

% Plot sensors
plot(sensors(:, 1), sensors(:, 2), 'bs', 'MarkerSize', 12, ...
     'LineWidth', 2, 'DisplayName', 'Sensors');

% Plot distance circles
theta = linspace(0, 2*pi, 100);
for i = 1:n_sensors
    x_circle = sensors(i, 1) + distances(i) * cos(theta);
    y_circle = sensors(i, 2) + distances(i) * sin(theta);
    plot(x_circle, y_circle, 'b--', 'LineWidth', 1, 'HandleVisibility', 'off');
end

% Plot true position
plot(true_pos(1), true_pos(2), 'go', 'MarkerSize', 15, ...
     'LineWidth', 3, 'DisplayName', 'True Position');

% Plot estimated position
plot(estimated_pos(1), estimated_pos(2), 'r^', 'MarkerSize', 15, ...
     'LineWidth', 3, 'DisplayName', 'Estimated Position');

xlabel('X Position (m)');
ylabel('Y Position (m)');
title('Trilateration using PK-Formula');
legend('Location', 'best');
axis equal;
xlim([-2, 12]);
ylim([-2, 10]);

fprintf('Visualization complete.\n');
