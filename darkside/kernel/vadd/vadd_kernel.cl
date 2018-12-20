kernel __attribute__((reqd_work_group_size(1, 1, 1)))
void vadd_kernel(global const int* a, global const int* b, global int* c, const int n_elements) {
    for (int i = 0 ; i < n_elements ; ++i) {
        c[i] = a[i] + b[i];
    }
}