function [] = lab3_fast
    y = load('y6.txt');
    c = [0 0 0.2 0.12];
    m = [12 0 18];
    b = [0.1 0.15 19]';
    h = 0.2;
    n = size(y, 2);
    
    while true
        b
        db = get_db(c, m, y, h, n, b);
        prevb = b;
        b = b + db;
        if sum(abs(b - prevb)) < 1e-3
            break;
        end
    end
end

function [ db ] = get_db(c, m, y, h, n, b)
    A = [
        0                   1   0                   0   0                   0;
        -(b(2)+b(1))/m(1)   0   b(2)/m(1)           0   0                   0;
        0                   0   0                   1   0                   0;
        b(2)/b(3)           0   -(b(2)+c(3))/b(3)   0   c(3)/b(3)           0;
        0                   0   0                   0   0                   1;
        0                   0   c(3)/m(3)           0   -(c(4)+c(3))/m(3)   0
    ];   
    y0 = y(:, 1);
    k = length(y0);
    l = length (b);
    U0 = zeros(k, l);
    p = zeros(l, l);
    q = zeros(l, 1);
    for i = 1:n
        delta_y = y(:, i) - y0;
        p = p + h * (U0' * U0);
        q = q + h * (U0' * delta_y);
        
        k1 = h * get_dU(U0,             A, y0, c, m, b);
        k2 = h * get_dU(U0 + k1 * 0.5,  A, y0, c, m, b);
        k3 = h * get_dU(U0 + k2 * 0.5,  A, y0, c, m, b);
        k4 = h * get_dU(U0 + k3,        A, y0, c, m, b);
        U0 = U0 + (1/6) * (k1 + 2*k2 + 2*k3 + k4);
        
        k1 = h * A * y0;
        k2 = h * A * (y0 + k1 * 0.5);
        k3 = h * A * (y0 + k2 * 0.5);
        k4 = h * A * (y0 + k3);
        y0 = y0 + (1/6) * (k1 + 2*k2 + 2*k3 + k4);
    end
    db = p\q;
end

function [ dU ] = get_dU(Ui, A, y, c, m, b)
    dUb = [
        0               0                       0;
        -y(1)/m(1)      (y(3)-y(1))/m(1)        0;
        0               0                       0;
        0               (y(1)-y(3))/b(3)        (-y(1)*b(2)+y(3)*(b(2)+c(3))-y(5)*c(3))/(b(3)^2);
        0               0                       0;
        0               0                       0
    ];
    dU = A * Ui + dUb;
end