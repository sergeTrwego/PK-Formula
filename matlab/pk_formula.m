function x = pk_formula(a, p, b, k)
    % PK_FORMULA Solve separable polynomial constraint
    %   x = pk_formula(a, p, b, k)
    %   Solves: sum(a_i * x_i^p_i) = b
    %
    % Inputs:
    %   a - coefficient vector [a1, a2, ..., an]
    %   p - exponent vector [p1, p2, ..., pn]
    %   b - constraint value (scalar)
    %   k - parameter value (scalar)
    %
    % Output:
    %   x - solution vector [x1, x2, ..., xn]
    %
    % Example:
    %   a = [1, 1, 1];
    %   p = [2, 2, 2];
    %   b = 10;
    %   k = 1.5;
    %   x = pk_formula(a, p, b, k);
    %
    % Reference:
    %   Rwego, S.T. "Efficient Closed-Form Solutions for Separable 
    %   Polynomial Constraints: The Parametric K-Formula with Applications 
    %   in Positioning and Control" Mathematics (2025)
    
    n = length(a);
    x = zeros(n, 1);
    
    % Compute x1
    x(1) = ((b - (n-1)*k) / a(1))^(1/p(1));
    
    % Compute remaining variables
    for i = 2:n
        x(i) = (k / a(i))^(1/p(i));
    end
    
    % Verification (optional)
    constraint_value = sum(a(:) .* (x(:).^p(:)));
    error = abs(constraint_value - b);
    if error > 1e-10
        warning('Solution error: %.2e', error);
    end
end
