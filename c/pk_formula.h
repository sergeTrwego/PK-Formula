/**
 * @file pk_formula.h
 * @brief Fast closed-form solver for separable polynomial constraints
 * 
 * This library provides an efficient method for solving constraints of the form:
 *     sum(a_i * x_i^p_i) = b
 * 
 * @author Serge T. Rwego
 * @date 2025
 * @license MIT
 * 
 * Reference:
 *     Rwego, S.T. "Efficient Closed-Form Solutions for Separable Polynomial 
 *     Constraints: The Parametric K-Formula with Applications in Positioning 
 *     and Control" Mathematics (2025)
 */

#ifndef PK_FORMULA_H
#define PK_FORMULA_H

/**
 * @brief Solve separable polynomial constraint using PK-Formula
 * 
 * Solves: sum(a[i] * x[i]^p[i]) = b
 * 
 * @param a Coefficient array (length n)
 * @param p Exponent array (length n)
 * @param b Constraint value
 * @param k Parameter value
 * @param n Number of variables
 * @param x Output solution array (length n, pre-allocated)
 * 
 * @return 0 on success, -1 on error
 * 
 * Example:
 * @code
 *     double a[] = {1.0, 1.0, 1.0};
 *     double p[] = {2.0, 2.0, 2.0};
 *     double b = 10.0;
 *     double k = 1.5;
 *     double x[3];
 *     int n = 3;
 *     
 *     pk_formula(a, p, b, k, n, x);
 * @endcode
 */
int pk_formula(const double *a, const double *p, 
               double b, double k, int n, double *x);

/**
 * @brief Verify that solution satisfies the constraint
 * 
 * @param x Solution array (length n)
 * @param a Coefficient array (length n)
 * @param p Exponent array (length n)
 * @param b Constraint value
 * @param n Number of variables
 * @param error Output absolute error
 * 
 * @return 1 if solution is valid (error < 1e-10), 0 otherwise
 */
int verify_solution(const double *x, const double *a, const double *p,
                    double b, int n, double *error);

#endif // PK_FORMULA_H
