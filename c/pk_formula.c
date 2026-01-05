/**
 * @file pk_formula.c
 * @brief Implementation of PK-Formula solver
 */

#include "pk_formula.h"
#include <math.h>
#include <stdio.h>

int pk_formula(const double *a, const double *p, 
               double b, double k, int n, double *x) {
    /*
     * Solve separable polynomial constraint
     * sum(a[i] * x[i]^p[i]) = b
     *
     * Inputs:
     *   a[n] - coefficient array
     *   p[n] - exponent array
     *   b    - constraint value
     *   k    - parameter value
     *   n    - number of variables
     *
     * Output:
     *   x[n] - solution array (pre-allocated)
     *
     * Returns:
     *   0 on success, -1 on error
     */
    
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return -1;
    }
    
    if (a == NULL || p == NULL || x == NULL) {
        fprintf(stderr, "Error: NULL pointer provided\n");
        return -1;
    }
    
    // Compute x[0]
    x[0] = pow((b - (n-1)*k) / a[0], 1.0/p[0]);
    
    // Compute remaining variables
    for (int i = 1; i < n; i++) {
        x[i] = pow(k / a[i], 1.0/p[i]);
    }
    
    return 0;
}

int verify_solution(const double *x, const double *a, const double *p,
                    double b, int n, double *error) {
    /*
     * Verify that solution satisfies the constraint
     *
     * Inputs:
     *   x[n]  - solution array
     *   a[n]  - coefficient array
     *   p[n]  - exponent array
     *   b     - constraint value
     *   n     - number of variables
     *
     * Output:
     *   error - absolute error (pointer)
     *
     * Returns:
     *   1 if valid (error < 1e-10), 0 otherwise
     */
    
    if (x == NULL || a == NULL || p == NULL || error == NULL) {
        fprintf(stderr, "Error: NULL pointer provided\n");
        return 0;
    }
    
    // Compute constraint value
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * pow(x[i], p[i]);
    }
    
    // Calculate error
    *error = fabs(sum - b);
    
    // Check if within tolerance
    return (*error < 1e-10) ? 1 : 0;
}
