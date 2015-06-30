function [ Y ] = pseudoinverse( A )
    [n, m] = size(A);
    reverse = n > m;
    if reverse
        A = A';
        [n, m] = size(A);
    end
    a1 = A(1, :)';
    Ax(:, 1) = a1 / (a1' * a1);
    for i = 2:n
        ZA = eye(m) - Ax * A(1:i-1,:);
        RA = Ax * Ax';
        a = A(i, :)';
        if a' * ZA * a > 1e-9
            Ax = Ax - (ZA * (a * a') * Ax) / (a' * ZA * a);
            'незал'
            ax = (ZA * a) / (a' * ZA * a);
        else
            Ax = Ax - (RA * (a * a') * Ax) / (1 + a' * RA * a);
            'залежні'
            ax = (RA * a) / (1 + a' * RA * a);
        end
        Ax(:, i) = ax;
    end
    if reverse
        Ax = Ax';
    end
    Y = Ax;
end