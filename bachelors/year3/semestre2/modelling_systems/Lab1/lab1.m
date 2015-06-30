clc;
clear;
y = load('f6.txt');
T = 5;
x = 0:0.01:T;
N = length(y);
figure;

% Discrete Fourier transform
n = round(N/2);
k = 1:n;
m = 1:N;
em = exp(-1i * 2 * pi * (k' * m) / N);
ft(k) = y(m) * em';
ft = abs(ft);

subplot(2, 2, 1)
plot(x(1:n), ft);
title('My DFT');
subplot(2, 2, 2)
ft1 = abs(fft(y));
plot(x(1:n), ft1(1:n));
title('Standard FFT');

% Find frequencies of sin's
[~, f] = findpeaks(ft);

% Find coeficients a from function formula
K = 3 + length(f);
pos = 1:K-3;
coefs = [x'.^3 x'.^2 x' sin(2*pi * x' * f(pos) / T) ones(N, 1)]';
b = coefs * y';
A = coefs * coefs';
a = linsolve(A, b);

F = a' * coefs;

subplot(2, 2, 3);
plot(x, y);
title('Initial data');

subplot(2, 2, 4);
plot(x, F);
title('Resulting function');

figure;
plot(x, (F-y).^2);