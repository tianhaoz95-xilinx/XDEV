/** @file */

/**
 * This is the copy kernel
 */
kernel __attribute__((reqd_work_group_size(1, 1, 1)))
void copy_kernel(global char* src, global char* dest, const int copy_size) {
    for (int i = 0; i < copy_size; ++i) {
        dest[i] = src[i];
    }
}