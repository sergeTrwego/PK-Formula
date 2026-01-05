/**
 * @file example_basic.c
 * @brief Basic example of using PK-Formula in C
 * 
 * Compile: gcc -o example_basic example_basic.c pk_formula.c -lm
 * Run: ./example_basic
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pk_formula.h"

void print_array(const char *name, const double *arr, int n) {
    printf("%s: [", name);
    for (int i = 0; i < n; i++) {
        printf("%.4f", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    printf("============================================================\n");
    printf("PK-Formula: Basic Example in C\n");
    printf("============================================================\n\n");
    
    // Problem setup
    int n = 5;
    double a[] = {1.0, 1.0, 1.0, 1.0, 1.0};
    double p[] = {2.0, 2.0, 2.0, 2.0, 2.0};
    double b = 25.0;
    double k = 2.5;
    
    printf("Problem Configuration:\n");
    printf("  Number of variables: %d\n", n);
    print_array("  Coefficients (a)", a, n);
    print_array("  Exponents (p)", p, n);
    printf("  Constraint value (b): %.4f\n", b);
    printf("  Parameter (k): %.4f\n\n", k);
    
    // Allocate solution array
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    
    // Solve using PK-Formula
    printf("Solving with PK-Formula...\n");
    
    clock_t start = clock();
    int result = pk_formula(a, p, b, k, n, x);
    clock_t end = clock();
    
    double time_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    
    if (result != 0) {
        fprintf(stderr, "Error: pk_formula failed\n");
        free(x);
        return 1;
    }
    
    printf("Solution computed successfully in %.6f ms\n\n", time_ms);
    
    // Display solution
    printf("Solution:\n");
    print_array("  x", x, n);
    printf("\n");
    
    // Verify solution
    double error;
    int is_valid = verify_solution(x, a, p, b, n, &error);
    
    printf("Verification:\n");
    printf("  Status: %s\n", is_valid ? "PASS" : "FAIL");
    printf("  Absolute error: %.2e\n\n", error);
    
    // Additional example: Different parameter value
    printf("------------------------------------------------------------\n");
    printf("Testing with different parameter value...\n\n");
    
    double k2 = 1.0;
    printf("New parameter (k): %.4f\n", k2);
    
    result = pk_formula(a, p, b, k2, n, x);
    if (result == 0) {
        print_array("New solution (x)", x, n);
        
        is_valid = verify_solution(x, a, p, b, n, &error);
        printf("Verification: %s (error: %.2e)\n\n", 
               is_valid ? "PASS" : "FAIL", error);
    }
    
    // Example: Larger problem
    printf("------------------------------------------------------------\n");
    printf("Testing with larger problem (n=20)...\n\n");
    
    int n_large = 20;
    double *a_large = (double *)malloc(n_large * sizeof(double));
    double *p_large = (double *)malloc(n_large * sizeof(double));
    double *x_large = (double *)malloc(n_large * sizeof(double));
    
    if (a_large == NULL || p_large == NULL || x_large == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(x);
        return 1;
    }
    
    // Initialize large problem
    for (int i = 0; i < n_large; i++) {
        a_large[i] = 1.0;
        p_large[i] = 2.0;
    }
    double b_large = 100.0;
    double k_large = 5.0;
    
    printf("  n = %d, b = %.1f, k = %.1f\n", n_large, b_large, k_large);
    
    // Solve
    start = clock();
    result = pk_formula(a_large, p_large, b_large, k_large, n_large, x_large);
    end = clock();
    time_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    
    if (result == 0) {
        printf("  Solution computed in %.6f ms\n", time_ms);
        
        // Verify
        is_valid = verify_solution(x_large, a_large, p_large, b_large, 
                                   n_large, &error);
        printf("  Verification: %s (error: %.2e)\n", 
               is_valid ? "PASS" : "FAIL", error);
        
        // Show first 5 values
        printf("  First 5 values: [%.4f, %.4f, %.4f, %.4f, %.4f]\n",
               x_large[0], x_large[1], x_large[2], x_large[3], x_large[4]);
    }
    
    printf("\n");
    printf("============================================================\n");
    printf("Examples completed successfully!\n");
    printf("============================================================\n");
    
    // Cleanup
    free(x);
    free(a_large);
    free(p_large);
    free(x_large);
    
    return 0;
}
