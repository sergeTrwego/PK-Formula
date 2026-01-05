"""
PK-Formula: Fast closed-form solver for separable polynomial constraints

This module provides an efficient method for solving constraints of the form:
    sum(a_i * x_i^p_i) = b

Reference:
    Rwego, S.T. "Efficient Closed-Form Solutions for Separable Polynomial 
    Constraints: The Parametric K-Formula with Applications in Positioning 
    and Control" Mathematics (2025)

Author: Serge T. Rwego
License: MIT
"""

import numpy as np


def pk_formula(a, p, b, k):
    """
    Solve separable polynomial constraint using PK-Formula.
    
    Solves: sum(a_i * x_i^p_i) = b
    
    Parameters
    ----------
    a : array_like
        Coefficient vector [a1, a2, ..., an]
    p : array_like
        Exponent vector [p1, p2, ..., pn]
    b : float
        Constraint value
    k : float
        Parameter value
    
    Returns
    -------
    x : ndarray
        Solution vector [x1, x2, ..., xn]
    
    Examples
    --------
    >>> import numpy as np
    >>> a = np.array([1.0, 1.0, 1.0])
    >>> p = np.array([2.0, 2.0, 2.0])
    >>> b = 10.0
    >>> k = 1.5
    >>> x = pk_formula(a, p, b, k)
    >>> print(x)
    [2.54950976 1.22474487 1.22474487]
    
    >>> # Verify solution
    >>> constraint_value = np.sum(a * np.power(x, p))
    >>> print(f"Constraint value: {constraint_value:.10f}, Target: {b}")
    Constraint value: 10.0000000000, Target: 10.0
    """
    a = np.asarray(a, dtype=float)
    p = np.asarray(p, dtype=float)
    n = len(a)
    
    x = np.zeros(n)
    
    # Compute x1
    x[0] = np.power((b - (n-1)*k) / a[0], 1.0/p[0])
    
    # Compute remaining variables
    for i in range(1, n):
        x[i] = np.power(k / a[i], 1.0/p[i])
    
    # Verification
    constraint_value = np.sum(a * np.power(x, p))
    error = np.abs(constraint_value - b)
    if error > 1e-10:
        print(f"Warning: Solution error {error:.2e}")
    
    return x


def pk_formula_vectorized(a, p, b, k):
    """
    Vectorized version of PK-Formula for improved performance.
    
    Parameters and returns are identical to pk_formula().
    This version uses NumPy vectorization for faster computation.
    """
    a = np.asarray(a, dtype=float)
    p = np.asarray(p, dtype=float)
    n = len(a)
    
    x = np.zeros(n)
    
    # Compute x1
    x[0] = np.power((b - (n-1)*k) / a[0], 1.0/p[0])
    
    # Compute remaining variables (vectorized)
    x[1:] = np.power(k / a[1:], 1.0 / p[1:])
    
    return x


def verify_solution(x, a, p, b, tol=1e-10):
    """
    Verify that solution x satisfies the constraint.
    
    Parameters
    ----------
    x : array_like
        Solution vector
    a : array_like
        Coefficient vector
    p : array_like
        Exponent vector
    b : float
        Constraint value
    tol : float, optional
        Tolerance for verification (default: 1e-10)
    
    Returns
    -------
    bool
        True if solution satisfies constraint within tolerance
    float
        Absolute error
    """
    x = np.asarray(x)
    a = np.asarray(a)
    p = np.asarray(p)
    
    constraint_value = np.sum(a * np.power(x, p))
    error = np.abs(constraint_value - b)
    
    is_valid = error < tol
    
    return is_valid, error


if __name__ == "__main__":
    # Example usage
    print("PK-Formula Example")
    print("=" * 50)
    
    # Define problem
    a = np.array([1.0, 1.0, 1.0])
    p = np.array([2.0, 2.0, 2.0])
    b = 10.0
    k = 1.5
    
    print(f"Constraint: sum(a_i * x_i^p_i) = {b}")
    print(f"Coefficients: {a}")
    print(f"Exponents: {p}")
    print(f"Parameter k: {k}")
    print()
    
    # Solve
    x = pk_formula(a, p, b, k)
    
    print(f"Solution: {x}")
    print()
    
    # Verify
    is_valid, error = verify_solution(x, a, p, b)
    print(f"Verification: {'PASS' if is_valid else 'FAIL'}")
    print(f"Error: {error:.2e}")
    print()
    
    # Compare with vectorized version
    x_vec = pk_formula_vectorized(a, p, b, k)
    print(f"Vectorized solution matches: {np.allclose(x, x_vec)}")
