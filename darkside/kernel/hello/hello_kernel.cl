/** @file */

#ifndef GEN_DOC
    kernel __attribute__((reqd_work_group_size(1, 1, 1)))
#endif
 /**
 * \ingroup kernel_src
 * \section hello_kernel Hello Kernel (OpenCL C)
 * \author Tianhao Zhou
 * \date 1/3/2019
 * \version final
 * \subsection intro Introduction
 * This kernel is hello world.
 * \subsection details Details
 * It takes a char pointer and write 
 * Hello World! to it
 * \subsection future Future Plans
 * none
 * \subsection availability Availability
 *  - Alveo U200 2018.3.1
 *      - profile counter
 *      - profile trace
 *  - Alveo U200 2018.3.1
 *      - 3 compute units
 *      - profile counter
 *      - profile trace
 *  - Alveo U250 2018.3.1
 *      - profile counter
 *      - profile trace
 */
void hello_kernel(global char* msg /**< [out] pointer to the address where "Hello World!" should be written to*/) {
    msg[0] = 'H';
    msg[1] = 'e';
    msg[2] = 'l';
    msg[3] = 'l';
    msg[4] = 'o';
    msg[5] = ' ';
    msg[6] = 'W';
    msg[7] = 'o';
    msg[8] = 'r';
    msg[9] = 'l';
    msg[10] = 'd';
    msg[11] = '!';
    msg[12] = '\n';
}