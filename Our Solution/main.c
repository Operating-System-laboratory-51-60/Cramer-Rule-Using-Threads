#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logger.h"
#include "sys_utils.h"
#include "matrix_math.h"
#include "thread_solver.h"

int main()
{
    // 1. Start the Logger immediately
    init_logger("cramer_execution_log.txt");
    
    log_msg("==========================================\n");
    log_msg(" PTHREAD CRAMER'S RULE SOLVER \n");
    log_msg("==========================================\n");
    
    int N;
    // We still use standard printf for the user prompt since it requires keyboard input
    printf("Enter number of equations (N) [e.g., 1000]: ");
    if (scanf("%d", &N) != 1 || N <= 0) N = 300;
    
    log_msg("[User Input] Matrix Size set to N = %d\n", N);

    int cores = get_cpu_cores();
    log_msg("[System] Auto-detected %d CPU cores via lscpu.\n", cores);
    
    srand(time(NULL));
    Matrix *A = create_matrix(N);
    double *B = malloc(N * sizeof(double));
    double *solutions = malloc(N * sizeof(double));
    
    log_msg("[Init] Generating random coefficients...\n");
    fill_random_system(A, B);

    log_msg("[Math] Pre-computing main determinant...\n");
    double det_A = fast_determinant(A);
    if (det_A == 0.0) {
        log_msg("[Error] Singular Matrix. No unique solution.\n");
        close_logger();
        return 1;
    }
    log_msg("[Math] Main determinant calculated: %e\n", det_A);

    log_msg("[Threads] Launching %d Pthreads to solve %d variables...\n", cores, N);
    double time_taken = solve_system_pthreads(A, B, N, cores, det_A, solutions);

    log_msg("------------------------------------------\n");
    log_msg("[Success] Calculation Complete!\n");
    log_msg("[Performance] Total Time Elapsed: %.4f seconds\n", time_taken);
    
    log_msg("[Results] Preview of Solutions (First 10):\n");
    for(int i = 0; i < 10 && i < N; i++) {
        log_msg(" x[%d] = %f\n", i, solutions[i]);
    }

    free(solutions); 
    free(B); 
    free_matrix(A);
    
    log_msg("[System] Shutting down normally.\n");
    close_logger();
    
    return 0;
}
