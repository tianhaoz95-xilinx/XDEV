/** @file */

#ifndef GEN_DOC
    kernel __attribute__((reqd_work_group_size(1, 1, 1)))
#endif

/**
 * Vadd Kernel: vector addition kernel which adds vector a and vector b
 * both of size n and saves the result in vector c
 */
void vadd_kernel(global const int* a /**< Pointer to vector a (addend 1) */, 
                global const int* b /**< Pointer to vector b (addend 2) */, 
                global int* c /**< Pointer to vector c (result) */, 
                const int n_elements /**< Size of the vectors */) {
    for (int i = 0 ; i < n_elements ; ++i) {
        c[i] = a[i] + b[i];
    }
}