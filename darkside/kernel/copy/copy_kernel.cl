/** @file */

#ifndef GEN_DOC
    kernel __attribute__((reqd_work_group_size(1, 1, 1)))
#endif
/**
 * \ingroup kernel_src
 * Copy Kernel: it copies a fixed size of mempry from one address to another inside the kernel
 */
void copy_kernel(global char* src /**< [in] Pointer to the source memory address */, 
                global char* dest /**< [out] Pointer to the destination memory address*/, 
                const int copy_size /**< [in] Size of the memory to copy */) {
    for (int i = 0; i < copy_size; ++i) {
        dest[i] = src[i];
    }
}