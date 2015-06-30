function [] = lab3
    y = load('y6.txt');
    h = 0.2;
    % b = [c1, c2, m2]
    c = [0.1 0.15 0.2 0.12]; %
    cvar = [true, true, false, false];
    m = [12 19 18];
    mvar = [false, true, false];
    % c = [0.14    0.3    0.2000    0.1200];    m = [12 28 18];
    n = size(y, 2);
    x = 1:n;
    lambda = 1e-4;
    delta = 1e-3;
    prevI = 1e10;
    while true
        I = estimate(c, m, x, y, h, n);
        if I >= prevI
            lambda = lambda * 2;
        end
        prevI = I;
        I
        if I < 1e-5 || isnan(I)
            break;
        end
        cd = zeros(1, 4);
        for i = 1:4
            cx = c;
            cx(i) = cx(i) + delta;
            cd(i) = cvar(i) * (estimate(cx, m, x, y, h, n) - I) / delta;
        end
        md = zeros(1, 3);
        for i = 1:3
            mx = m;
            mx(i) = mx(i) + delta;
            md(i) = mvar(i) * (estimate(c, mx, x, y, h, n) - I) / delta;
        end
        m = m - md * lambda; c = c - cd * lambda;
    end
    c
    m
end

function [ I ] = estimate(c, m, x, y, h, n)
    A = [
        0                   1   0                   0   0                   0;
        -(c(2)+c(1))/m(1)   0   c(2)/m(1)           0   0                   0;
        0                   0   0                   1   0                   0;
        c(2)/m(2)           0   -(c(2)+c(3))/m(2)   0   c(3)/m(2)           0;
        0                   0   0                   0   0                   1;
        0                   0   c(3)/m(3)           0   -(c(4)+c(3))/m(3)   0
    ];
    Y = RungeKutta(A, y(:, 1), n, h);
    I = 0;
    for i = x
        I = I + h * (y(:, i) - Y(:, i))' * (y(:, i) - Y(:, i));
    end
end

function [ Y ] = RungeKutta( A, y0, n, h )
    Y = zeros(6, n);
    Y(:, 1) = y0;
    for i = 2:n
        k1 = h * A * y0;
        k2 = h * A * (y0 + k1 * 0.5);
        k3 = h * A * (y0 + k2 * 0.5);
        k4 = h * A * (y0 + k3);
        y0 = y0 + (1/6) * (k1 + 2*k2 + 2*k3 + k4);
        Y(:, i) = y0;
    end
end
