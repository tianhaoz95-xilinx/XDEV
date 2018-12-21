kernel __attribute__((reqd_work_group_size(1, 1, 1)))
void hello_kernel(global char* msg) {
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