/**
 * @file 
 * \ingroup kernel_src
 */

#ifndef GEN_DOC
    kernel __attribute__((reqd_work_group_size(1, 1, 1)))
#endif
/**
 * \ingroup kernel_src
 * \section copy_kernel Copy Kernel (OpenCL C)
 * \author Tianhao Zhou
 * \date 1/3/2019
 * \version final
 * \subsection intro Introduction
 * This kernel copies a fixed size of memory from one address 
 * to another inside the kernel.
 * \subsection details Details
 * It simply use a for loop to copy everything without
 * any optimization as it is not for performance.
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
void copy_kernel(global char* src /**< [in] Pointer to the source memory address */, 
                global char* dest /**< [out] Pointer to the destination memory address*/, 
                const int copy_size /**< [in] Size of the memory to copy */) {
    for (int i = 0; i < copy_size; ++i) {
        dest[i] = src[i];
    }
}