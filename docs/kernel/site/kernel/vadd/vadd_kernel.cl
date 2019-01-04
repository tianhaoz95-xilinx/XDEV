/** @file */

#ifndef GEN_DOC
    kernel __attribute__((reqd_work_group_size(1, 1, 1)))
#endif
 /**
 * \ingroup kernel_src
 * \section vadd_kernel Vadd Kernel (OpenCL C)
 * \author Tianhao Zhou
 * \date 1/3/2019
 * \version final
 * \subsection intro Introduction
 * Vector addition kernel which adds vector a and vector b
 * both of size n and saves the result in vector c.
 * \subsection details Details
 * It is a simple for loop without any optimization.
 * \subsection future Future Plans
 * none
 * \subsection availability Availability
 *  - Alveo U200 2018.3.1
 *      - profile counter
 *      - profile trace
 *  - Alveo U250 2018.3.1
 *      - profile counter
 *      - profile trace
 */
void vadd_kernel(global const int* a /**< [in] Pointer to vector a (addend 1) */, 
                global const int* b /**< [in] Pointer to vector b (addend 2) */, 
                global int* c /**< [out] Pointer to vector c (result) */, 
                const int n_elements /**< [in] Size of the vectors */) {
    for (int i = 0 ; i < n_elements ; ++i) {
        c[i] = a[i] + b[i];
    }
}